/*
Copyright (C) 2001-2008, The Perl Foundation.
$Id: gc_ims.c 27452 2008-05-12 02:15:12Z Whiteknight $

=head1 NAME

src/gc/gc_it.c - Incremental Tricolor Garbage Collector

=head1 DESCRIPTION

This garbage collector, as described in PDD09, will use a tricolor
incremental marking scheme. More details to be fleshed out later.

=head1 NOTES

This file is under heavy manipulation, and it isn't going to be the
prettiest or most standards-compliant code for now. We can add
spit and polish later.

Open Questions:
1) Should GC headers exist in the small object pools, or should they be
   separate? I could create a separate pool for GC headers, managed manually
   by the GC.
2) Should the Arenas object have a fourth pointer for an initialization
   function? Alternatively, reuse the current deinit function pointer
   with an optional init/deinit flag. This makes the GC more dynamic.
*/

#include "parrot/parrot.h"
#include "parrot/dod.h"

#if PARROT_GC_IT

#if GC_IT_SERIAL_MODE
#   define gc_it_trace(i) gc_it_trace_normal(i);
#elif GC_IT_PARALLEL_MODE
#   define gc_it_trace(i) gc_it_trace_threaded(i);
#endif

#define GC_IT_DEBUG 1

/*
 * Macros for doing common things with the GC_IT
 */

#define GC_IT_MARK_NODE_BLACK(gc_data, hdr) do{ \
    gc_it_set_card_mark((hdr), GC_IT_CARD_BLACK); \
    if((gc_data)->queue == (hdr)) \
        (gc_data)->queue = (hdr)->next; \
    (hdr)->next = NULL; \
} while(0)

#define GC_IT_MARK_NODE_GREY(gc_data, hdr) do { \
    (hdr)->next = (gc_data)->queue; \
    (gc_data)->queue = (hdr); \
} while(0)

#define GC_IT_ADD_TO_QUEUE(gc_data, hdr) do {\
    (hdr)->next = (gc_data)->queue; \
    (gc_data)->queue = (hdr); \
} while(0)

#define GC_IT_ADD_TO_ROOT_QUEUE(gc_data, hdr) do {\
    (hdr)->next = (gc_data)->root_queue; \
    (gc_data)->root_queue = (hdr); \
} while(0)

#define GC_IT_ADD_TO_FREE_LIST(pool, hdr) do { \
    (hdr)->next = (Gc_it_hdr*)((pool)->free_list); \
    (pool)->free_list = (void *)(hdr); \
} while(0)

#define GC_IT_POP_HDR_FROM_LIST(list, hdr, type) do {\
    (hdr) = (Gc_it_hdr*)(list); \
    (list) = (type)(hdr)->next; \
} while(0)

#define GC_IT_MARK_CHILDREN_GREY(interp, node) do { \
    if(gc_it_hdr_is_PObj_compatible(node)) \
        gc_it_mark_PObj_children_grey(interp, node); \
} while(0);

#define GC_IT_HDR_FROM_INDEX(p, a, i) \
    (Gc_it_hdr*)(((char*)(a)->start_objects)+((p)->object_size*(i)))


/* HEADERIZER HFILE: include/parrot/dod.h */

/* HEADERIZER BEGIN: static */
/* Don't modify between HEADERIZER BEGIN / HEADERIZER END.  Your changes will be lost. */

static void gc_it_add_arena_to_free_list(PARROT_INTERP,
    ARGMOD(Small_Object_Pool *pool),
    ARGMOD(Small_Object_Arena *new_arena))
        __attribute__nonnull__(1)
        __attribute__nonnull__(2)
        __attribute__nonnull__(3)
        FUNC_MODIFIES(*pool)
        FUNC_MODIFIES(*new_arena);

PARROT_INLINE
static void gc_it_enqueue_all_roots(PARROT_INTERP)
        __attribute__nonnull__(1);

static void gc_it_enqueue_next_root(PARROT_INTERP)
        __attribute__nonnull__(1);

static void gc_it_finalize_all_pmc(PARROT_INTERP)
        __attribute__nonnull__(1);

static void gc_it_finalize_PMC_arenas(PARROT_INTERP,
    ARGMOD(Gc_it_data* gc_priv_data),
    ARGMOD(Small_Object_Pool *pool))
        __attribute__nonnull__(1)
        __attribute__nonnull__(2)
        __attribute__nonnull__(3)
        FUNC_MODIFIES(* gc_priv_data)
        FUNC_MODIFIES(*pool);

PARROT_INLINE
static void gc_it_mark_children_grey(PARROT_INTERP, ARGMOD(Gc_it_hdr * hdr))
        __attribute__nonnull__(1)
        __attribute__nonnull__(2)
        FUNC_MODIFIES(* hdr);

static void gc_it_post_sweep_cleanup(SHIM_INTERP);
static void gc_it_sweep_header_arenas(PARROT_INTERP,
    ARGMOD(Gc_it_data *gc_priv_data),
    ARGMOD(Small_Object_Pool *pool))
        __attribute__nonnull__(1)
        __attribute__nonnull__(2)
        __attribute__nonnull__(3)
        FUNC_MODIFIES(*gc_priv_data)
        FUNC_MODIFIES(*pool);

static void gc_it_sweep_header_pools(PARROT_INTERP)
        __attribute__nonnull__(1);

static void gc_it_sweep_PMC_arenas(PARROT_INTERP,
    ARGMOD(Gc_it_data *gc_priv_data),
    ARGMOD(Small_Object_Pool *pool))
        __attribute__nonnull__(1)
        __attribute__nonnull__(2)
        __attribute__nonnull__(3)
        FUNC_MODIFIES(*gc_priv_data)
        FUNC_MODIFIES(*pool);

static void gc_it_sweep_pmc_pools(PARROT_INTERP)
        __attribute__nonnull__(1);

static void gc_it_sweep_sized_pools(PARROT_INTERP)
        __attribute__nonnull__(1);

/* Don't modify between HEADERIZER BEGIN / HEADERIZER END.  Your changes will be lost. */
/* HEADERIZER END: static */

