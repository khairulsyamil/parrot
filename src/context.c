/*
Copyright (C) 2001-2009, Parrot Foundation.
$Id$

=head1 NAME

src/context.c - Parrot_Context functions.

=head1 DESCRIPTION

=head2 Functions

=over 4

=cut

*/

#include "parrot/parrot.h"
#include "parrot/context.h"


/* HEADERIZER HFILE: include/parrot/context.h */

/* HEADERIZER BEGIN: static */
/* Don't modify between HEADERIZER BEGIN / HEADERIZER END.  Your changes will be lost. */

/* Don't modify between HEADERIZER BEGIN / HEADERIZER END.  Your changes will be lost. */
/* HEADERIZER END: static */


/*

=item C<STRING* Parrot_cx_get_string_constant(PARROT_INTERP, PMC *ctx, INTVAL
idx)>

Get string constant from context.

=cut

*/

PARROT_EXPORT
PARROT_CAN_RETURN_NULL
STRING*
Parrot_cx_get_string_constant(PARROT_INTERP, ARGIN(PMC *ctx), INTVAL idx)
{
    ASSERT_ARGS(Parrot_cx_get_string_constant)
    Parrot_Context const * c = Parrot_cx_get_context(interp, ctx);
    return c->constants[idx]->u.string;
}


/*

=item C<PMC* Parrot_cx_get_pmc_constant(PARROT_INTERP, PMC *ctx, INTVAL idx)>

Get PMC constant from context.

=cut

*/

PARROT_EXPORT
PARROT_CAN_RETURN_NULL
PMC*
Parrot_cx_get_pmc_constant(PARROT_INTERP, ARGIN(PMC *ctx), INTVAL idx)
{
    ASSERT_ARGS(Parrot_cx_get_pmc_constant)
    Parrot_Context const * c = Parrot_cx_get_context(interp, ctx);
    return c->constants[idx]->u.key;
}


/*

=item C<struct PackFile_Constant ** Parrot_cx_constants(PARROT_INTERP, PMC
*ctx)>

Get reference to constants.

=cut

*/
PARROT_EXPORT
PARROT_CANNOT_RETURN_NULL
struct PackFile_Constant **
Parrot_cx_constants(PARROT_INTERP, ARGIN(PMC *ctx))
{
    ASSERT_ARGS(Parrot_cx_constants)
    return ((Parrot_Context*)(VTABLE_get_pointer(interp, ctx)))->constants;
}



/*

=item C<Parrot_Context* Parrot_cx_get_context(PARROT_INTERP, PMC *ctx)>

Fetch Parrot_Context from Context PMC.

=cut

*/
PARROT_EXPORT
PARROT_CAN_RETURN_NULL
Parrot_Context*
Parrot_cx_get_context(PARROT_INTERP, ARGIN_NULLOK(PMC *ctx))
{
    ASSERT_ARGS(Parrot_cx_get_context)
    if (PMC_IS_NULL(ctx))
        return NULL;

    return (Parrot_Context*)(VTABLE_get_pointer(interp, ctx));
}

/*

=item C<UINTVAL Parrot_cx_get_recursion_depth(PARROT_INTERP, PMC *ctx)>

Get recursion depth from context.

=cut

*/

PARROT_EXPORT
UINTVAL
Parrot_cx_get_recursion_depth(PARROT_INTERP, ARGIN(PMC *ctx))
{
    ASSERT_ARGS(Parrot_cx_get_recursion_depth)
    Parrot_Context *c = Parrot_cx_get_context(interp, ctx);
    return c->recursion_depth;
}

/*

=item C<UINTVAL Parrot_cx_inc_recursion_depth(PARROT_INTERP, PMC *ctx)>

Increase recurtion depth. Returns new recursion_depth value.

=cut

*/

PARROT_EXPORT
UINTVAL
Parrot_cx_inc_recursion_depth(PARROT_INTERP, ARGIN(PMC *ctx))
{
    ASSERT_ARGS(Parrot_cx_inc_recursion_depth)
    Parrot_Context *c = Parrot_cx_get_context(interp, ctx);
    return ++c->recursion_depth;
}

