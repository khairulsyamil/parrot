/*
Copyright: 2003 The Perl Foundation.  All Rights Reserved.
$Id$

=head1 NAME

src/mmd.c - Multimethod dispatch for binary opcode functions

=head1 SYNOPSIS

This system is set up to handle type-based dispatching for binary (i.e.
two-arg) functions. This includes, though isn't necessarily limited to,
binary operators such as addition or subtraction.

=head1 DESCRIPTION

The MMD system is straightforward, and currently must be explicitly
invoked, for example by a vtable function. (We may reserve the right to
use MMD in all circumstances, but currently do not).

=head2 API

For the purposes of the API, each MMD-able function is assigned a unique
number which is used to find the correct function table. This is the
C<func_num> parameter in the following functions. While Parrot isn't
restricted to a predefined set of functions, it I<does> set things up so
that all the binary vtable functions have a MMD table preinstalled for
them, with default behaviour.

=head2 Remarks

C<< binop_mmd_funcs->x >> and C<< ->y >> are table sizes
not highest type in table.

=head2 Functions

=over 4

=cut

*/

#include "parrot/parrot.h"
#include <assert.h>

typedef void (*pmc_mmd_f)(Interp *, PMC *, PMC *, PMC *);
typedef STRING *(*string_mmd_f)(Interp *, PMC *, PMC *);
typedef INTVAL (*intval_mmd_f)(Interp *, PMC *, PMC *);
typedef FLOATVAL (*floatval_mmd_f)(Interp *, PMC *, PMC *);

#ifndef NDEBUG
static void
dump_mmd(Interp *interpreter, INTVAL function)
{
    UINTVAL x, y;
    UINTVAL offset, x_funcs, y_funcs;
    MMD_table *table = interpreter->binop_mmd_funcs;
    funcptr_t func, def;

    x_funcs = table->x[function];
    y_funcs = table->y[function];
    def = table->default_func[function];
    if (!def) {
        printf("default for %d not registered\n", (int)function);
        return;
    }
    printf("    ");
    for (x = 0; x < x_funcs; ++x) {
        if (! (x % 10))
            printf("%d", (int) x / 10);
        else
            printf(" ");
    }
    printf("\n");
    for (y = 0; y < y_funcs; ++y) {
        printf("%3d ", (int)y);
        for (x = 0; x < x_funcs; ++x) {
            offset = x_funcs * y + x;
            func = table->mmd_funcs[function][offset];
            printf("%c",
                    func == def ?  '.' :
                    (UINTVAL)func & 1 ?  'P' :
                    !func  ? '0' : 'F');
        }
        printf("\n");
    }
    for (y = 0; y < y_funcs; ++y) {
        for (x = 0; x < x_funcs; ++x) {
            offset = x_funcs * y + x;
            func = table->mmd_funcs[function][offset];
            if (func && func != def && !((UINTVAL) func & 1))
                printf("%3d %3d: %p\n", (int)x, (int)y, (void*) func);
        }
    }
}
#endif

static funcptr_t
get_mmd_dispatch_type(Interp *interpreter, UINTVAL left_type,
        UINTVAL right_type, INTVAL function, int *is_pmc)
{
    funcptr_t func;
    UINTVAL offset, x_funcs, y_funcs;
    MMD_table *table = interpreter->binop_mmd_funcs;
    x_funcs = table->x[function];
    y_funcs = table->y[function];

    if (left_type < x_funcs) {
        if (right_type < y_funcs) {
            offset = x_funcs * right_type + left_type;
            func = table->mmd_funcs[function][offset];
        }
        else {
            func = table->mmd_funcs[function][left_type];
        }
    } else {
        func = table->default_func[function];
    }
    /*
     * empty slots are filled with the default function, so we really
     * shouldn't have a NULL function pointer
     */
    assert(func);
#ifdef PARROT_HAS_ALIGNED_FUNCPTR
    if ((UINTVAL)func & 1) {
        *is_pmc = 1;
        func = (funcptr_t)((UINTVAL)func & ~1);
    }
    else {
        *is_pmc = 0;
    }
    return func;
#else
    {
        void *sub = (void*)((UINTVAL)func & ~1);
        if (is_pmc_ptr(interpreter, sub)) {
            *is_pmc = 1;
            return (funcptr_t) sub;
        }
        else {
            *is_pmc = 0;
        }
        return func;
    }
#endif
}