/*

=item C<void Parrot_gc_it_init>

Initializes the GC, sets the necessary pointers in the interpreter.
We initialize the Gc_it_data structure for the GC, and set the initial
state of the collector.

=cut

*/

PARROT_API
void
Parrot_gc_it_init(PARROT_INTERP)
{
    Arenas * const arena_base = interp->arena_base;
    Gc_it_data * gc_priv_data;
    /* Create our private data. We might need to initialize some things
    here, depending on the data we include in this structure */
    arena_base->gc_private        = mem_allocate_zeroed_typed(Gc_it_data);
    gc_priv_data = (Gc_it_data *)arena_base->gc_private;

    gc_priv_data->state           = GC_IT_READY;

    /* set function hooks according to pdd09 */
    arena_base->do_gc_mark         = Parrot_gc_it_run;
    arena_base->finalize_gc_system = Parrot_gc_it_deinit;
    arena_base->init_pool          = Parrot_gc_it_pool_init;
}

/*

=item C<void Parrot_gc_it_run>

Run the GC. Not sure what it means to "run" yet, might only run one
increment, or one step from many.

Basic Algorithm:
1) Determine which pool/generation to scan
2) Mark root items as being grey
3) For all grey items, mark all children as grey, then mark item as black
4) repeat (3) until there are no grey items in current pool/generation
5) mark all objects grey that appear in IGP lists. Repeat (1) - (4) for these
6) Add all items that are still white to the free list
7) Scan through simple buffers, add white objects to free list
8) reset all flags to white
Only reclaim objects where there are no greys in the current area,
and when a run has completed. Do not reclaim, for instance, any white
objects after a run has completed and all black objects have been turned
back to white (which would free all objects, alive or dead).

Flags and other issues:
GC_trace_normal = run a trace, or a partial trace, but not a sweep.
    set the macro CHECK_IF_WE_BREAK_BEFORE_SWEEP, however we do that,
    to break off the function after the trace phase.
GC_trace_stack_FLAG = we need to trace the C stack and the processor
    registers too. I wouldn't even know how to start doing this.
GC_lazy_FLAG = Appears we run a sweep phase if we have already marked,
    or complete the current mark and then sweep. Or, we find some other
    way to free items that are obviously dead.
GC_finish_FLAG = set all objects to dead, call all finalizers on PMC
    objects. We don't need to mark free items, since everything is going
    to die anyway.

If GC_trace_normal && (GC_IT_FLAG_NEW_MARK || GC_IT_FLAG_RESUME_MARK)
    run a trace or resume the current trace.

if GC_trace_normal && (GC_IT_FLAG_NEW_SWEEP || GC_IT_FLAG_RESUME_SWEEP)
    do nothing

if GC_lazy_FLAG && (GC_IT_FLAG_NEW_SWEEP || GC_IT_FLAG_RESUME_SWEEP)
    run a sweep, possibly to conclusion.

if GC_finish_FLAG
    run a complete sweep of the PMC area calling finalizers only but not
    marking objects or adding objects to the free list

=cut

*/

PARROT_API
void
Parrot_gc_it_run(PARROT_INTERP, int flags)
{
    const Arenas * const arena_base = interp->arena_base;
    Gc_it_data * const gc_priv_data = (Gc_it_data*)(arena_base->gc_private);

    if(flags & GC_finish_FLAG) {
        /* If we've gotten the finish flag, the interpreter is closing down.
           go through all items, call finalization on all PMCs, and do
           whatever else we need to do. */
        gc_priv_data->state = GC_IT_RESUME_MARK;
        Parrot_dod_trace_root(interp, 1); /* Add globals directly to the queue */
        gc_it_finalize_all_pmc(interp);
        gc_it_post_sweep_cleanup(interp);
        gc_priv_data->state = GC_IT_FINAL_CLEANUP;
        return;
    }
    gc_priv_data->item_count = 0; /* items scanned this run */
    switch (gc_priv_data->state) {
        case GC_IT_READY:
            gc_priv_data->state = GC_IT_START_MARK;
#ifdef GC_IT_DEBUG
            printf("initializing new GC run.\n");
#endif
            GC_IT_BREAK_AFTER_0;

        case GC_IT_START_MARK:
            gc_priv_data->total_count = 0;
            gc_priv_data->state = GC_IT_MARK_ROOTS;
            GC_IT_BREAK_AFTER_1;

        case GC_IT_MARK_ROOTS:
            Parrot_dod_trace_root(interp, 1);
            gc_priv_data->state = GC_IT_RESUME_MARK;
            GC_IT_BREAK_AFTER_2;

        case GC_IT_RESUME_MARK:
#if GC_IT_INCREMENT_MODE
            /* scan a single tree. Check to ensure we've hit a minimum number
               of items. If not, scan another tree. */
            do {
                gc_it_enqueue_next_root(interp);
                gc_it_trace(interp);
            } while(gc_priv_data->item_count < GC_IT_ITEMS_MARKED_MIN &&
                    gc_priv_data->root_queue != NULL);
            /* We've either scanned the necessary number of items, or we've
               run out of new root items to scan. Check to see if the mark
               is complete, and if so move to the next state. Otherwise,
               stay at the same state so we can come back. */
            if(gc_priv_data->queue == NULL &&
               gc_priv_data->root_queue == NULL)
                gc_priv_data->state = GC_IT_END_MARK;
            else
                break;
#elif GC_IT_BATCH_MODE
            /* in batch mode, enqueue all roots, and scan the entire pile */
            gc_it_enqueue_all_roots(interp);
            gc_it_trace(interp)
#endif
            GC_IT_BREAK_AFTER_3;

        case GC_IT_END_MARK:
            /* Don't know if there is anything to be done here */
            gc_priv_data->state = GC_IT_SWEEP_PMCS;
#ifdef GC_IT_DEBUG
            printf("ending mark, marked %d items\n", gc_priv_data->total_count);
#endif
            GC_IT_BREAK_AFTER_4;

        case GC_IT_SWEEP_PMCS:
            gc_it_sweep_pmc_pools(interp);
            gc_priv_data->state = GC_IT_SWEEP_HEADERS;
            GC_IT_BREAK_AFTER_5;

        case GC_IT_SWEEP_HEADERS:
            gc_it_sweep_header_pools(interp);
            gc_priv_data->state = GC_IT_SWEEP_BUFFERS;
            GC_IT_BREAK_AFTER_6;

        case GC_IT_SWEEP_BUFFERS:
            gc_it_sweep_sized_pools(interp);
            gc_priv_data->state = GC_IT_FINAL_CLEANUP;
            GC_IT_BREAK_AFTER_7;

        case GC_IT_FINAL_CLEANUP:
            gc_it_post_sweep_cleanup(interp); /* if any. */
        default:
            gc_priv_data->state = GC_IT_READY;
#ifdef GC_IT_DEBUG
            printf("Finished GC run.\n");
#endif
    }
    return;
}