/*

=item C<UINTVAL Parrot_cx_dec_recursion_depth(PARROT_INTERP, PMC *ctx)>

Decrease recurtion depth. Returns new recursion_depth value.

=cut

*/

PARROT_EXPORT
UINTVAL
Parrot_cx_dec_recursion_depth(PARROT_INTERP, ARGIN(PMC *ctx))
{
    ASSERT_ARGS(Parrot_cx_dec_recursion_depth)
    Parrot_Context *c = Parrot_cx_get_context(interp, ctx);
    return --c->recursion_depth;
}

/*

=item C<PMC* Parrot_cx_get_caller_ctx(PARROT_INTERP, PMC *ctx)>

Get caller Context.

=cut

*/

PARROT_EXPORT
PMC*
Parrot_cx_get_caller_ctx(PARROT_INTERP, ARGIN(PMC *ctx))
{
    ASSERT_ARGS(Parrot_cx_get_caller_ctx)
    Parrot_Context *c = Parrot_cx_get_context(interp, ctx);
    return c->caller_ctx;
}


/*

=item C<void Parrot_cx_set_caller_ctx(PARROT_INTERP, PMC *ctx, PMC *caller_ctx)>

Set caller Context.

=cut

*/

PARROT_EXPORT
void
Parrot_cx_set_caller_ctx(PARROT_INTERP, ARGIN(PMC *ctx), ARGIN(PMC *caller_ctx))
{
    ASSERT_ARGS(Parrot_cx_set_caller_ctx)
    Parrot_Context *c = Parrot_cx_get_context(interp, ctx);
    c->caller_ctx = caller_ctx;
}

/*

=item C<PMC* Parrot_cx_get_outer_ctx(PARROT_INTERP, PMC *ctx)>

Get outer Context.

=cut

*/

PARROT_EXPORT
PMC*
Parrot_cx_get_outer_ctx(PARROT_INTERP, ARGIN(PMC *ctx))
{
    ASSERT_ARGS(Parrot_cx_get_outer_ctx)
    Parrot_Context *c = Parrot_cx_get_context(interp, ctx);
    return c->outer_ctx;
}


/*

=item C<void Parrot_cx_set_outer_ctx(PARROT_INTERP, PMC *ctx, PMC *outer_ctx)>

Set outer Context.

=cut

*/

PARROT_EXPORT
void
Parrot_cx_set_outer_ctx(PARROT_INTERP, ARGIN(PMC *ctx), ARGIN(PMC *outer_ctx))
{
    ASSERT_ARGS(Parrot_cx_set_outer_ctx)
    Parrot_Context *c = Parrot_cx_get_context(interp, ctx);
    c->outer_ctx = outer_ctx;
}

/*

=item C<PMC* Parrot_cx_get_lex_pad(PARROT_INTERP, PMC *ctx)>

Get LexPad.

=cut

*/

PARROT_EXPORT
PMC*
Parrot_cx_get_lex_pad(PARROT_INTERP, ARGIN(PMC *ctx))
{
    ASSERT_ARGS(Parrot_cx_get_lex_pad)
    Parrot_Context *c = Parrot_cx_get_context(interp, ctx);
    return c->lex_pad;
}


/*

=item C<void Parrot_cx_set_lex_pad(PARROT_INTERP, PMC *ctx, PMC *lex_pad)>

Set LexPad.

=cut

*/

PARROT_EXPORT
void
Parrot_cx_set_lex_pad(PARROT_INTERP, ARGIN(PMC *ctx), ARGIN(PMC *lex_pad))
{
    ASSERT_ARGS(Parrot_cx_set_lex_pad)
    Parrot_Context *c = Parrot_cx_get_context(interp, ctx);
    c->lex_pad = lex_pad;
}

/*

=item C<PMC* Parrot_cx_get_namespace(PARROT_INTERP, PMC *ctx)>

Get namespace of Context.

=cut

*/