static funcptr_t
get_mmd_dispatcher(Interp *interpreter, PMC *left, PMC * right,
        INTVAL function, int *is_pmc)
{
    UINTVAL left_type, right_type;
    left_type = VTABLE_type(interpreter, left);
    right_type = VTABLE_type(interpreter, right);
    return get_mmd_dispatch_type(interpreter, left_type, right_type,
            function, is_pmc);
}

/*

=item C<void
mmd_dispatch_pmc(Interp *interpreter,
		 PMC *left, PMC *right, PMC *dest, INTVAL function)>

Dispatch to a multimethod that "returns" a PMC. C<left>, C<right>, and
C<dest> are all PMC pointers, while C<func_num> is the MMD table that
should be used to do the dispatching.

The MMD system will figure out which function should be called based on
the types of C<left> and C<right> and call it, passing in C<left>,
C<right>, and C<dest> like any other binary vtable function.

This function has a C<void> return type, like all the "take two PMCs,
return a PMC" vtable functions do.

=cut

*/

void
mmd_dispatch_pmc(Interp *interpreter,
		 PMC *left, PMC *right, PMC *dest, INTVAL function)
{
    pmc_mmd_f real_function;
    PMC *sub;
    int is_pmc;

    real_function = (pmc_mmd_f)get_mmd_dispatcher(interpreter,
            left, right, function, &is_pmc);

    if (is_pmc) {
        sub = (PMC*)real_function;
        Parrot_runops_fromc_args_save(interpreter, sub, "vPPP",
                left, right, dest);
    }
    else {
        (*real_function)(interpreter, left, right, dest);
    }
}

/*

=item C<STRING *
mmd_dispatch_string(Interp *interpreter,
		 PMC *left, PMC *right, INTVAL function)>

Dispatch to a multimethod that returns a string. left and right are PMC
pointers, while C<func_num> is the MMD table that should be used to do the
dispatching. The function is responsible for creating the returned
string.

=cut

*/

STRING *
mmd_dispatch_string(Interp *interpreter,
		 PMC *left, PMC *right, INTVAL function)
{
    string_mmd_f real_function;
    PMC *sub;
    int is_pmc;
    STRING *ret;
    /*
     * XXX actually we don't have a MMD function matching this signature
     * -leo
     */

    real_function = (string_mmd_f)get_mmd_dispatcher(interpreter,
            left, right, function, &is_pmc);

    if (is_pmc) {
        sub = (PMC*)real_function;
        ret = Parrot_runops_fromc_args_save(interpreter, sub, "SPP",
                left, right);
    }
    else {
        ret = (*real_function)(interpreter, left, right);
    }
    return ret;
}

/*

=item C<INTVAL
mmd_dispatch_intval(Interp *interpreter,
		 PMC *left, PMC *right, INTVAL function)>

Like C<mmd_dispatch_string()>, only it returns an C<INTVAL>.

=cut

*/

INTVAL
mmd_dispatch_intval(Interp *interpreter,
		 PMC *left, PMC *right, INTVAL function)
{
    intval_mmd_f real_function;
    PMC *sub;
    int is_pmc;
    INTVAL ret;

    real_function = (intval_mmd_f)get_mmd_dispatcher(interpreter,
            left, right, function, &is_pmc);

    if (is_pmc) {
        sub = (PMC*)real_function;
        ret = Parrot_runops_fromc_args_save_reti(interpreter, sub, "IPP",
                left, right);
    }
    else {
        ret = (*real_function)(interpreter, left, right);
    }
    return ret;
}

/*

=item C<FLOATVAL
mmd_dispatch_floatval(Interp *interpreter,
		 PMC *left, PMC *right, INTVAL function)>

Like C<mmd_dispatch_string()>, only it returns a C<FLOATVAL>.

=cut

*/