/*

=item C<void gc_it_trace_normal>

Perform a "normal" (i.e. not "threaded") trace. We run through the entire
queue, and continue to scan until the queue is empty. The secret to the
incremental behavior of the collector is careful limiting of what objects
are added to the queue in the first place. We store root objects on the
separate C<root_queue>, and add them one-at-a-time to the queue before
we call this function. This algorithm is probably best called "tree at a
time", because we scan a single tree from the root all the way through to
it's children.

=cut

*/

#if GC_IT_SERIAL_MODE
void
gc_it_trace_normal(PARROT_INTERP)
{
    /* trace through the entire queue until it is empty. */
    Gc_it_data * const gc_priv_data = (Gc_it_data*)interp->arena_base->gc_private;
    Gc_it_hdr * cur_item;

    while((cur_item = gc_priv_data->queue)) {
        /* for each item, add all chidren to the queue, and then mark the item
           black. Once black, the item can be removed from the queue and
           discarded */
        PARROT_ASSERT(cur_item);
        GC_IT_MARK_CHILDREN_GREY(interp, cur_item);
        GC_IT_MARK_NODE_BLACK(gc_priv_data, cur_item);
        gc_priv_data->total_count++; /* total items since beginning of scan */
        gc_priv_data->item_count++;  /* number of items this increment */
    }
    gc_priv_data->queue = NULL;
}

/*

=item C<static void gc_it_sweep_pmc_pools>

Sweep through the PMC pools, freeing dead objects.

=cut

*/

static void
gc_it_sweep_pmc_pools(PARROT_INTERP)
{
    const Arenas * const arena_base = interp->arena_base;
    Gc_it_data * const gc_priv_data = (Gc_it_data*)arena_base->gc_private;
    /* PMCs need to be handled differently from other types of pools. We'll
       set up lists of our pools here, and handle different types differently. */
    Small_Object_Pool * const pmc_pools[] = {
        arena_base->pmc_pool,
        arena_base->constant_pmc_pool
    };
    register UINTVAL i;
    for(i = 0; i < 2; i++) {
        gc_it_sweep_PMC_arenas(interp, gc_priv_data, pmc_pools[i]);
    }
    /* I'm going to ignore PMC_EXT for now, it has a separate, special
       marking system set up for it already and I dont know that anything
       I do here will improve on that. */
}

/*

=item C<static void gc_it_finalize_all_pmc>

Final GC run, sweep through the pmc pool and call custom destroy VTABLE
methods, if any

=cut

*/

static void
gc_it_finalize_all_pmc(PARROT_INTERP)
{
    const Arenas * const arena_base = interp->arena_base;
    Gc_it_data * const gc_priv_data = (Gc_it_data*)arena_base->gc_private;
    /* PMCs need to be handled differently from other types of pools. We'll
       set up lists of our pools here, and handle different types differently. */
    Small_Object_Pool * const pmc_pools[] = {
        arena_base->pmc_pool,
        arena_base->constant_pmc_pool
    };
    register UINTVAL i;
    for(i = 0; i < 2; i++) {
        gc_it_finalize_PMC_arenas(interp, gc_priv_data, pmc_pools[i]);
    }
}

/*

=item C<static void gc_it_finalize_PMC_arenas>

In a particular PMC pool, run through all arenas and call custom finalization
methods of all live PMCs, if any.

I need to rework this whole function, but it's a good placeholder for now

=cut

*/

static void
gc_it_finalize_PMC_arenas(PARROT_INTERP, ARGMOD(Gc_it_data* gc_priv_data), 
    ARGMOD(Small_Object_Pool *pool))
{
    Small_Object_Arena * arena;
    INTVAL index;
    Gc_it_hdr * hdr;
    for (arena = pool->last_Arena; arena; arena = arena->prev) {
        for(index = arena->total_objects - 1; index >= 0; index--) {
            hdr = GC_IT_HDR_FROM_INDEX(pool, arena, index);
            if(hdr->next == NULL) {
                Parrot_dod_free_pmc(interp, pool, IT_HDR_to_PObj(hdr));
            }
        }
    }
}

/*

=item C<static void gc_it_sweep_header_pools>

Sweep through the header pools, freeing dead objects.

=cut

*/

static void
gc_it_sweep_header_pools(PARROT_INTERP)
{
    const Arenas * const arena_base = interp->arena_base;
    Gc_it_data * const gc_priv_data = (Gc_it_data*)arena_base->gc_private;
    Small_Object_Pool * const header_pools[] = {
        arena_base->string_header_pool,
        arena_base->buffer_header_pool,
        arena_base->constant_string_header_pool
    };
    register UINTVAL i;
    for(i = 0; i < 3; i++) {
        gc_it_sweep_header_arenas(interp, gc_priv_data, header_pools[i]);
    }
}

/*

=item C<static void gc_it_sweep_sized_pools>

Sweep through the sized pools, freeing dead objects.

=cut

*/