PARROT_EXPORT
PMC*
Parrot_cx_get_namespace(PARROT_INTERP, ARGIN(PMC *ctx))
{
    ASSERT_ARGS(Parrot_cx_get_namespace)
    Parrot_Context *c = Parrot_cx_get_context(interp, ctx);
    return c->current_namespace;
}


/*

=item C<void Parrot_cx_set_namespace(PARROT_INTERP, PMC *ctx, PMC *_namespace)>

Set namespace of Context.

=cut

*/

PARROT_EXPORT
void
Parrot_cx_set_namespace(PARROT_INTERP, ARGIN(PMC *ctx), ARGIN_NULLOK(PMC *_namespace))
{
    ASSERT_ARGS(Parrot_cx_set_namespace)
    Parrot_Context *c = Parrot_cx_get_context(interp, ctx);
    c->current_namespace = _namespace;
}

/*

=item C<INTVAL Parrot_cx_get_HLL(PARROT_INTERP, PMC *ctx)>

Get HLL of Context.

=cut

*/

PARROT_EXPORT
INTVAL
Parrot_cx_get_HLL(PARROT_INTERP, ARGIN(PMC *ctx))
{
    ASSERT_ARGS(Parrot_cx_get_HLL)
    Parrot_Context *c = Parrot_cx_get_context(interp, ctx);
    return c->current_HLL;
}


/*

=item C<void Parrot_cx_set_HLL(PARROT_INTERP, PMC *ctx, INTVAL hll)>

Set HLL of Context.

=cut

*/

PARROT_EXPORT
void
Parrot_cx_set_HLL(PARROT_INTERP, ARGIN(PMC *ctx), INTVAL hll)
{
    ASSERT_ARGS(Parrot_cx_set_HLL)
    Parrot_Context *c = Parrot_cx_get_context(interp, ctx);
    c->current_HLL = hll;
}

/*

=item C<PMC* Parrot_cx_get_continuation(PARROT_INTERP, PMC *ctx)>

Get continuation of Context.

=cut

*/

PARROT_EXPORT
PMC*
Parrot_cx_get_continuation(PARROT_INTERP, ARGIN(PMC *ctx))
{
    ASSERT_ARGS(Parrot_cx_get_continuation)
    Parrot_Context *c = Parrot_cx_get_context(interp, ctx);
    return c->current_cont;
}


/*

=item C<void Parrot_cx_set_continuation(PARROT_INTERP, PMC *ctx, PMC
*_continuation)>

Set continuation of Context.

=cut

*/

PARROT_EXPORT
void
Parrot_cx_set_continuation(PARROT_INTERP, ARGIN(PMC *ctx), ARGIN_NULLOK(PMC *_continuation))
{
    ASSERT_ARGS(Parrot_cx_set_continuation)
    Parrot_Context *c = Parrot_cx_get_context(interp, ctx);
    c->current_cont = _continuation;
}

/*

=item C<PMC* Parrot_cx_get_object(PARROT_INTERP, PMC *ctx)>

Get object of Context (in method call).

=cut

*/

PARROT_EXPORT
PMC*
Parrot_cx_get_object(PARROT_INTERP, ARGIN(PMC *ctx))
{
    ASSERT_ARGS(Parrot_cx_get_object)
    Parrot_Context *c = Parrot_cx_get_context(interp, ctx);
    return c->current_object;
}


/*

=item C<void Parrot_cx_set_object(PARROT_INTERP, PMC *ctx, PMC *object)>

Set object of Context (in method call).

=cut

*/

PARROT_EXPORT
void
Parrot_cx_set_object(PARROT_INTERP, ARGIN(PMC *ctx), ARGIN_NULLOK(PMC *object))
{
    ASSERT_ARGS(Parrot_cx_set_object)
    Parrot_Context *c = Parrot_cx_get_context(interp, ctx);
    c->current_object = object;
}

/*

=item C<PMC* Parrot_cx_get_sub(PARROT_INTERP, PMC *ctx)>

Get Sub executed inside Context.

=cut

*/