FLOATVAL
mmd_dispatch_floatval(Interp *interpreter,
		 PMC *left, PMC *right, INTVAL function)
{

    floatval_mmd_f real_function;
    PMC *sub;
    int is_pmc;
    FLOATVAL ret;

    /*
     * XXX actually we don't have a MMD function matching this signature
     * -leo
     */
    real_function = (floatval_mmd_f)get_mmd_dispatcher(interpreter,
            left, right, function, &is_pmc);

    if (is_pmc) {
        sub = (PMC*)real_function;
        ret = Parrot_runops_fromc_args_save_reti(interpreter, sub, "NPP",
                left, right);
    }
    else {
        ret = (*real_function)(interpreter, left, right);
    }
    return ret;
}

/*

=item C<void
mmd_add_function(Interp *interpreter,
        INTVAL funcnum, funcptr_t function)>

Add a new binary MMD function to the list of functions the MMD system knows
of. C<func_num> is the number of the new function, while C<default_func> is
the function to be called when the system doesn't know which function it
should call. (Because, for example, there hasn't been a function
installed that matches the left and right types for a call).

=cut

*/

void
mmd_add_function(Interp *interpreter,
        INTVAL funcnum, funcptr_t function)
{
    UINTVAL func_count = funcnum + 1;
    UINTVAL cur_func_count = interpreter->binop_mmd_funcs->tables;

    /*    printf("Default for %i is %p\n", funcnum, function); */

    /* Is the new function past where we have expanded to? If so, make
       all the tables bigger
    */
    if (func_count > cur_func_count) {
        UINTVAL *new_x;
        UINTVAL *new_y;
        funcptr_t *new_default;
        UINTVAL *new_func_count;
        funcptr_t **new_functable;

        /* All this stuff should be checked to make sure it succeeds. */
        new_x = mem_sys_allocate_zeroed(sizeof(UINTVAL) * func_count);
        new_y = mem_sys_allocate_zeroed(sizeof(UINTVAL) * func_count);
        new_func_count = mem_sys_allocate_zeroed(sizeof(UINTVAL) * func_count);
        new_default = mem_sys_allocate_zeroed(sizeof(funcptr_t) * func_count);
        new_functable = mem_sys_allocate_zeroed(sizeof(funcptr_t) * func_count);

        /* Now copy the data over */
        memcpy(new_x, interpreter->binop_mmd_funcs->x,
                sizeof(UINTVAL) * cur_func_count);
        memcpy(new_y, interpreter->binop_mmd_funcs->y,
                sizeof(UINTVAL) * cur_func_count);
        memcpy(new_func_count, interpreter->binop_mmd_funcs->funcs_in_table,
                sizeof(UINTVAL) * cur_func_count);
        memcpy(new_default, interpreter->binop_mmd_funcs->default_func,
                sizeof(funcptr_t) * cur_func_count);
        memcpy(new_functable, interpreter->binop_mmd_funcs->mmd_funcs,
                sizeof(funcptr_t) * cur_func_count);

        /* free old if any */
        if (interpreter->binop_mmd_funcs->x)
            mem_sys_free(interpreter->binop_mmd_funcs->x);
        if (interpreter->binop_mmd_funcs->y)
            mem_sys_free(interpreter->binop_mmd_funcs->y);
        if (interpreter->binop_mmd_funcs->funcs_in_table)
            mem_sys_free(interpreter->binop_mmd_funcs->funcs_in_table);
        if (interpreter->binop_mmd_funcs->default_func)
            mem_sys_free(interpreter->binop_mmd_funcs->default_func);
        if (interpreter->binop_mmd_funcs->mmd_funcs)
            mem_sys_free(interpreter->binop_mmd_funcs->mmd_funcs);

        /* And set the values */
        interpreter->binop_mmd_funcs->x = new_x;
        interpreter->binop_mmd_funcs->y = new_y;
        interpreter->binop_mmd_funcs->default_func = new_default;
        interpreter->binop_mmd_funcs->funcs_in_table = new_func_count;
        interpreter->binop_mmd_funcs->mmd_funcs = new_functable;
        interpreter->binop_mmd_funcs->tables = func_count;

    }
    /* We mark the new function by adding in the default function
       pointer */
    interpreter->binop_mmd_funcs->default_func[funcnum] = function;

}

/*

=item C<static void
mmd_expand_x(Interp *interpreter, INTVAL function, INTVAL new_x)>

Expands the function table in the X dimension to include C<new_x>.

=cut

*/