static void
gc_it_sweep_sized_pools(PARROT_INTERP)
{
    const Arenas * const arena_base = interp->arena_base;
    Gc_it_data * const gc_priv_data = (Gc_it_data*)arena_base->gc_private;
    register INTVAL i;
    for(i = arena_base->num_sized - 1; i >= 0; i--) {
        Small_Object_Pool * const pool = arena_base->sized_header_pools[i];
        if(pool)
#define gc_it_sweep_sized_arenas(i, d, p) gc_it_sweep_header_arenas(i, d, p)
            gc_it_sweep_sized_arenas(interp, gc_priv_data, pool);
    }
}
/*

=item C<static void gc_it_sweep_PMC_arenas>

If the pool contains PMCs, we sweep through it. When a dead object is found,
we call C<Parrot_dod_free_pmc> on it. This should, in theory, kill the PMC
and clean up all it's dependencies. After the PMC is dead, we add it to the
pool's free list.

This function uses Duff's device magic for partial loop unrolling. We'll
start at the end of the card, and mark forward. Duff's device is not
necessarily the fastest way to unroll most loops, and it may interfere
with branch prediction. However, I think it makes the most sense here,
considering the layout of our flags.

See L<http://en.wikipedia.org/wiki/Duff%27s_device> for more details.

=cut

*/

static void
gc_it_sweep_PMC_arenas(PARROT_INTERP, ARGMOD(Gc_it_data *gc_priv_data),
    ARGMOD(Small_Object_Pool *pool))
{
    /* Go through each arena in the pool, free objects marked white,
       set black cards to white, and call finalization routines, if
       needed. */
    Small_Object_Arena * arena;
    Gc_it_card * card;
    register UINTVAL i;
    for (arena = pool->last_Arena; arena; arena = arena->prev) {
        card = &(arena->cards[arena->card_info._d.card_size]);
        PARROT_ASSERT(card);
        i = arena->card_info._d.last_index;

        switch (arena->card_info._d.last_index % 4) {
            Gc_it_hdr * hdr;
            case 0:
                do {
                    if(card->_f.flag4 == GC_IT_CARD_WHITE) {
                        /* Get a pointer to the object header from it's index */
                        hdr = GC_IT_HDR_FROM_INDEX(pool, arena, i);
                        /* add the header to the free list */
                        GC_IT_ADD_TO_FREE_LIST(pool, hdr);
                        /* free the PMC */
                        Parrot_dod_free_pmc(interp, pool, IT_HDR_to_PObj(hdr));
                        /* mark the card as "FREE" */
                        card->_f.flag4 = GC_IT_CARD_FREE;
                    }
                    else if(card->_f.flag4 == GC_IT_CARD_BLACK)
                        /* if it's black, reset it to white for the next run */
                        card->_f.flag4 = GC_IT_CARD_WHITE;
                    /* move to the next index value, and fall through */
                    i--;
            case 3:
                    if(card->_f.flag3 == GC_IT_CARD_WHITE) {
                        hdr = GC_IT_HDR_FROM_INDEX(pool, arena, i);
                        GC_IT_ADD_TO_FREE_LIST(pool, hdr);
                        Parrot_dod_free_pmc(interp, pool, IT_HDR_to_PObj(hdr));
                        card->_f.flag3 = GC_IT_CARD_FREE;
                    }
                    else if(card->_f.flag3 == GC_IT_CARD_BLACK)
                        card->_f.flag3 = GC_IT_CARD_WHITE;
                    i--;
            case 2:
                    if(card->_f.flag2 == GC_IT_CARD_WHITE) {
                        hdr = GC_IT_HDR_FROM_INDEX(pool, arena, i);
                        GC_IT_ADD_TO_FREE_LIST(pool, hdr);
                        Parrot_dod_free_pmc(interp, pool, IT_HDR_to_PObj(hdr));
                        card->_f.flag2 = GC_IT_CARD_FREE;
                    }
                    else if(card->_f.flag2 == GC_IT_CARD_BLACK)
                        card->_f.flag2 = GC_IT_CARD_WHITE;
                    i--;
            case 1:
            default:
                    if(card->_f.flag1 == GC_IT_CARD_WHITE) {
                        hdr = GC_IT_HDR_FROM_INDEX(pool, arena, i);
                        GC_IT_ADD_TO_FREE_LIST(pool, hdr);
                        Parrot_dod_free_pmc(interp, pool, IT_HDR_to_PObj(hdr));
                        card->_f.flag1 = GC_IT_CARD_FREE;
                    }
                    else if(card->_f.flag1 == GC_IT_CARD_BLACK)
                        card->_f.flag1 = GC_IT_CARD_WHITE;
                    i--;
                } while(card-- != arena->cards);
        }
    }
}

/*

=item C<static void gc_it_sweep_header_arenas>

Sweep through the header pool, and free dead objects. Unlike PMCs, we don't
need to kill the dead object first (that i'm aware of), we just add the
header to the pool's free list.

=cut

*/