PARROT_EXPORT
PMC*
Parrot_cx_get_sub(PARROT_INTERP, ARGIN(PMC *ctx))
{
    ASSERT_ARGS(Parrot_cx_get_sub)
    Parrot_Context *c = Parrot_cx_get_context(interp, ctx);
    return c->current_sub;
}


/*

=item C<void Parrot_cx_set_sub(PARROT_INTERP, PMC *ctx, PMC *sub)>

Set Sub executed inside Context.

=cut

*/

PARROT_EXPORT
void
Parrot_cx_set_sub(PARROT_INTERP, ARGIN(PMC *ctx), ARGIN_NULLOK(PMC *sub))
{
    ASSERT_ARGS(Parrot_cx_set_sub)
    Parrot_Context *c = Parrot_cx_get_context(interp, ctx);
    c->current_sub = sub;
}

/*

=item C<opcode_t* Parrot_cx_get_pc(PARROT_INTERP, PMC *ctx)>

Get program counter of Sub invocation.

=cut

*/

PARROT_EXPORT
opcode_t*
Parrot_cx_get_pc(PARROT_INTERP, ARGIN(PMC *ctx))
{
    ASSERT_ARGS(Parrot_cx_get_pc)
    Parrot_Context *c = Parrot_cx_get_context(interp, ctx);
    return c->current_pc;
}


/*

=item C<void Parrot_cx_set_pc(PARROT_INTERP, PMC *ctx, opcode_t *pc)>

Set program counter of Sub invocation.

=cut

*/

PARROT_EXPORT
void
Parrot_cx_set_pc(PARROT_INTERP, ARGIN(PMC *ctx), ARGIN_NULLOK(opcode_t *pc))
{
    ASSERT_ARGS(Parrot_cx_set_pc)
    Parrot_Context *c = Parrot_cx_get_context(interp, ctx);
    c->current_pc = pc;
}

/*

=item C<opcode_t* Parrot_cx_get_results(PARROT_INTERP, PMC *ctx)>

Set ptr into code with get_results opcode.

=cut

*/

PARROT_EXPORT
opcode_t*
Parrot_cx_get_results(PARROT_INTERP, ARGIN(PMC *ctx))
{
    ASSERT_ARGS(Parrot_cx_get_results)
    Parrot_Context *c = Parrot_cx_get_context(interp, ctx);
    return c->current_results;
}


/*

=item C<void Parrot_cx_set_results(PARROT_INTERP, PMC *ctx, opcode_t *pc)>

Set ptr into code with get_results opcode.

=cut

*/

PARROT_EXPORT
void
Parrot_cx_set_results(PARROT_INTERP, ARGIN(PMC *ctx), ARGIN_NULLOK(opcode_t *pc))
{
    ASSERT_ARGS(Parrot_cx_set_results)
    Parrot_Context *c = Parrot_cx_get_context(interp, ctx);
    c->current_results = pc;
}


/*

=item C<size_t Parrot_cx_get_pred_offset(PARROT_INTERP, PMC *ctx)>

Get pred_offset

=cut

*/

PARROT_EXPORT
size_t
Parrot_cx_get_pred_offset(PARROT_INTERP, ARGIN(PMC *ctx))
{
    ASSERT_ARGS(Parrot_cx_get_pred_offset)
    Parrot_Context *c = Parrot_cx_get_context(interp, ctx);
    return c->pred_offset;
}


/*

=item C<void Parrot_cx_set_pred_offset(PARROT_INTERP, PMC *ctx, size_t
pred_offset)>

Set pred_offset

=cut

*/

PARROT_EXPORT
void
Parrot_cx_set_pred_offset(PARROT_INTERP, ARGIN(PMC *ctx), size_t pred_offset)
{
    ASSERT_ARGS(Parrot_cx_set_pred_offset)
    Parrot_Context *c = Parrot_cx_get_context(interp, ctx);
    c->pred_offset = pred_offset;
}


/*

=back

*/


/*

=back

*/


/*
 * Local variables:
 *   c-file-style: "parrot"
 * End:
 * vim: expandtab shiftwidth=4:
 */