static void
mmd_expand_x(Interp *interpreter, INTVAL function, INTVAL new_x)
{
    funcptr_t *new_table;
    UINTVAL x;
    UINTVAL y;
    funcptr_t default_func;
    UINTVAL i;

    /* Is the Y 0? If so, nothing to expand, so just set the X for
       later use */
    if (interpreter->binop_mmd_funcs->y[function] == 0) {
        interpreter->binop_mmd_funcs->x[function] = new_x;
        return;
    }

    /* The Y is not zero. Bleah. This means we have to expand the
       table in an unpleasant way. */

    x = interpreter->binop_mmd_funcs->x[function];
    y = interpreter->binop_mmd_funcs->y[function];
    default_func = interpreter->binop_mmd_funcs->default_func[function];

    /* First, fill in the whole new table with the default function
       pointer. We only really need to do the new part, but... */
    new_table = mem_sys_allocate(sizeof(funcptr_t) * y * new_x);
    for (i = 0; i < y * new_x; i++) {
        new_table[i] = default_func;
    }

    /* Then copy the old table over. We have to do this row by row,
       because the rows in the old and new tables are different
       lengths */
    for (i = 0; i < y; i++) {
        INTVAL newoffset, oldoffset;
        newoffset = i * new_x;
        oldoffset = i * x;
        memcpy(new_table + newoffset,
               interpreter->binop_mmd_funcs->mmd_funcs[function] + oldoffset,
               sizeof(funcptr_t) * x);
    }
    if (interpreter->binop_mmd_funcs->mmd_funcs[function])
        mem_sys_free(interpreter->binop_mmd_funcs->mmd_funcs[function]);
    interpreter->binop_mmd_funcs->x[function] = new_x;
    /* Set the old table to point to the new table */
    interpreter->binop_mmd_funcs->mmd_funcs[function] = new_table;
}

/*

=item C<static void
mmd_expand_y(Interp *interpreter, INTVAL function, INTVAL new_y)>

Expands the function table in the Y direction.

=cut

*/

static void
mmd_expand_y(Interp *interpreter, INTVAL function, INTVAL new_y)
{
    funcptr_t *new_table;
    UINTVAL x;
    UINTVAL y;
    funcptr_t default_func;
    UINTVAL i;

#if 0
    /* Is the X 0? If so, nothing to expand, so just set the Y for
       later use */
    if (interpreter->binop_mmd_funcs->x[function] == 0) {
        interpreter->binop_mmd_funcs->y[function] = new_y;
        return;
    }
#endif

    x = interpreter->binop_mmd_funcs->x[function];
    y = interpreter->binop_mmd_funcs->y[function];
    default_func = interpreter->binop_mmd_funcs->default_func[function];

    /* First, fill in the whole new table with the default function
       pointer. We only really need to do the new part, but... */
    new_table = mem_sys_allocate(sizeof(funcptr_t) * x * new_y);
    for (i = 0; i < x * new_y; i++) {
        new_table[i] = default_func;
    }

    /* Then copy the old table over, if it existed in the first place. */
    if (interpreter->binop_mmd_funcs->mmd_funcs[function]) {
        memcpy(new_table, interpreter->binop_mmd_funcs->mmd_funcs[function],
               sizeof(funcptr_t) * x * y);
        mem_sys_free(interpreter->binop_mmd_funcs->mmd_funcs[function]);
    }
    interpreter->binop_mmd_funcs->y[function] = new_y;
    interpreter->binop_mmd_funcs->mmd_funcs[function] = new_table;

}

/*

=item C<void
mmd_add_by_class(Interp *interpreter,
             INTVAL functype,
             STRING *left_class, STRING *right_class,
             funcptr_t funcptr)>

Add a function to the MMD table by class name, rather than class number.
Handles the case where the named class isn't loaded yet.

Adds a new MMD function C<funcptr> to the C<func_num> function table
that will be invoked when the left parameter is of class C<left_class>
and the right parameter is of class C<right_class>. Both classes are
C<STRING *>s that hold the PMC class names for the left and right sides.
If either class isn't yet loaded, Parrot will cache the information such
that the function will be installed if at some point in the future both
classes are available.

Currently this is done by just assigning class numbers to the classes,
which the classes will pick up and use if they're later loaded, but we
may later put the functions into a deferred table that we scan when PMC
classes are loaded. Either way, the function will be guaranteed to be
installed when it's needed.

The function table must exist, but if it is too small, it will
automatically be expanded.

=cut

*/