static void
gc_it_sweep_header_arenas(PARROT_INTERP, ARGMOD(Gc_it_data *gc_priv_data),
    ARGMOD(Small_Object_Pool *pool))
{
    Small_Object_Arena *arena;
    Gc_it_card *card;
    Gc_it_hdr *hdr;
    register UINTVAL i;
    for (arena = pool->last_Arena; arena; arena = arena->prev) {
        card = &(arena->cards[arena->card_info._d.card_size]);
        PARROT_ASSERT(card);
        i = arena->card_info._d.last_index;
        /* Partially unroll the loop with Duff's device, do 4 items at a time. */
        switch (arena->card_info._d.last_index % 4) {
            case 0:
                do {
                    if(card->_f.flag4 == GC_IT_CARD_WHITE) {
                        hdr = GC_IT_HDR_FROM_INDEX(pool, arena, i);
                        GC_IT_ADD_TO_FREE_LIST(pool, hdr);
                        card->_f.flag4 = GC_IT_CARD_FREE;
                    }
                    else if(card->_f.flag4 == GC_IT_CARD_BLACK)
                        card->_f.flag4 = GC_IT_CARD_WHITE;
                    i--;
            case 3:
                    if(card->_f.flag3 == GC_IT_CARD_WHITE) {
                        hdr = GC_IT_HDR_FROM_INDEX(pool, arena, i);
                        GC_IT_ADD_TO_FREE_LIST(pool, hdr);
                        card->_f.flag3 = GC_IT_CARD_FREE;
                    }
                    else if(card->_f.flag3 == GC_IT_CARD_BLACK)
                        card->_f.flag3 = GC_IT_CARD_WHITE;
                    i--;
            case 2:
                    if(card->_f.flag2 == GC_IT_CARD_WHITE) {
                        hdr = GC_IT_HDR_FROM_INDEX(pool, arena, i);
                        GC_IT_ADD_TO_FREE_LIST(pool, hdr);
                        card->_f.flag2 = GC_IT_CARD_FREE;
                    }
                    else if(card->_f.flag2 == GC_IT_CARD_BLACK)
                        card->_f.flag2 = GC_IT_CARD_WHITE;
                    i--;
            case 1:
            default:
                    if(card->_f.flag1 == GC_IT_CARD_WHITE) {
                        hdr = GC_IT_HDR_FROM_INDEX(pool, arena, i);
                        GC_IT_ADD_TO_FREE_LIST(pool, hdr);
                        card->_f.flag1 = GC_IT_CARD_FREE;
                    }
                    else if(card->_f.flag1 == GC_IT_CARD_BLACK)
                        card->_f.flag1 = GC_IT_CARD_WHITE;
                    i--;
                } while(card-- != arena->cards);
        }
    }
}
#endif

/*

=item C<void gc_it_trace_threaded>

If the GC is running in multithreaded mode, we do whatever we need to do
in that situation. This is not implemented. Here are some ideas of what we
could do:

1) We have a GC thread which is persistent. In that case, this function will
do nothing, and that thread will run continuously in the background doing it's
thing.
2) We launch child threads every time this function is called. For each child
thread, we enqueue a single root (probably as a thread function parameter)
and run the thread to completion. The GC thread will trace through it's queue
entirely, and will terminate when it's queue has become empty. When all child
threads have terminated, and when all root queue items have been scanned, we
move on to the sweep phase.
3) Same as #2, but instead of blindly launching a child thread every time this
function is called, we only launch up to a finite number of threads. If we
have too many threads running already, we do not launch another one here.

=cut

*/

#if GC_IT_PARALLEL_MODE
void
gc_it_trace_threaded(SHIM_INTERP)
{

}

/*

=item C<void gc_it_mark_threaded>

Run one thread's worth of the trace algorithm, as discussed in the function
documentation of C<gc_it_trace_threaded>

=cut

*/

void
gc_it_mark_threaded(SHIM_INTERP)
{

}
#endif

/*

=item C<static void gc_it_enqueue_all_roots>

"batch mode" is a mode where the GC performs a complete stop-the-world
mark phase, instead of the incremental behaviour which is the default.

Moves all items from the root queue into the ordinary queue. If the queue
is not empty, we run a trace first to mark all items on the queue already.

=cut

*/

#if GC_IT_BATCH_MODE
PARROT_INLINE
static void
gc_it_enqueue_all_roots(PARROT_INTERP)
{
    Gc_it_data * const gc_priv_data = (Gc_it_data*)interp->arena_base->gc_private;
    if(gc_priv_data->queue != NULL)
        gc_it_trace_normal(interp);
    PARROT_ASSERT(gc_priv_data->queue == NULL);
    gc_priv_data->queue       = gc_priv_data->root_queue;
    gc_priv_data->root_queue  = NULL;
}
#endif

#if GC_IT_INCREMENT_MODE
/*

=item C<static void gc_it_enqueue_next_root>

In normal incremental mode, we add a single item from the root queue onto
the ordinary queue. However, we only add aggregate items: non-aggregate
root items are marked immediately and discarded. We don't want to waste
an entire GC increment marking a single item.

=cut

*/

static void
gc_it_enqueue_next_root(PARROT_INTERP)
{
    Gc_it_data * const gc_priv_data = (Gc_it_data*)interp->arena_base->gc_private;
    Gc_it_hdr * hdr = gc_priv_data->root_queue;
    PARROT_ASSERT(hdr);

    while(gc_priv_data->root_queue != NULL) {
        gc_priv_data->root_queue = hdr->next;
        if(PObj_is_PMC_TEST(IT_HDR_to_PObj(hdr))) {
            /* add the item to the queue. return */
            GC_IT_ADD_TO_QUEUE(gc_priv_data, hdr);
            return;
        }
        else {
            /* mark the buffer immediately, set the header to float, grab the
               next item from the root_queue */
            gc_it_set_card_mark(hdr, GC_IT_CARD_BLACK);
            hdr->next = NULL;
            hdr = gc_priv_data->root_queue;
        }
    }
    /* If we've fallen through here, that means there are no more root objects,
       no more objects to mark, and we move on to the next stage. Notice
       that there may be items in the regular queue, added by Parrot explicitly
       between increments. Those still need to be traced, if any. */
    PARROT_ASSERT(gc_priv_data->root_queue == NULL);
}
#endif

/*

=item C<static void gc_it_mark_PObj_children_grey>

Mark the children of the current pmc node grey. "Children" can be data, or
metadata, and may be in several places. We need to search around to see
what children there are, and add all of them to the queue.

Places to search (for PMCs):
1) C<PMC_metadata(obj)>
2) C<obj->real_self>
3) C<PMC_next_for_GC(obj)>
4) all sorts of other places, so if the PMC is special, we have to
C<mark_special> it.

For all PObjs:
1) PObj data, if C<PObj_data_is_PMC_array_FLAG>

For strings:
1) Memory pool buffer that contains the actual string data

Also, if C<PObj_custom_mark_TEST(obj)>, we have to call the custom mark
vtable function. Hopefully, all PMC mark VTABLE functions call
C<pobject_lives> and don't try to monkey around with the PObj flags directly.

Notice that the function C<src/gc/dod.c:mark_special> already marks some
children grey inside the call to C<pobject_lives>.

=cut

*/