void
mmd_add_by_class(Interp *interpreter,
             INTVAL functype,
             STRING *left_class, STRING *right_class,
             funcptr_t funcptr)
{
    INTVAL left_type = pmc_type(interpreter, left_class);
    INTVAL right_type = pmc_type(interpreter, right_class);

    if (left_type == enum_type_undef) {
        left_type = pmc_register(interpreter, left_class);
    }
    if (right_type == enum_type_undef) {
        right_type = pmc_register(interpreter, right_class);
    }

    mmd_register(interpreter, functype, left_type, right_type, funcptr);

}

/*

=item C<void
mmd_register(Interp *interpreter,
             INTVAL type,
             INTVAL left_type, INTVAL right_type,
             funcptr_t funcptr)>

Register a function C<funcptr> for MMD function table C<func_num> for classes
C<left_type> and C<right_type>. The left and right types are C<INTVAL>s that
represent the class ID numbers.

The function table must exist, but if it is too small, it will
automatically be expanded.

Adding a new function to the table can be interestingly non-trivial, so
we get to be tricky.

If the left or right types are larger than anything we've seen so far,
it means that we have to expand the table. Making Y larger is simple --
just realloc with some more rows. Making X larger is less simple. In
either case, we punt to other functions.

TODO - Currently the MMD system doesn't handle inheritance and best match
searching, as it assumes that all PMC types have no parent type. This
can be considered a bug, and will be resolved at some point in the
future.

=cut

*/

void
mmd_register(Interp *interpreter,
             INTVAL type,
             INTVAL left_type, INTVAL right_type,
             funcptr_t funcptr)
{

    INTVAL cur_x, cur_y;
    INTVAL offset;
    cur_x = interpreter->binop_mmd_funcs->x[type];
    cur_y = interpreter->binop_mmd_funcs->y[type];
    if (cur_x <= left_type) {
        mmd_expand_x(interpreter, type, left_type + 1);
    }

    if (cur_y <= right_type) {
        mmd_expand_y(interpreter, type, right_type + 1);
    }

    offset = interpreter->binop_mmd_funcs->x[type] * right_type + left_type;
    *(interpreter->binop_mmd_funcs->mmd_funcs[type] + offset) = funcptr;
}

void
mmd_register_sub(Interp *interpreter,
             INTVAL type,
             INTVAL left_type, INTVAL right_type,
             PMC *sub)
{
    PMC *fake = (PMC*)((UINTVAL) sub | 1);
    mmd_register(interpreter, type, left_type, right_type, D2FPTR(fake));
}

/*

=item C<void
mmd_destroy(Parrot_Interp interpreter)>

Frees all the memory allocated used the MMD subsystem.

=cut

*/

void
mmd_destroy(Parrot_Interp interpreter)
{
    if (interpreter->binop_mmd_funcs->tables) {
        UINTVAL i;
        for (i = 0; i <interpreter->binop_mmd_funcs->tables; ++i) {
            if (interpreter->binop_mmd_funcs->mmd_funcs[i])
                mem_sys_free(interpreter->binop_mmd_funcs->mmd_funcs[i]);
        }
        mem_sys_free(interpreter->binop_mmd_funcs->mmd_funcs);

        mem_sys_free(interpreter->binop_mmd_funcs->x);
        mem_sys_free(interpreter->binop_mmd_funcs->y);
        mem_sys_free(interpreter->binop_mmd_funcs->default_func);
        mem_sys_free(interpreter->binop_mmd_funcs->funcs_in_table);
    }
    mem_sys_free(interpreter->binop_mmd_funcs);
}


PMC *
mmd_vtfind(Parrot_Interp interpreter, INTVAL type, INTVAL left, INTVAL right) {
    int is_pmc;
    funcptr_t func = get_mmd_dispatch_type(interpreter,
            left, right, type, &is_pmc);
    if (func && is_pmc)
        return (PMC*)F2DPTR(func);
    return PMCNULL;
}

/*

=back

=head1 SEE ALSO

F<include/parrot/mmd.h>.

=cut

*/

/*
 * Local variables:
 * c-indentation-style: bsd
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 *
 * vim: expandtab shiftwidth=4:
*/