PARROT_INLINE
static void
gc_it_mark_PObj_children_grey(PARROT_INTERP, ARGMOD(Gc_it_hdr * hdr))
{
    /* Add all children of the current node to the queue for processing. */
    PObj * const obj = IT_HDR_to_PObj(hdr);
    PARROT_ASSERT(hdr);
    PARROT_ASSERT(obj);
    if(PObj_is_PMC_TEST(obj)) {
        if(PMC_metadata((PMC*)obj))
            /* add the metadata PMC, if it exists */
            pobject_lives(interp, (PObj *)PMC_metadata((PMC*)obj));
        if (((PMC*)obj)->real_self != (PMC*)obj)
            /* if the "real self" of the PMC is separate, mark that too. */
            pobject_lives(interp, (PObj*)(((PMC*)obj)->real_self));
        if(PMC_next_for_GC((PMC*)obj) != (PMC*)obj) {
            /* Do whatever we need here */
        }
    }
    else if(PObj_is_STRING_TEST(obj) {
        /* It's a string or a const-string, or whatever. Deal with that
           here. */
    }
    /* if the PMC is an array of other PMCs, we cycle through those. I'm
       surprised if this isn't covered by VTABLE_mark, but I won't question
       it now. */
    if(obj->flags & PObj_data_is_PMC_array_FLAG)
        Parrot_dod_trace_pmc_data(interp, (PMC*)obj);
    /* if it's a PMC with a custom mark routine, call that here. The
       custom mark routine will call pobject_lives on the children,
       which will add them to the queue properly. */
    if(PObj_custom_mark_TEST(obj))
        VTABLE_mark(interp, (PMC*)obj);

    /* If the item is shared, we need to do some magic trickery with it. I
       don't know if I'm going to do said trickery here, or offload it to a
       function like src/gc/dod.c:mark_special (which is where some of the
       other logic in this function originated) */
}

/*

=item C<PARROT_INLINE static void gc_it_mark_buffer_children_grey>

Marks children nodes of the buffer as being

=cut

*/

PARROT_INLINE
static void
gc_it_mark_buffer_children_grey(PARROT_INTERP, ARGMOD(Gc_it_hdr * hdr))
{
}

/*

=item C<void Parrot_gc_it_deinit>

Kill the GC and reset everything.

1) Free all generation structures
2) Free all GC headers in all pools and arenas, if possible
3) Free any additional memory that i will create in the future

=cut

*/

PARROT_API
void
Parrot_gc_it_deinit(PARROT_INTERP)
{
    Arenas * const arena_base = interp->arena_base;

    mem_sys_free(arena_base->gc_private);
    arena_base->gc_private        = NULL;
    /* Null-out the function pointers, except the init pointer
       who knows? the interp might want to load us up again. */
    arena_base->do_gc_mark         = NULL;
    arena_base->finalize_gc_system = NULL;
    arena_base->init_pool          = NULL;
}

/*

=item C<void Parrot_gc_it_pool_init>

Initialize a new memory pool. Set the pointers to the necessary functions,
and set the size of the objects to include the GC header.

=cut

*/

PARROT_API
void
Parrot_gc_it_pool_init(PARROT_INTERP, ARGMOD(Small_Object_Pool *pool)) 
{
    /* Set up function pointers for pool. */
    pool->add_free_object = gc_it_add_free_object;
    pool->get_free_object = gc_it_get_free_object;
    pool->alloc_objects   = gc_it_alloc_objects;
    pool->more_objects    = gc_it_more_objects;

    /* Increase allocated space to account for GC header */
    pool->object_size += sizeof (Gc_it_hdr);
}

/*

=item C<void gc_it_add_free_object>

Adds a dead item to the free list. I suppose this is for cases where other
systems are trying to manage their own memory manually.

I don't really know what this is for, so I'm going to wing it.

=cut

*/

PARROT_API
void
gc_it_add_free_object(PARROT_INTERP, ARGMOD(struct Small_Object_Pool *pool),
    ARGMOD(void *to_add))
{
    Gc_it_hdr * const hdr = PObj_to_IT_HDR(to_add);
    GC_IT_ADD_TO_FREE_LIST(pool, hdr);
    gc_it_set_card_mark(hdr, GC_IT_CARD_FREE);
}

/*

=item C<void * gc_it_get_free_object>

Get an object from the pool's free list and return a pointer to it.

=cut

*/

PARROT_WARN_UNUSED_RESULT
PARROT_CANNOT_RETURN_NULL
PARROT_API
void *
gc_it_get_free_object(PARROT_INTERP, ARGMOD(struct Small_Object_Pool *pool))
{
    Gc_it_hdr *hdr;

    /* If there are no objects, allocate a new arena */
    hdr = (Gc_it_hdr*)pool->free_list;
    if (hdr == NULL)
        (pool->more_objects)(interp, pool);

    /* pull the first header off the free list */
    GC_IT_POP_HDR_FROM_LIST(pool->free_list, hdr, void*);
    hdr->next = NULL;
    --pool->num_free_objects;

    /* mark the item as black for now, so it doesn't get collected prematurely. */
    gc_it_set_card_mark(hdr, GC_IT_CARD_BLACK);

    /* return pointer to the object from the header */
    return (void*)IT_HDR_to_PObj(hdr);
}

/*

=item C<void gc_it_alloc_objects>

Allocate a new Small_Object_Arena from the OS. Set up the arena as
necessary. The arena contains enough space to house several objects
of the given size, and we allocate locally from these arenas as needed.

The memory block for the arena is allocated large enough to hold not only the
arena's object, but also the C<Small_Object_Arena> structure itself and the
C<Gc_it_card> array for cardmarking. Here's a layout of how things look in
memory:

[ Small_Object_Arena | Cards | ... Objects ... ]

And each object looks like this:

[ Gc_it_hdr | Data ]

This kind of layout requires a few extra pointer operations, which is
obnoxious, but it saves on fewer allocations and making better use of memory
locality. Once everything gets set up, macros and cached pointers hide all
the initialization nastyness.

=cut

*/

PARROT_API
void
gc_it_alloc_objects(PARROT_INTERP, ARGMOD(struct Small_Object_Pool *pool))
{
    const size_t real_size = pool->object_size;
    const size_t num_objects = pool->objects_per_alloc;
    const size_t card_size = (num_objects / 4 + ((num_objects % 4) ? (1) : (0)));
    size_t size = real_size * pool->objects_per_alloc + /* the stuff */
                  sizeof(Small_Object_Arena) + /* for the arena struct */
                  card_size * sizeof(Gc_it_card); /* for the card */

    Small_Object_Arena * const new_arena = (Small_Object_Arena*)mem_internal_allocate(size);
    new_arena->card_info._d.card_size = card_size;
    new_arena->card_info._d.last_index = num_objects - 1;
    new_arena->parent_pool = pool;

    /* ...the downside is this messy pointer arithmetic. */
    new_arena->cards = ((Gc_it_card*) ((Small_Object_Arena*)new_arena) + 1);
    new_arena->start_objects = (void*) (((Gc_it_card*)(new_arena->cards)) + card_size);
    memset(new_arena->cards, GC_IT_CARD_ALL_NEW, card_size);

    /* insert new_arena in pool's arena linked list */
    Parrot_append_arena_in_pool(interp, pool, new_arena, real_size * pool->objects_per_alloc);

    /* Add all these new objects we've created into the pool's free list */
    gc_it_add_arena_to_free_list(interp, pool, new_arena);

    /* allocate more next time */
    pool->objects_per_alloc = (UINTVAL) pool->objects_per_alloc *
        UNITS_PER_ALLOC_GROWTH_FACTOR;
    size = real_size * pool->objects_per_alloc;
    if (size > POOL_MAX_BYTES) {
        pool->objects_per_alloc = POOL_MAX_BYTES / real_size;
    }
}

/*

=item C<static void gc_it_add_arena_to_free_list>

Take a newly allocated arena structure, and add all of it's new objects to
the pool's free list. We start at the beginning of the arena's memory block
and do the following steps:

1) add the current object to the free list
2) initialize the C<parent_arena> and C<index> fields of the object, for fast
   lookup later.
3) calculate the address of the next GC header in the arena. This is the part
   that requires pointer dark magic, and is likely the source of bugs.
4) set the C<next> field of the current object to the address of the
   next object, which we've just calculated in #3 above. Update the current
   object pointer to point to the next item.
5) repeat for all items in the arena

=cut

*/

static void
gc_it_add_arena_to_free_list(PARROT_INTERP, 
    ARGMOD(Small_Object_Pool *pool), ARGMOD(Small_Object_Arena *new_arena))
{
    Gc_it_hdr * p = (Gc_it_hdr*)new_arena->start_objects;
    Gc_it_hdr * temp;
    register UINTVAL i;
    const size_t num_objs = new_arena->total_objects;

    for(i = 0; i < num_objs - 1; i++) {
        /* Add the current item to the free list */
        GC_IT_ADD_TO_FREE_LIST(pool, p);

        /* Cache the object's parent pool and card addresses */
        p->parent_arena = new_arena;
        p->index.num.card = i / 4;
        p->index.num.flag = i % 4;

        /* Find the next item in the arena with voodoo pointer magic */
        temp = ((Gc_it_hdr *)p) + 1;
        temp = (Gc_it_hdr *)(((char*)temp) + (pool->object_size));
        p->next = temp;
        p = temp;
    }
    p->next = (Gc_it_hdr*)pool->free_list;
    pool->free_list = new_arena->start_objects;
    pool->num_free_objects += num_objs;
}

/*

=item C<void gc_it_set_card_mark>

Mark the card associated with the given item to the value given by C<flag>.
We've done a lot of value caching, so finding the card is as easy
as a few pointer dereferences and a little bit of algebra. Each card contains
4 flags.

=cut

*/

void
gc_it_set_card_mark(ARGMOD(Gc_it_hdr * hdr), UINTVAL flag)
{
    Gc_it_card * const card = &(hdr->parent_arena->cards[hdr->index.num.card]);
    PARROT_ASSERT(flag < 4);
    switch (hdr->index.num.flag) {
        case 0:
            card->_f.flag1 = flag;
            break;
        case 1:
            card->_f.flag2 = flag;
            break;
        case 2:
            card->_f.flag3 = flag;
            break;
        case 3:
            card->_f.flag3 = flag;
            break;
        default:
            break;
            /* This needs to be better, throw an exception or something. */
    }
}

/*

=item C<UINTVAL gc_it_get_card_mark>

Return the current flag value associated with the given object header.

=cut

*/

PARROT_WARN_UNUSED_RESULT
UINTVAL
gc_it_get_card_mark(ARGMOD(Gc_it_hdr * hdr))
{
    const Gc_it_card * const card = &(hdr->parent_arena->cards[hdr->index.num.card]);
    switch (hdr->index.num.flag) {
        case 0:
            return card->_f.flag1;
        case 1:
            return card->_f.flag2;
        case 2:
            return card->_f.flag3;
        case 3:
            return card->_f.flag4;
        default:
            /* This needs to be better, throw an exception or something. */
            return 0;
    }
}

/*

=item C<void gc_it_more_objects>

Try to allocate new objects. If the mark phase is finished, run a quick sweep.
If the sweep frees up some objects, return one of those. Otherwise, we allocate
a new arena and return an object from that.

=cut

*/

PARROT_API
void
gc_it_more_objects(PARROT_INTERP, ARGMOD(Small_Object_Pool *pool))
{
    const Gc_it_data * const gc_priv_data = (Gc_it_data*)interp->arena_base->gc_private;
    const Gc_it_state state = gc_priv_data->state;
    if(state == GC_IT_SWEEP_PMCS || state == GC_IT_SWEEP_HEADERS || state == GC_IT_SWEEP_BUFFERS) {
        /* Do a complete sweep now, go through all sweep increments, look for
           dead objects, whatever. I'll make a function to do that. */
        if(pool->free_list != NULL)
            return;
    }
    gc_it_alloc_objects(interp, pool);
}

/*

=item C<static void gc_it_post_sweep_cleanup>

Cleanup the GC system after we've completed an entire mark and sweep.
Currently, no cleanup is needed, so this function does nothing.

=cut

*/

static void
gc_it_post_sweep_cleanup(SHIM_INTERP)
{
}

#define GC_IT_PTR_HAS_PARENT_POOL(ptr, pool) \
    (PObj_to_IT_HDR(ptr)->parent_arena->parent_pool == (pool))
#define GC_IT_HDR_HAS_PARENT_POOL(hdr, pool) \
    ((hdr)->parent_arena->parent_pool == (pool))

/*

=item C<int gc_it_ptr_is_pmc>

Determines whether a given pointer is a PMC object from the PMC pool.
Returns C<1> if so, C<0> otherwise.

=item C<int gc_it_hdr_is_pmc>

Determines whether the given C<Gc_it_hdr> structure is located in the PMC
pool. Returns C<1> if so, C<0> otherwise.

=item C<int gc_it_ptr_is_pmc_ext>

=item C<static int gc_it_hdr_is_pmc_ext>

=cut

*/

int
gc_it_ptr_is_pmc(PARROT_INTERP, void * ptr)
{
    return GC_IT_PTR_HAS_PARENT_POOL(ptr, interp->arena_base->pmc_pool);
}

static int
gc_it_hdr_is_pmc(PARROT_INTERP, Gc_it_hdr * hdr)
{
    return GC_IT_HDR_HAS_PARENT_POOL(hdr, interp->arena_base->pmc_pool);
}

int
gc_it_ptr_is_pmc_ext(PARROT_INTERP, void * ptr)
{
    return GC_IT_PTR_HAS_PARENT_POOL(ptr, interp->arena_base->pmc_ext_pool);
}

static int
gc_it_hdr_is_pmc_ext(PARROT_INTERP, Gc_it_hdr * hdr)
{
    return GC_IT_HDR_HAS_PARENT_POOL(hdr, interp->arena_base->pmc_ext_pool);
}

/*

=item C<int gc_it_ptr_is_const_pmc>

Determines whether a given pointer is a constant PMC object from the
const_pmc pool. Returns C<1> if so, C<0> otherwise.

=item C<int gc_it_hdr_is_const_pmc>

Determines whether the given C<Gc_it_hdr> structure is located in the
const PMC pool.

=cut

*/

int
gc_it_ptr_is_const_pmc(PARROT_INTERP, void * ptr)
{
    return GC_IT_PTR_HAS_PARENT_POOL(ptr, interp->arena_base->const_pmc_pool);
}

static int
gc_it_hdr_is_const_pmc(PARROT_INTERP, Gc_it_hdr *)
{
    return GC_IT_HDR_HAS_PARENT_POOL(hdr, interp->arena_base->const_pmc_pool);
}

/*

=item C<int gc_it_ptr_is_any_pmc>

Determines whether a given pointer is a PMC or a constant PMC object from
the pmc pool or the const_pmc pool respectively. Returns C<1> if so, C<0>
otherwise.

=item C<int gc_it_hdr_is_any_pmc>

Determines whether the given C<Gc_it_hdr> is any kind of PMC, from either
the regular PMC pool, or the constant PMC pool.

=item C<int gc_it_hdr_is_PObj_compatible>

Determines whether the given header is a data object that shares isomorphism
with PObjs. If so, we can treat the object as a PObj, and read flags from it
as normal. Otherwise, it's a plane non-aggregate buffer and can be treated
as such.

=cut

*/

int
gc_it_ptr_is_any_pmc(PARROT_INTERP, void * ptr)
{
    /* Whichever one is more common should go first here, to take advantage
       of the short-circuiting OR operation. */
    return GC_IT_PTR_HAS_PARENT_POOL(ptr, interp->arena_base->pmc_pool) ||
           GC_IT_PTR_HAS_PARENT_POOL(ptr, interp->arena_base->const_pmc_pool);
}

static int
gc_it_hdr_is_any_pmc(PARROT_INTERP, Gc_it_hdr * hdr)
{
    /* Whichever one is more common should go first here, to take advantage
       of the short-circuiting OR operation. */
    return GC_IT_HDR_HAS_PARENT_POOL(hdr, interp->arena_base->pmc_pool) ||
           GC_IT_HDR_HAS_PARENT_POOL(hdr, interp->arena_base->const_pmc_pool);
}

static int
gc_it_hdr_is_PObj_compatible(PARROT_INTERP, Gc_it_hdr * hdr)
{
    /* Arrange these in order of most common to least common, to take
       advantage of short-circuiting. */
    return GC_IT_HDR_HAS_PARENT_POOL(hdr, interp->arena_base->pmc_pool) ||
           GC_IT_HDR_HAS_PARENT_POOL(hdr, interp->arena_base->const_pmc_pool) ||
           GC_IT_HDR_HAS_PARENT_POOL(hdr, interp->arena_base->string_header_pool) ||
           GC_IT_HDR_HAS_PARENT_POOL(hdr, interp->arena_base->const_string_header_pool);
}

/*

=item C<Small_Object_Pool * gc_it_ptr_is_sized_buffer>

Determines whether a given pointer is located in one of the sized header
pools. We loop over all these pools to determine if the pointer is in
any of them. Returns a pointer to the pool that the object is found in,
or returns C<NULL> if it is not found in any pools.

=cut

*/


Small_Object_Pool *
gc_it_ptr_is_sized_buffer(PARROT_INTERP, void * ptr)
{
    register INTVAL i = 0;
    for(i = interp->arena_base->num_sized; i >= 0; i--) {
        if(gc_it_ptr_has_parent_pool(ptr, interp->arena_base->sized_pools[i]))
            return interp->arena_base->sized_pools[i];
    }
    return NULL;
}

#endif  /* PARROT_GC_IT */


/*

=head1 HISTORY

Initial version by Whiteknight (2008.05.26)

=cut

*/

/*
 * Local variables:
 *   c-file-style: "parrot"
 * End:
 * vim: expandtab shiftwidth=4:
 */
