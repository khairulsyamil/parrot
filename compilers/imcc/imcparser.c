/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     LOW_PREC = 258,
     PARAM = 259,
     PRAGMA = 260,
     N_OPERATORS = 261,
     HLL = 262,
     HLL_MAP = 263,
     GOTO = 264,
     ARG = 265,
     IF = 266,
     UNLESS = 267,
     PNULL = 268,
     ADV_FLAT = 269,
     ADV_SLURPY = 270,
     ADV_OPTIONAL = 271,
     ADV_OPT_FLAG = 272,
     ADV_NAMED = 273,
     ADV_ARROW = 274,
     NEW = 275,
     NAMESPACE = 276,
     ENDNAMESPACE = 277,
     DOT_METHOD = 278,
     SUB = 279,
     SYM = 280,
     LOCAL = 281,
     LEXICAL = 282,
     CONST = 283,
     INC = 284,
     DEC = 285,
     GLOBAL_CONST = 286,
     PLUS_ASSIGN = 287,
     MINUS_ASSIGN = 288,
     MUL_ASSIGN = 289,
     DIV_ASSIGN = 290,
     CONCAT_ASSIGN = 291,
     BAND_ASSIGN = 292,
     BOR_ASSIGN = 293,
     BXOR_ASSIGN = 294,
     FDIV = 295,
     FDIV_ASSIGN = 296,
     MOD_ASSIGN = 297,
     SHR_ASSIGN = 298,
     SHL_ASSIGN = 299,
     SHR_U_ASSIGN = 300,
     SHIFT_LEFT = 301,
     SHIFT_RIGHT = 302,
     INTV = 303,
     FLOATV = 304,
     STRINGV = 305,
     PMCV = 306,
     LOG_XOR = 307,
     RELOP_EQ = 308,
     RELOP_NE = 309,
     RELOP_GT = 310,
     RELOP_GTE = 311,
     RELOP_LT = 312,
     RELOP_LTE = 313,
     GLOBAL = 314,
     GLOBALOP = 315,
     ADDR = 316,
     RESULT = 317,
     RETURN = 318,
     YIELDT = 319,
     GET_RESULTS = 320,
     POW = 321,
     SHIFT_RIGHT_U = 322,
     LOG_AND = 323,
     LOG_OR = 324,
     COMMA = 325,
     ESUB = 326,
     DOTDOT = 327,
     PCC_BEGIN = 328,
     PCC_END = 329,
     PCC_CALL = 330,
     PCC_SUB = 331,
     PCC_BEGIN_RETURN = 332,
     PCC_END_RETURN = 333,
     PCC_BEGIN_YIELD = 334,
     PCC_END_YIELD = 335,
     NCI_CALL = 336,
     METH_CALL = 337,
     INVOCANT = 338,
     MAIN = 339,
     LOAD = 340,
     INIT = 341,
     IMMEDIATE = 342,
     POSTCOMP = 343,
     METHOD = 344,
     ANON = 345,
     OUTER = 346,
     NEED_LEX = 347,
     MULTI = 348,
     VTABLE_METHOD = 349,
     LOADLIB = 350,
     UNIQUE_REG = 351,
     LABEL = 352,
     EMIT = 353,
     EOM = 354,
     IREG = 355,
     NREG = 356,
     SREG = 357,
     PREG = 358,
     IDENTIFIER = 359,
     REG = 360,
     MACRO = 361,
     ENDM = 362,
     STRINGC = 363,
     INTC = 364,
     FLOATC = 365,
     USTRINGC = 366,
     PARROT_OP = 367,
     VAR = 368,
     LINECOMMENT = 369,
     FILECOMMENT = 370,
     DOT = 371,
     CONCAT = 372,
     POINTY = 373
   };
#endif
/* Tokens.  */
#define LOW_PREC 258
#define PARAM 259
#define PRAGMA 260
#define N_OPERATORS 261
#define HLL 262
#define HLL_MAP 263
#define GOTO 264
#define ARG 265
#define IF 266
#define UNLESS 267
#define PNULL 268
#define ADV_FLAT 269
#define ADV_SLURPY 270
#define ADV_OPTIONAL 271
#define ADV_OPT_FLAG 272
#define ADV_NAMED 273
#define ADV_ARROW 274
#define NEW 275
#define NAMESPACE 276
#define ENDNAMESPACE 277
#define DOT_METHOD 278
#define SUB 279
#define SYM 280
#define LOCAL 281
#define LEXICAL 282
#define CONST 283
#define INC 284
#define DEC 285
#define GLOBAL_CONST 286
#define PLUS_ASSIGN 287
#define MINUS_ASSIGN 288
#define MUL_ASSIGN 289
#define DIV_ASSIGN 290
#define CONCAT_ASSIGN 291
#define BAND_ASSIGN 292
#define BOR_ASSIGN 293
#define BXOR_ASSIGN 294
#define FDIV 295
#define FDIV_ASSIGN 296
#define MOD_ASSIGN 297
#define SHR_ASSIGN 298
#define SHL_ASSIGN 299
#define SHR_U_ASSIGN 300
#define SHIFT_LEFT 301
#define SHIFT_RIGHT 302
#define INTV 303
#define FLOATV 304
#define STRINGV 305
#define PMCV 306
#define LOG_XOR 307
#define RELOP_EQ 308
#define RELOP_NE 309
#define RELOP_GT 310
#define RELOP_GTE 311
#define RELOP_LT 312
#define RELOP_LTE 313
#define GLOBAL 314
#define GLOBALOP 315
#define ADDR 316
#define RESULT 317
#define RETURN 318
#define YIELDT 319
#define GET_RESULTS 320
#define POW 321
#define SHIFT_RIGHT_U 322
#define LOG_AND 323
#define LOG_OR 324
#define COMMA 325
#define ESUB 326
#define DOTDOT 327
#define PCC_BEGIN 328
#define PCC_END 329
#define PCC_CALL 330
#define PCC_SUB 331
#define PCC_BEGIN_RETURN 332
#define PCC_END_RETURN 333
#define PCC_BEGIN_YIELD 334
#define PCC_END_YIELD 335
#define NCI_CALL 336
#define METH_CALL 337
#define INVOCANT 338
#define MAIN 339
#define LOAD 340
#define INIT 341
#define IMMEDIATE 342
#define POSTCOMP 343
#define METHOD 344
#define ANON 345
#define OUTER 346
#define NEED_LEX 347
#define MULTI 348
#define VTABLE_METHOD 349
#define LOADLIB 350
#define UNIQUE_REG 351
#define LABEL 352
#define EMIT 353
#define EOM 354
#define IREG 355
#define NREG 356
#define SREG 357
#define PREG 358
#define IDENTIFIER 359
#define REG 360
#define MACRO 361
#define ENDM 362
#define STRINGC 363
#define INTC 364
#define FLOATC 365
#define USTRINGC 366
#define PARROT_OP 367
#define VAR 368
#define LINECOMMENT 369
#define FILECOMMENT 370
#define DOT 371
#define CONCAT 372
#define POINTY 373




/* Copy the first part of user declarations.  */
#line 1 "imcc.y"

/*
 * imcc.y
 *
 * Intermediate Code Compiler for Parrot.
 *
 * Copyright (C) 2002 Melvin Smith <melvin.smith@mindspring.com>
 * Copyright (C) 2002-2007, The Perl Foundation.
 *
 * Grammar for the parser.
 *
 * $Id$
 *
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define _PARSER
#define PARSER_MAIN
#include "imc.h"
#include "parrot/dynext.h"
#include "pbc.h"
#include "parser.h"
#include "optimizer.h"

/* HEADERIZER HFILE: compilers/imcc/imc.h */

/* HEADERIZER BEGIN: static */

#ifndef YYENABLE_NLS
#  define YYENABLE_NLS 0
#endif

#ifndef YYLTYPE_IS_TRIVIAL
#  define YYLTYPE_IS_TRIVIAL 0
#endif

static void add_pcc_named_arg( PARROT_INTERP,
    NOTNULL(SymReg *cur_call),
    const char     *name,
    SymReg         *value )
        __attribute__nonnull__(1)
        __attribute__nonnull__(2);

static void add_pcc_named_param( PARROT_INTERP,
    SymReg     *cur_call,
    const char *name,
    SymReg     *value )
        __attribute__nonnull__(1);

static void add_pcc_named_result( PARROT_INTERP,
    SymReg     *cur_call,
    const char *name,
    SymReg     *value )
        __attribute__nonnull__(1);

static void add_pcc_named_return( PARROT_INTERP,
    SymReg     *cur_call,
    const char *name,
    SymReg     *value )
        __attribute__nonnull__(1);

static void begin_return_or_yield( PARROT_INTERP, int yield )
        __attribute__nonnull__(1);

static void clear_state( PARROT_INTERP )
        __attribute__nonnull__(1);

static void do_loadlib( PARROT_INTERP, NOTNULL(const char *lib) )
        __attribute__nonnull__(1)
        __attribute__nonnull__(2);

PARROT_WARN_UNUSED_RESULT
static Instruction* func_ins(
    PARROT_INTERP,
    IMC_Unit   *unit,
    SymReg     *lhs,
    const char *op,
    NOTNULL(SymReg **r),
    int n,
    int keyv,
    int emit )
        __attribute__nonnull__(5);

static Instruction * iINDEXFETCH( PARROT_INTERP,
    IMC_Unit *unit,
    SymReg *r0,
    SymReg *r1,
    SymReg *r2 )
        __attribute__nonnull__(1);

static Instruction * iINDEXSET( PARROT_INTERP,
    IMC_Unit *unit,
    SymReg *r0,
    SymReg *r1,
    SymReg *r2 )
        __attribute__nonnull__(1);

static Instruction * iLABEL( PARROT_INTERP, IMC_Unit *unit, SymReg *r0 )
        __attribute__nonnull__(1);

static const char * inv_op( const char *op );
static Instruction * iSUBROUTINE( PARROT_INTERP,
    IMC_Unit *unit,
    NOTNULL(SymReg *r) )
        __attribute__nonnull__(1)
        __attribute__nonnull__(3);

static Instruction * MK_I( PARROT_INTERP,
    IMC_Unit *unit,
    NOTNULL(const char *fmt),
    int n,
    ... )
        __attribute__nonnull__(1)
        __attribute__nonnull__(3);

PARROT_WARN_UNUSED_RESULT
static Instruction* mk_pmc_const( PARROT_INTERP,
    IMC_Unit *unit,
    NOTNULL(const char *type),
    NOTNULL(SymReg *left),
    NOTNULL(char *constant))
        __attribute__nonnull__(1)
        __attribute__nonnull__(3)
        __attribute__nonnull__(4)
        __attribute__nonnull__(5);

static SymReg * mk_sub_address_fromc( PARROT_INTERP, char *name )
        __attribute__nonnull__(1);

static SymReg * mk_sub_address_u( PARROT_INTERP, char *name )
        __attribute__nonnull__(1);

static void set_lexical( PARROT_INTERP, NOTNULL(SymReg *r), char *name )
        __attribute__nonnull__(1)
        __attribute__nonnull__(2);

/* HEADERIZER END: static */


#define YYDEBUG 1
#define YYERROR_VERBOSE 1

/*
 * we use a pure parser with the interpreter as a parameter this still
 * doesn't make the parser reentrant, there are too many globals
 * around.
 */

/*
 * Choosing instructions for Parrot is pretty easy since many are
 * polymorphic.
 */


/*
 * MK_I: build and emitb instruction by INS
 *
 * fmt may contain:
 *   op %s, %s # comment
 * or just
 *   op
 *
 *
 *  NOTE: Most usage of this function is with
 *        IMCC_INFO(interp)->cur_unit, but there are some
 *        exceptions. Thus, we can't easily factorize that piece of
 *        code.
 */
static Instruction *
MK_I(PARROT_INTERP, IMC_Unit *unit, NOTNULL(const char *fmt), int n, ...)
{
    char opname[64];
    char *p;
    const char *q;
    va_list ap;
    SymReg *r[IMCC_MAX_FIX_REGS];
    int i;

    for (p = opname, q = fmt; *q && *q != ' '; )
        *p++ = *q++;
    *p = 0;
    if (!*q)
        fmt = NULL;
    else
        fmt = ++q;
#ifdef OPDEBUG
    fprintf(stderr, "op '%s' format '%s' (%d)\n", opname, fmt?:"",n);
#endif
    va_start(ap, n);
    i = 0;
    for (i = 0; i < n; ++i) {
        r[i] = va_arg(ap, SymReg *);
    }
    va_end(ap);
    return INS(interp, unit, opname, fmt, r, n,
               IMCC_INFO(interp)->keyvec, 1);
}

PARROT_WARN_UNUSED_RESULT
static Instruction*
mk_pmc_const(PARROT_INTERP, IMC_Unit *unit, NOTNULL(const char *type),
             NOTNULL(SymReg *left), NOTNULL(char *constant))
{
    const   int type_enum = atoi(type);
    SymReg *rhs;
    SymReg *r[2];
    char   *name;
    int     ascii;

    if (left->type == VTADDRESS) {      /* IDENTIFIER */
        if (IMCC_INFO(interp)->state->pasm_file) {
            IMCC_fataly(interp, E_SyntaxError,
                        "Ident as PMC constant",
                        " %s\n", left->name);
        }
        left->type = VTIDENTIFIER;
        left->set = 'P';
    }
    r[0] = left;
    ascii = (*constant == '\'' || *constant == '"' );
    if (ascii) {
        /* strip delimiters */
        const size_t len  = strlen(constant);
        name              = (char *)mem_sys_allocate(len);
        constant[len - 1] = '\0';

        strcpy(name, constant + 1);
        free(constant);
    }
    else {
        name = constant;
    }
    switch (type_enum) {
    case enum_class_Sub:
    case enum_class_Coroutine:
        rhs = mk_const(interp, name, 'p');
        if (!ascii)
            rhs->type |= VT_ENCODED;
        r[1] = rhs;
        rhs->pmc_type = type_enum;
        rhs->usage = U_FIXUP;
        return INS(interp, unit, "set_p_pc", "", r, 2, 0, 1);
    }
    rhs = mk_const(interp, name, 'P');
    r[1] = rhs;
    rhs->pmc_type = type_enum;
    return INS(interp, unit, "set_p_pc", "", r, 2, 0, 1);
}

PARROT_WARN_UNUSED_RESULT
static Instruction*
func_ins(PARROT_INTERP, IMC_Unit *unit, SymReg *lhs, const char *op,
         SymReg ** r, int n, int keyv, int emit)
{
    int i;
    /* shift regs up by 1 */
    for (i = n - 1; i >= 0; --i)
        r[i+1] = r[i];
    r[0] = lhs;
    /* shift keyvec */
    keyv <<= 1;
    return INS(interp, unit, op, "", r, n+1, keyv, emit);
}
/*
 * special instructions
 *
 * labels and such
 */

static void
clear_state(PARROT_INTERP)
{
    IMCC_INFO(interp) -> nargs = 0;
    IMCC_INFO(interp) -> keyvec = 0;
}

Instruction *
INS_LABEL(PARROT_INTERP, IMC_Unit *unit, SymReg *r0, int emit)
{

    Instruction * const ins = _mk_instruction("","%s:", 1, &r0, 0);
    ins->type               = ITLABEL;
    r0->first_ins           = ins;

    if (emit)
        emitb(interp, unit, ins);

    return ins;
}

static Instruction * iLABEL(PARROT_INTERP, IMC_Unit *unit, SymReg *r0) {
    Instruction * const i = INS_LABEL(interp, unit, r0, 1);
    i->line               = IMCC_INFO(interp)->line;

    clear_state(interp);
    return i;
}

static Instruction *
iSUBROUTINE(PARROT_INTERP, IMC_Unit *unit, NOTNULL(SymReg *r)) {
    Instruction * const i =iLABEL(interp, unit, r);

    r->type    = (r->type & VT_ENCODED) ? VT_PCC_SUB|VT_ENCODED : VT_PCC_SUB;
    r->pcc_sub = (pcc_sub_t*)calloc(1, sizeof(struct pcc_sub_t));

    IMCC_INFO(interp)->cur_call = r;
    i->line                     = IMCC_INFO(interp)->line;

    add_namespace(interp, unit);
    return i;
}

/*
 * substr or X = P[key]
 */
static Instruction *
iINDEXFETCH(PARROT_INTERP, IMC_Unit *unit, SymReg *r0, SymReg *r1, SymReg *r2)
{
    if (r0->set == 'S' && r1->set == 'S' && r2->set == 'I') {
        SymReg * const r3 = mk_const(interp, str_dup("1"), 'I');
        return MK_I(interp, unit, "substr %s, %s, %s, 1", 4, r0, r1, r2, r3);
    }

    IMCC_INFO(interp) -> keyvec |= KEY_BIT(2);
    return MK_I(interp, unit, "set %s, %s[%s]", 3, r0,r1,r2);
}

/*
 * substr or P[key] = X
 */

static Instruction *
iINDEXSET(PARROT_INTERP, IMC_Unit * unit,
          SymReg * r0, SymReg * r1, SymReg * r2)
{
    if (r0->set == 'S' && r1->set == 'I' && r2->set == 'S') {
        SymReg * r3 = mk_const(interp, str_dup("1"), 'I');
        MK_I(interp, unit, "substr %s, %s, %s, %s", 4, r0, r1,r3, r2);
    }
    else if (r0->set == 'P') {
        IMCC_INFO(interp) -> keyvec |= KEY_BIT(1);
        MK_I(interp, unit, "set %s[%s], %s", 3, r0,r1,r2);
    }
    else {
        IMCC_fataly(interp, E_SyntaxError,
            "unsupported indexed set op\n");
    }
    return 0;
}

static const char *
inv_op(const char *op) {
    int n;
    return get_neg_op(op, &n);
}

Instruction *
IMCC_create_itcall_label(PARROT_INTERP)
{
    char name[128];
    SymReg * r;
    Instruction *i;

    sprintf(name, "%cpcc_sub_call_%d", IMCC_INTERNAL_CHAR, IMCC_INFO(interp)->cnr++);
    r = mk_pcc_sub(interp, str_dup(name), 0);
    i = iLABEL(interp, IMCC_INFO(interp)->cur_unit, r);
    IMCC_INFO(interp)->cur_call = r;
    i->type = ITCALL | ITPCCSUB;
    return i;
}


static SymReg *
mk_sub_address_fromc(PARROT_INTERP, char * name)
{
    /* name is a quoted sub name */
    SymReg *r;

    name[strlen(name) - 1] = '\0';
    r = mk_sub_address(interp, str_dup(name + 1));
    mem_sys_free(name);
    return r;
}

static SymReg *
mk_sub_address_u(PARROT_INTERP, char * name)
{
    SymReg * const r = mk_sub_address(interp, name);
    r->type         |= VT_ENCODED;

    return r;
}

void
IMCC_itcall_sub(PARROT_INTERP, SymReg *sub)
{
    IMCC_INFO(interp)->cur_call->pcc_sub->sub = sub;
    if (IMCC_INFO(interp)->cur_obj) {
        if (IMCC_INFO(interp)->cur_obj->set != 'P')
            IMCC_fataly(interp, E_SyntaxError, "object isn't a PMC");
        IMCC_INFO(interp)->cur_call->pcc_sub->object = IMCC_INFO(interp)->cur_obj;
        IMCC_INFO(interp)->cur_obj = NULL;
    }
    if (IMCC_INFO(interp)->cur_call->pcc_sub->sub->pmc_type == enum_class_NCI)
        IMCC_INFO(interp)->cur_call->pcc_sub->flags |= isNCI;
    if (IMCC_INFO(interp)->cur_unit->type == IMC_PCCSUB)
        IMCC_INFO(interp)->cur_unit->instructions->r[0]->pcc_sub->calls_a_sub |= 1;
}

static void
begin_return_or_yield(PARROT_INTERP, int yield)
{
    Instruction *i;
    Instruction * const ins = IMCC_INFO(interp)->cur_unit->instructions;
    char                name[128];

    if (!ins || !ins->r[0] || !(ins->r[0]->type & VT_PCC_SUB))
        IMCC_fataly(interp, E_SyntaxError,
                    "yield or return directive outside pcc subroutine\n");
    if (yield)
       ins->r[0]->pcc_sub->calls_a_sub = 1 | ITPCCYIELD;
    sprintf(name, yield ? "%cpcc_sub_yield_%d" : "%cpcc_sub_ret_%d",
            IMCC_INTERNAL_CHAR, IMCC_INFO(interp)->cnr++);
    interp->imc_info->sr_return = mk_pcc_sub(interp, str_dup(name), 0);
    i = iLABEL(interp, IMCC_INFO(interp)->cur_unit, interp->imc_info->sr_return);
    i->type = yield ? ITPCCSUB | ITLABEL | ITPCCYIELD : ITPCCSUB | ITLABEL ;
    interp->imc_info->asm_state = yield ? AsmInYield : AsmInReturn;
}

static void
set_lexical(PARROT_INTERP, NOTNULL(SymReg *r), char *name)
{
    SymReg *n = mk_const(interp, name, 'S');

    r->usage |= U_LEXICAL;

    if (n == r->reg)
        IMCC_fataly(interp, E_SyntaxError,
            "register %s already declared as lexical %s", r->name, n->name);

    /* chain all names in r->reg */
    n->reg = r->reg;
    r->reg = n;
}

static void
add_pcc_named_arg(PARROT_INTERP, NOTNULL(SymReg *cur_call), const char *name,
                  SymReg *value)
{
    SymReg *r = mk_const(interp, name, 'S');
    r->type  |= VT_NAMED;

    add_pcc_arg(cur_call, r);
    add_pcc_arg(cur_call, value);
}

static void
add_pcc_named_result(PARROT_INTERP, SymReg *cur_call, const char *name,
                     SymReg *value)
{
    SymReg * const r = mk_const(interp, name, 'S');
    r->type         |= VT_NAMED;

    add_pcc_result(cur_call, r);
    add_pcc_result(cur_call, value);
}

static void
add_pcc_named_param(PARROT_INTERP, SymReg *cur_call, const char *name,
                    SymReg *value)
{
    SymReg * const r = mk_const(interp, name, 'S');
    r->type         |= VT_NAMED;

    add_pcc_param(cur_call, r);
    add_pcc_param(cur_call, value);
}

static void
add_pcc_named_return(PARROT_INTERP, SymReg *cur_call, const char *name,
                     SymReg *value)
{
    SymReg * const r = mk_const(interp, name, 'S');
    r->type         |= VT_NAMED;

    add_pcc_return(cur_call, r);
    add_pcc_return(cur_call, value);
}

static void
adv_named_set(PARROT_INTERP, char *name) {
    if (IMCC_INFO(interp)->adv_named_id) {
        IMCC_fataly(interp, E_SyntaxError,
                    "Named parameter with more than one name.\n");
    }
    IMCC_INFO(interp)->adv_named_id = name;
}

static void
do_loadlib(PARROT_INTERP, NOTNULL(const char *lib))
{
    STRING * const s = string_unescape_cstring(interp, lib + 1, '"', NULL);
    Parrot_load_lib(interp, s, NULL);
    Parrot_register_HLL_lib(interp, s);
}

/* HEADERIZER STOP */



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 514 "imcc.y"
{
    IdList * idlist;
    int t;
    char * s;
    SymReg * sr;
    Instruction *i;
}
/* Line 187 of yacc.c.  */
#line 853 "imcc.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 866 "imcc.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  34
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   854

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  135
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  119
/* YYNRULES -- Number of rules.  */
#define YYNRULES  340
/* YYNRULES -- Number of states.  */
#define YYNSTATES  590

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   373

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       4,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   125,     2,     2,     2,   131,   132,     2,
     123,   124,   129,   128,     2,   126,     2,   130,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,   134,
       2,   120,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   121,     2,   122,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,   133,     2,   127,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    12,    14,    16,    18,
      20,    23,    25,    27,    31,    34,    38,    41,    46,    51,
      52,    59,    60,    67,    69,    71,    73,    76,    80,    83,
      85,    87,    89,    91,    93,    94,    98,    99,   104,   107,
     112,   113,   115,   116,   121,   122,   124,   128,   132,   133,
     134,   135,   136,   147,   148,   150,   154,   155,   159,   163,
     169,   170,   172,   177,   182,   187,   189,   194,   195,   199,
     201,   203,   205,   207,   209,   211,   213,   217,   218,   220,
     221,   222,   223,   234,   235,   245,   246,   249,   250,   254,
     255,   257,   259,   263,   265,   267,   269,   271,   273,   275,
     277,   279,   281,   283,   285,   291,   295,   299,   303,   307,
     313,   319,   320,   324,   327,   328,   332,   336,   337,   342,
     343,   346,   348,   350,   352,   354,   359,   361,   363,   365,
     367,   369,   370,   376,   378,   379,   382,   386,   390,   391,
     397,   398,   404,   405,   407,   411,   415,   421,   423,   426,
     427,   430,   433,   435,   437,   438,   440,   443,   445,   447,
     451,   454,   456,   460,   463,   465,   467,   469,   472,   475,
     476,   481,   486,   487,   494,   496,   497,   504,   507,   510,
     513,   516,   518,   520,   522,   523,   525,   527,   529,   531,
     533,   535,   539,   544,   549,   554,   560,   566,   572,   578,
     584,   590,   596,   602,   608,   614,   620,   626,   632,   638,
     644,   650,   656,   662,   668,   674,   680,   686,   692,   699,
     706,   713,   721,   726,   731,   738,   745,   753,   758,   763,
     768,   773,   780,   788,   792,   793,   803,   805,   807,   809,
     813,   814,   820,   824,   828,   832,   836,   840,   844,   848,
     852,   856,   860,   864,   868,   872,   877,   879,   881,   883,
     885,   889,   893,   897,   899,   901,   902,   908,   909,   913,
     915,   921,   925,   928,   929,   932,   934,   936,   941,   944,
     948,   954,   956,   960,   961,   968,   975,   981,   987,   992,
     997,  1002,  1007,  1009,  1011,  1013,  1015,  1017,  1019,  1021,
    1023,  1024,  1026,  1030,  1032,  1034,  1039,  1043,  1045,  1047,
    1049,  1051,  1053,  1055,  1057,  1059,  1061,  1063,  1065,  1066,
    1069,  1070,  1073,  1075,  1079,  1080,  1085,  1087,  1091,  1094,
    1097,  1099,  1101,  1103,  1105,  1107,  1109,  1111,  1113,  1115,
    1117
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     136,     0,    -1,   137,    -1,   138,    -1,   137,   138,    -1,
     156,    -1,   142,    -1,   158,    -1,   173,    -1,   153,    -1,
     107,     4,    -1,   139,    -1,     4,    -1,     6,   140,     4,
      -1,   141,     4,    -1,    96,   109,     4,    -1,     7,   110,
      -1,     8,   109,    71,   109,    -1,     9,   110,    71,   110,
      -1,    -1,    29,   143,   215,   105,   120,   252,    -1,    -1,
      29,   145,   110,   242,   120,   146,    -1,   109,    -1,   112,
      -1,   148,    -1,   147,   148,    -1,   205,   149,     4,    -1,
     107,     4,    -1,   116,    -1,   115,    -1,   156,    -1,   144,
      -1,   139,    -1,    -1,   150,   113,   152,    -1,    -1,    77,
     151,   181,    98,    -1,    14,   243,    -1,    28,   109,    71,
     106,    -1,    -1,   236,    -1,    -1,    99,   154,   155,   100,
      -1,    -1,   147,    -1,    22,   157,     4,    -1,   121,   244,
     122,    -1,    -1,    -1,    -1,    -1,    25,   159,   239,   160,
     181,     4,   161,   162,   172,    72,    -1,    -1,     4,    -1,
     162,   163,     4,    -1,    -1,     5,   164,   165,    -1,   215,
     105,   190,    -1,   215,   109,    20,   105,   190,    -1,    -1,
      71,    -1,    94,   123,   170,   124,    -1,    92,   123,   109,
     124,    -1,    92,   123,   105,   124,    -1,    95,    -1,    95,
     123,   109,   124,    -1,    -1,   170,    71,   171,    -1,   171,
      -1,    49,    -1,    50,    -1,    52,    -1,    51,    -1,   105,
      -1,   109,    -1,   121,   244,   122,    -1,    -1,   202,    -1,
      -1,    -1,    -1,    77,   174,   105,   175,   181,     4,   176,
     162,   172,    72,    -1,    -1,    74,     4,   178,   185,   180,
     184,   179,   187,    75,    -1,    -1,   207,     4,    -1,    -1,
      84,   243,     4,    -1,    -1,   182,    -1,   183,    -1,   182,
     166,   183,    -1,    86,    -1,    87,    -1,    85,    -1,    88,
      -1,    89,    -1,    91,    -1,    90,    -1,    93,    -1,   167,
      -1,   168,    -1,   169,    -1,    76,   243,    71,   243,     4,
      -1,    76,   243,     4,    -1,    82,   243,     4,    -1,    83,
     235,     4,    -1,    83,   109,     4,    -1,    83,   235,    71,
     243,     4,    -1,    83,   109,    71,   243,     4,    -1,    -1,
     185,   186,     4,    -1,    11,   228,    -1,    -1,   187,   188,
       4,    -1,    63,   235,   190,    -1,    -1,    27,   189,   215,
     210,    -1,    -1,   190,   191,    -1,    16,    -1,    17,    -1,
      18,    -1,    19,    -1,    19,   123,   109,   124,    -1,    97,
      -1,    78,    -1,    80,    -1,    79,    -1,    81,    -1,    -1,
     192,     4,   195,   196,   193,    -1,   198,    -1,    -1,   196,
       4,    -1,   196,   197,     4,    -1,    64,   243,   229,    -1,
      -1,    64,   123,   199,   201,   124,    -1,    -1,    65,   123,
     200,   201,   124,    -1,    -1,   228,    -1,   109,    20,   243,
      -1,   201,    71,   228,    -1,   201,    71,   109,    20,   243,
      -1,   204,    -1,   202,   204,    -1,    -1,   203,   208,    -1,
     107,     4,    -1,   116,    -1,   115,    -1,    -1,   206,    -1,
     206,   207,    -1,   207,    -1,    98,    -1,   205,   211,     4,
      -1,     1,     4,    -1,   210,    -1,   209,    71,   210,    -1,
     105,    97,    -1,   105,    -1,   217,    -1,   233,    -1,    22,
     105,    -1,    23,   105,    -1,    -1,    27,   212,   215,   209,
      -1,    28,   109,    71,   235,    -1,    -1,    29,   213,   215,
     105,   120,   252,    -1,   144,    -1,    -1,    32,   214,   215,
     105,   120,   252,    -1,    64,   225,    -1,    10,   241,    -1,
     113,   236,    -1,    14,   243,    -1,   225,    -1,   177,    -1,
     194,    -1,    -1,    49,    -1,    50,    -1,    51,    -1,    52,
      -1,   216,    -1,   105,    -1,   235,   120,   243,    -1,   235,
     120,   125,   243,    -1,   235,   120,   126,   243,    -1,   235,
     120,   127,   243,    -1,   235,   120,   243,   128,   243,    -1,
     235,   120,   243,   126,   243,    -1,   235,   120,   243,   129,
     243,    -1,   235,   120,   243,    67,   243,    -1,   235,   120,
     243,   130,   243,    -1,   235,   120,   243,    41,   243,    -1,
     235,   120,   243,   131,   243,    -1,   235,   120,   243,   118,
     243,    -1,   235,   120,   243,    54,   243,    -1,   235,   120,
     243,    55,   243,    -1,   235,   120,   243,    56,   243,    -1,
     235,   120,   243,    58,   243,    -1,   235,   120,   243,    59,
     243,    -1,   235,   120,   243,    57,   243,    -1,   235,   120,
     243,    47,   243,    -1,   235,   120,   243,    48,   243,    -1,
     235,   120,   243,    68,   243,    -1,   235,   120,   243,    69,
     243,    -1,   235,   120,   243,    70,   243,    -1,   235,   120,
     243,    53,   243,    -1,   235,   120,   243,   132,   243,    -1,
     235,   120,   243,   133,   243,    -1,   235,   120,   243,   127,
     243,    -1,   235,   120,   243,   121,   244,   122,    -1,   235,
     121,   244,   122,   120,   243,    -1,   235,   120,    21,   216,
      71,   243,    -1,   235,   120,    21,   216,   121,   244,   122,
      -1,   235,   120,    21,   216,    -1,   235,   120,    21,   243,
      -1,   235,   120,    21,   121,   244,   122,    -1,   235,   120,
      21,   243,    71,   243,    -1,   235,   120,    21,   243,   121,
     244,   122,    -1,   235,   120,    62,   105,    -1,   235,   120,
      61,   253,    -1,    61,   253,   120,   243,    -1,    21,   235,
      71,   243,    -1,    21,   235,    71,   243,    71,   243,    -1,
      21,   235,    71,   243,   121,   244,   122,    -1,   235,   120,
     225,    -1,    -1,   123,   218,   232,   124,   120,   223,   123,
     227,   124,    -1,   219,    -1,   221,    -1,   222,    -1,   235,
     120,    14,    -1,    -1,    66,   220,   123,   232,   124,    -1,
     235,    33,   243,    -1,   235,    34,   243,    -1,   235,    35,
     243,    -1,   235,    36,   243,    -1,   235,    43,   243,    -1,
     235,    42,   243,    -1,   235,    37,   243,    -1,   235,    38,
     243,    -1,   235,    39,   243,    -1,   235,    40,   243,    -1,
     235,    44,   243,    -1,   235,    45,   243,    -1,   235,    46,
     243,    -1,   235,   120,   113,   152,    -1,   105,    -1,   109,
      -1,   112,    -1,   235,    -1,   235,   224,   240,    -1,   235,
     224,   109,    -1,   235,   224,   235,    -1,   119,    -1,   117,
      -1,    -1,   223,   226,   123,   227,   124,    -1,    -1,   227,
      71,   228,    -1,   228,    -1,   227,    71,   109,    20,   243,
      -1,   109,    20,   243,    -1,   243,   229,    -1,    -1,   229,
     230,    -1,    15,    -1,    19,    -1,    19,   123,   109,   124,
      -1,   235,   190,    -1,   232,    71,   231,    -1,   232,    71,
     109,    20,   235,    -1,   231,    -1,   109,    20,   235,    -1,
      -1,    12,   243,   234,   243,    10,   241,    -1,    13,   243,
     234,   243,    10,   241,    -1,    12,    14,   243,    10,   241,
      -1,    13,    14,   243,    10,   241,    -1,    12,   243,    10,
     241,    -1,    13,   243,    10,   241,    -1,    12,   243,    71,
     241,    -1,    13,   243,    71,   241,    -1,    54,    -1,    55,
      -1,    56,    -1,    57,    -1,    58,    -1,    59,    -1,   114,
      -1,   251,    -1,    -1,   237,    -1,   237,    71,   238,    -1,
     238,    -1,   242,    -1,   235,   121,   244,   122,    -1,   121,
     246,   122,    -1,   240,    -1,   109,    -1,   112,    -1,   105,
      -1,   113,    -1,   105,    -1,   113,    -1,   241,    -1,   243,
      -1,   235,    -1,   252,    -1,    -1,   245,   248,    -1,    -1,
     247,   248,    -1,   250,    -1,   248,   134,   250,    -1,    -1,
     248,    71,   249,   250,    -1,   243,    -1,   243,    73,   243,
      -1,    73,   243,    -1,   243,    73,    -1,   101,    -1,   102,
      -1,   103,    -1,   104,    -1,   106,    -1,   110,    -1,   111,
      -1,   109,    -1,   112,    -1,   103,    -1,   109,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   605,   605,   609,   610,   614,   615,   616,   619,   622,
     625,   626,   627,   630,   631,   632,   635,   643,   655,   664,
     664,   669,   669,   673,   674,   678,   679,   683,   684,   685,
     686,   687,   688,   689,   692,   692,   699,   698,   709,   711,
     716,   720,   724,   724,   734,   736,   740,   755,   756,   761,
     765,   768,   760,   774,   775,   776,   787,   787,   791,   796,
     806,   807,   811,   814,   817,   822,   826,   833,   834,   835,
     839,   840,   841,   842,   843,   853,   863,   866,   868,   872,
     873,   874,   872,   881,   880,   913,   914,   918,   919,   924,
     925,   929,   930,   934,   935,   936,   937,   938,   939,   940,
     941,   942,   943,   944,   948,   953,   955,   960,   962,   964,
     968,   976,   977,   981,   986,   987,   991,   992,   992,  1005,
    1006,  1010,  1011,  1012,  1013,  1014,  1015,  1020,  1021,  1025,
    1026,  1031,  1030,  1035,  1041,  1042,  1045,  1051,  1056,  1055,
    1063,  1062,  1072,  1073,  1080,  1082,  1089,  1095,  1096,  1108,
    1112,  1114,  1115,  1116,  1120,  1121,  1125,  1126,  1130,  1138,
    1140,  1149,  1156,  1165,  1173,  1183,  1184,  1185,  1186,  1187,
    1187,  1202,  1206,  1206,  1208,  1209,  1209,  1211,  1215,  1216,
    1222,  1224,  1225,  1226,  1227,  1231,  1232,  1233,  1234,  1235,
    1239,  1250,  1252,  1254,  1256,  1258,  1260,  1262,  1264,  1266,
    1268,  1270,  1272,  1274,  1276,  1278,  1280,  1282,  1284,  1286,
    1288,  1290,  1292,  1294,  1296,  1298,  1300,  1302,  1304,  1306,
    1308,  1310,  1312,  1314,  1316,  1318,  1320,  1322,  1325,  1327,
    1331,  1333,  1335,  1338,  1345,  1344,  1353,  1354,  1355,  1356,
    1360,  1360,  1366,  1368,  1370,  1372,  1374,  1376,  1378,  1380,
    1382,  1384,  1386,  1388,  1390,  1395,  1404,  1405,  1406,  1407,
    1412,  1413,  1414,  1417,  1418,  1423,  1422,  1432,  1433,  1440,
    1447,  1449,  1453,  1457,  1458,  1462,  1463,  1464,  1467,  1471,
    1478,  1480,  1487,  1488,  1492,  1494,  1496,  1498,  1500,  1502,
    1504,  1506,  1511,  1512,  1513,  1514,  1515,  1516,  1520,  1521,
    1525,  1526,  1530,  1531,  1535,  1536,  1543,  1550,  1551,  1552,
    1556,  1557,  1561,  1562,  1566,  1567,  1571,  1572,  1575,  1575,
    1582,  1582,  1590,  1591,  1594,  1594,  1600,  1605,  1610,  1611,
    1615,  1616,  1617,  1618,  1619,  1623,  1624,  1625,  1626,  1630,
    1631
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "LOW_PREC", "'\\n'", "PARAM", "PRAGMA",
  "N_OPERATORS", "HLL", "HLL_MAP", "GOTO", "ARG", "IF", "UNLESS", "PNULL",
  "ADV_FLAT", "ADV_SLURPY", "ADV_OPTIONAL", "ADV_OPT_FLAG", "ADV_NAMED",
  "ADV_ARROW", "NEW", "NAMESPACE", "ENDNAMESPACE", "DOT_METHOD", "SUB",
  "SYM", "LOCAL", "LEXICAL", "CONST", "INC", "DEC", "GLOBAL_CONST",
  "PLUS_ASSIGN", "MINUS_ASSIGN", "MUL_ASSIGN", "DIV_ASSIGN",
  "CONCAT_ASSIGN", "BAND_ASSIGN", "BOR_ASSIGN", "BXOR_ASSIGN", "FDIV",
  "FDIV_ASSIGN", "MOD_ASSIGN", "SHR_ASSIGN", "SHL_ASSIGN", "SHR_U_ASSIGN",
  "SHIFT_LEFT", "SHIFT_RIGHT", "INTV", "FLOATV", "STRINGV", "PMCV",
  "LOG_XOR", "RELOP_EQ", "RELOP_NE", "RELOP_GT", "RELOP_GTE", "RELOP_LT",
  "RELOP_LTE", "GLOBAL", "GLOBALOP", "ADDR", "RESULT", "RETURN", "YIELDT",
  "GET_RESULTS", "POW", "SHIFT_RIGHT_U", "LOG_AND", "LOG_OR", "COMMA",
  "ESUB", "DOTDOT", "PCC_BEGIN", "PCC_END", "PCC_CALL", "PCC_SUB",
  "PCC_BEGIN_RETURN", "PCC_END_RETURN", "PCC_BEGIN_YIELD", "PCC_END_YIELD",
  "NCI_CALL", "METH_CALL", "INVOCANT", "MAIN", "LOAD", "INIT", "IMMEDIATE",
  "POSTCOMP", "METHOD", "ANON", "OUTER", "NEED_LEX", "MULTI",
  "VTABLE_METHOD", "LOADLIB", "UNIQUE_REG", "LABEL", "EMIT", "EOM", "IREG",
  "NREG", "SREG", "PREG", "IDENTIFIER", "REG", "MACRO", "ENDM", "STRINGC",
  "INTC", "FLOATC", "USTRINGC", "PARROT_OP", "VAR", "LINECOMMENT",
  "FILECOMMENT", "DOT", "CONCAT", "POINTY", "'='", "'['", "']'", "'('",
  "')'", "'!'", "'-'", "'~'", "'+'", "'*'", "'/'", "'%'", "'&'", "'|'",
  "';'", "$accept", "program", "compilation_units", "compilation_unit",
  "pragma", "pragma_1", "hll_def", "constdef", "@1", "pmc_const", "@2",
  "any_string", "pasmcode", "pasmline", "pasm_inst", "@3", "@4",
  "pasm_args", "emit", "@5", "opt_pasmcode", "class_namespace", "maybe_ns",
  "sub", "@6", "@7", "@8", "sub_params", "sub_param", "@9",
  "sub_param_type_def", "opt_comma", "multi", "outer", "vtable",
  "multi_types", "multi_type", "sub_body", "pcc_sub", "@10", "@11", "@12",
  "pcc_sub_call", "@13", "opt_label", "opt_invocant", "sub_proto",
  "sub_proto_list", "proto", "pcc_call", "pcc_args", "pcc_arg",
  "pcc_results", "pcc_result", "@14", "paramtype_list", "paramtype",
  "begin_ret_or_yield", "end_ret_or_yield", "pcc_ret", "@15",
  "pcc_returns", "pcc_return", "pcc_return_many", "@16", "@17",
  "var_returns", "statements", "helper_clear_state", "statement", "labels",
  "_labels", "label", "instruction", "id_list", "id_list_id",
  "labeled_inst", "@18", "@19", "@20", "type", "classname", "assignment",
  "@21", "get_results", "@22", "op_assign", "func_assign", "the_sub",
  "ptr", "sub_call", "@23", "arglist", "arg", "argtype_list", "argtype",
  "result", "targetlist", "if_statement", "relop", "target", "vars",
  "_vars", "_var_or_i", "sub_label_op_c", "sub_label_op", "label_op",
  "var_or_i", "var", "keylist", "@24", "keylist_force", "@25", "_keylist",
  "@26", "key", "reg", "const", "string", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,    10,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,   300,   301,   302,   303,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   318,   319,   320,   321,   322,   323,
     324,   325,   326,   327,   328,   329,   330,   331,   332,   333,
     334,   335,   336,   337,   338,   339,   340,   341,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,   352,   353,
     354,   355,   356,   357,   358,   359,   360,   361,   362,   363,
     364,   365,   366,   367,   368,   369,   370,   371,   372,   373,
      61,    91,    93,    40,    41,    33,    45,   126,    43,    42,
      47,    37,    38,   124,    59
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   135,   136,   137,   137,   138,   138,   138,   138,   138,
     138,   138,   138,   139,   139,   139,   140,   141,   141,   143,
     142,   145,   144,   146,   146,   147,   147,   148,   148,   148,
     148,   148,   148,   148,   150,   149,   151,   149,   149,   149,
     149,   152,   154,   153,   155,   155,   156,   157,   157,   159,
     160,   161,   158,   162,   162,   162,   164,   163,   165,   165,
     166,   166,   167,   168,   168,   169,   169,   170,   170,   170,
     171,   171,   171,   171,   171,   171,   171,   172,   172,   174,
     175,   176,   173,   178,   177,   179,   179,   180,   180,   181,
     181,   182,   182,   183,   183,   183,   183,   183,   183,   183,
     183,   183,   183,   183,   184,   184,   184,   184,   184,   184,
     184,   185,   185,   186,   187,   187,   188,   189,   188,   190,
     190,   191,   191,   191,   191,   191,   191,   192,   192,   193,
     193,   195,   194,   194,   196,   196,   196,   197,   199,   198,
     200,   198,   201,   201,   201,   201,   201,   202,   202,   203,
     204,   204,   204,   204,   205,   205,   206,   206,   207,   208,
     208,   209,   209,   210,   210,   211,   211,   211,   211,   212,
     211,   211,   213,   211,   211,   214,   211,   211,   211,   211,
     211,   211,   211,   211,   211,   215,   215,   215,   215,   215,
     216,   217,   217,   217,   217,   217,   217,   217,   217,   217,
     217,   217,   217,   217,   217,   217,   217,   217,   217,   217,
     217,   217,   217,   217,   217,   217,   217,   217,   217,   217,
     217,   217,   217,   217,   217,   217,   217,   217,   217,   217,
     217,   217,   217,   217,   218,   217,   217,   217,   217,   217,
     220,   219,   221,   221,   221,   221,   221,   221,   221,   221,
     221,   221,   221,   221,   221,   222,   223,   223,   223,   223,
     223,   223,   223,   224,   224,   226,   225,   227,   227,   227,
     227,   227,   228,   229,   229,   230,   230,   230,   231,   232,
     232,   232,   232,   232,   233,   233,   233,   233,   233,   233,
     233,   233,   234,   234,   234,   234,   234,   234,   235,   235,
     236,   236,   237,   237,   238,   238,   238,   239,   239,   239,
     240,   240,   241,   241,   242,   242,   243,   243,   245,   244,
     247,   246,   248,   248,   249,   248,   250,   250,   250,   250,
     251,   251,   251,   251,   251,   252,   252,   252,   252,   253,
     253
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     1,     1,
       2,     1,     1,     3,     2,     3,     2,     4,     4,     0,
       6,     0,     6,     1,     1,     1,     2,     3,     2,     1,
       1,     1,     1,     1,     0,     3,     0,     4,     2,     4,
       0,     1,     0,     4,     0,     1,     3,     3,     0,     0,
       0,     0,    10,     0,     1,     3,     0,     3,     3,     5,
       0,     1,     4,     4,     4,     1,     4,     0,     3,     1,
       1,     1,     1,     1,     1,     1,     3,     0,     1,     0,
       0,     0,    10,     0,     9,     0,     2,     0,     3,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     5,     3,     3,     3,     3,     5,
       5,     0,     3,     2,     0,     3,     3,     0,     4,     0,
       2,     1,     1,     1,     1,     4,     1,     1,     1,     1,
       1,     0,     5,     1,     0,     2,     3,     3,     0,     5,
       0,     5,     0,     1,     3,     3,     5,     1,     2,     0,
       2,     2,     1,     1,     0,     1,     2,     1,     1,     3,
       2,     1,     3,     2,     1,     1,     1,     2,     2,     0,
       4,     4,     0,     6,     1,     0,     6,     2,     2,     2,
       2,     1,     1,     1,     0,     1,     1,     1,     1,     1,
       1,     3,     4,     4,     4,     5,     5,     5,     5,     5,
       5,     5,     5,     5,     5,     5,     5,     5,     5,     5,
       5,     5,     5,     5,     5,     5,     5,     5,     6,     6,
       6,     7,     4,     4,     6,     6,     7,     4,     4,     4,
       4,     6,     7,     3,     0,     9,     1,     1,     1,     3,
       0,     5,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     4,     1,     1,     1,     1,
       3,     3,     3,     1,     1,     0,     5,     0,     3,     1,
       5,     3,     2,     0,     2,     1,     1,     4,     2,     3,
       5,     1,     3,     0,     6,     6,     5,     5,     4,     4,
       4,     4,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     1,     3,     1,     1,     4,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     2,
       0,     2,     1,     3,     0,     4,     1,     3,     2,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,    12,     0,     0,     0,    48,    49,    19,    79,     0,
      42,     0,     0,     2,     3,    11,     0,     6,     9,     5,
       7,     8,     0,     0,     0,     0,   318,     0,     0,     0,
       0,     0,   154,    10,     1,     4,    14,    16,    13,     0,
       0,     0,     0,    46,   310,   308,   309,   311,    50,   307,
     185,   186,   187,   188,   190,     0,   189,    80,    15,    21,
     158,     0,    30,    29,    33,    32,   154,    25,     0,    31,
      34,   155,   157,    17,    18,    47,     0,   330,   331,   332,
     333,   334,   337,   335,   336,   338,   298,   316,   326,   319,
     322,   299,   317,    89,     0,    89,     0,    28,    26,    43,
       0,     0,    36,     0,     0,   156,   328,   329,   324,     0,
      95,    93,    94,    96,    97,    99,    98,     0,   100,     0,
      65,   101,   102,   103,     0,    60,    91,     0,     0,     0,
      38,     0,    89,    27,   300,   327,     0,   323,     0,    67,
       0,    51,    61,     0,    20,    81,   312,   313,   314,     0,
     315,     0,     0,   320,    35,   316,    41,   301,   303,   304,
     325,     0,     0,    70,    71,    73,    72,    74,    75,   318,
       0,    69,     0,    53,    92,    53,     0,    39,    37,     0,
       0,   318,     0,    64,    63,     0,     0,    62,    66,    54,
     149,   149,    23,    24,    22,   306,   321,     0,   302,    76,
      68,    56,     0,   153,   152,     0,     0,   149,     0,   147,
       0,   305,     0,   151,    55,    52,   148,     0,   184,   150,
      82,    57,     0,   160,     0,     0,     0,     0,     0,     0,
       0,   169,     0,   172,   175,     0,     0,     0,   240,     0,
     127,   128,   256,   257,   258,   300,   234,   174,   182,     0,
     183,   133,     0,   165,   236,   237,   238,   265,   181,   166,
     259,   119,     0,   178,     0,     0,     0,     0,   180,     0,
     167,   168,     0,     0,     0,     0,   339,   340,     0,   138,
     177,   259,   140,     0,    83,   179,   283,   131,   159,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   264,   263,     0,   318,     0,    58,     0,
       0,     0,   292,   293,   294,   295,   296,   297,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     142,   142,   283,   111,     0,   281,     0,   119,   134,   267,
     242,   243,   244,   245,   248,   249,   250,   251,   247,   246,
     252,   253,   254,   239,     0,     0,     0,   337,   338,   300,
       0,     0,     0,   233,   316,   191,     0,   261,   262,   260,
     121,   122,   123,   124,   126,   120,   119,     0,   288,   290,
       0,     0,   289,   291,     0,   230,   164,   170,   161,   171,
       0,     0,   229,   337,     0,   143,   273,     0,     0,    87,
       0,     0,     0,   278,     0,   337,     0,   269,   318,   222,
     223,   228,   227,   255,   192,   193,   194,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   318,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    59,   286,     0,   287,     0,     0,   318,
     163,     0,     0,     0,     0,     0,   139,   272,   141,   241,
       0,     0,     0,     0,   282,     0,   279,     0,   135,     0,
     129,   130,   132,     0,     0,     0,   266,     0,     0,   318,
       0,   318,   200,   209,   210,   214,   203,   204,   205,   208,
     206,   207,   198,   211,   212,   213,   202,     0,   196,   217,
     195,   197,   199,   201,   215,   216,     0,     0,   284,   285,
     231,     0,   162,   173,   176,   144,   337,   145,   275,   276,
     274,   113,     0,     0,     0,     0,    85,   112,     0,     0,
     273,   136,   271,   337,   268,   224,   220,     0,   225,     0,
     218,   219,   125,   232,     0,     0,    88,     0,     0,     0,
       0,   114,     0,   280,   267,   137,     0,   221,   226,   146,
       0,   105,     0,   106,   108,     0,   107,     0,     0,    86,
       0,   270,   277,     0,     0,     0,   117,     0,    84,     0,
     235,   104,   110,   109,     0,   119,   115,     0,   116,   118
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    12,    13,    14,    15,    23,    16,    17,    29,    65,
      96,   194,    66,    67,   103,   104,   132,   154,    18,    32,
      68,    19,    27,    20,    28,    93,   173,   190,   205,   212,
     221,   143,   121,   122,   123,   170,   171,   206,    21,    30,
      95,   175,   248,   333,   551,   462,   124,   125,   126,   526,
     399,   463,   568,   579,   584,   308,   375,   249,   472,   250,
     338,   404,   473,   251,   330,   331,   394,   207,   208,   209,
      70,    71,    72,   219,   387,   388,   252,   272,   274,   275,
      55,    56,   253,   286,   254,   283,   255,   256,   257,   307,
     258,   289,   406,   395,   457,   520,   335,   336,   259,   319,
      87,   156,   157,   158,    48,    49,   148,   159,   396,    41,
      42,   179,   180,    89,   136,    90,    91,    92,   278
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -445
static const yytype_int16 yypact[] =
{
     327,  -445,    23,    19,     3,    18,  -445,  -445,  -445,    42,
    -445,   140,   133,   327,  -445,  -445,   153,  -445,  -445,  -445,
    -445,  -445,    60,   174,   108,   115,  -445,   193,   -63,    12,
      95,   198,    14,  -445,  -445,  -445,  -445,  -445,  -445,    96,
     110,   104,   397,  -445,  -445,  -445,  -445,  -445,  -445,  -445,
    -445,  -445,  -445,  -445,  -445,   122,  -445,  -445,  -445,  -445,
    -445,   225,  -445,  -445,  -445,  -445,   190,  -445,   131,  -445,
      27,   134,  -445,  -445,  -445,  -445,   645,  -445,  -445,  -445,
    -445,  -445,  -445,  -445,  -445,  -445,  -445,  -445,   160,   -57,
    -445,  -445,  -445,   759,   118,   759,   125,  -445,  -445,  -445,
     645,   130,  -445,   236,   128,  -445,  -445,   645,  -445,   397,
    -445,  -445,  -445,  -445,  -445,  -445,  -445,   119,  -445,   123,
     124,  -445,  -445,  -445,   240,     4,  -445,    99,   241,   631,
    -445,   191,   759,  -445,   589,  -445,   397,  -445,   -58,    85,
     155,  -445,  -445,   759,  -445,  -445,  -445,  -445,  -445,   145,
    -445,   162,   168,  -445,  -445,   148,  -445,   200,  -445,  -445,
    -445,   149,   150,  -445,  -445,  -445,  -445,  -445,  -445,  -445,
     -50,  -445,   154,   268,  -445,   268,   -39,  -445,  -445,   157,
     397,  -445,   589,  -445,  -445,   158,    85,  -445,  -445,  -445,
       0,     0,  -445,  -445,  -445,  -445,   -57,   161,  -445,  -445,
    -445,  -445,   281,  -445,  -445,   285,   219,   121,   465,  -445,
     220,  -445,    12,  -445,  -445,  -445,  -445,   289,   528,  -445,
    -445,  -445,    72,  -445,   -65,   256,   339,   645,   197,   189,
     199,  -445,   186,   192,  -445,   -49,   557,   173,  -445,   303,
    -445,  -445,  -445,  -445,  -445,   589,  -445,  -445,  -445,   304,
    -445,  -445,   305,  -445,  -445,  -445,  -445,  -445,  -445,  -445,
     610,  -445,   290,  -445,   645,    91,   645,   159,  -445,   242,
    -445,  -445,    12,   244,    12,    12,  -445,  -445,   201,  -445,
    -445,    35,  -445,   202,  -445,  -445,   237,  -445,  -445,   203,
     645,   645,   645,   645,   645,   645,   645,   645,   645,   645,
     645,   645,   645,  -445,  -445,    62,  -445,   715,     8,   217,
     313,   -65,  -445,  -445,  -445,  -445,  -445,  -445,   -65,   645,
     314,   -65,   -65,   645,   645,   222,   197,   227,   229,   645,
     659,   659,   237,  -445,   310,  -445,   -34,  -445,  -445,   673,
    -445,  -445,  -445,  -445,  -445,  -445,  -445,  -445,  -445,  -445,
    -445,  -445,  -445,  -445,   603,   -49,   232,   221,   224,   589,
     645,   645,   645,  -445,   -84,   556,   223,  -445,  -445,  -445,
    -445,  -445,  -445,   231,  -445,  -445,  -445,   -65,  -445,  -445,
     338,   -65,  -445,  -445,   340,   -52,   258,   292,  -445,  -445,
     249,   251,  -445,   341,   -33,  -445,  -445,   -27,   -26,     1,
     197,   307,   252,     8,     7,   344,   -18,  -445,  -445,    -3,
      37,  -445,  -445,  -445,  -445,  -445,  -445,   645,   645,   645,
     645,   645,   645,   645,   645,   645,   645,   645,   645,   645,
     645,   645,  -445,   645,   645,   645,   645,   645,   645,   645,
     645,   253,   265,     8,  -445,   -65,  -445,   -65,   645,  -445,
    -445,   222,    99,    99,   645,   687,  -445,   176,  -445,  -445,
     645,   645,    49,   395,  -445,   381,  -445,   729,  -445,   645,
    -445,  -445,  -445,   398,   645,   701,  -445,   283,   645,  -445,
     645,  -445,  -445,  -445,  -445,  -445,  -445,  -445,  -445,  -445,
    -445,  -445,  -445,  -445,  -445,  -445,  -445,   293,  -445,  -445,
    -445,  -445,  -445,  -445,  -445,  -445,   645,   294,  -445,  -445,
    -445,   295,  -445,  -445,  -445,  -445,   387,  -445,  -445,   291,
    -445,  -445,   416,   645,   645,   359,   134,  -445,   197,   299,
    -445,  -445,  -445,   404,  -445,  -445,  -445,   306,  -445,   308,
    -445,  -445,  -445,  -445,   645,   316,  -445,    11,   425,    13,
      24,  -445,   427,  -445,   673,   176,   645,  -445,  -445,  -445,
     309,  -445,   645,  -445,  -445,   645,  -445,   645,   129,  -445,
     -15,  -445,  -445,   431,   433,   435,  -445,   197,  -445,   440,
    -445,  -445,  -445,  -445,    12,  -445,  -445,   222,     8,  -445
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -445,  -445,  -445,   434,    87,  -445,  -445,  -445,  -445,   228,
    -445,  -445,  -445,   388,  -445,  -445,  -445,    98,  -445,  -445,
    -445,    94,  -445,  -445,  -445,  -445,  -445,   280,  -445,  -445,
    -445,  -445,  -445,  -445,  -445,  -445,   272,   276,  -445,  -445,
    -445,  -445,  -445,  -445,  -445,  -445,   -66,  -445,   328,  -445,
    -445,  -445,  -445,  -445,  -445,  -324,  -445,  -445,  -445,  -445,
    -445,  -445,  -445,  -445,  -445,  -445,   141,  -445,  -445,   267,
     275,  -445,   -70,  -445,  -445,  -444,  -445,  -445,  -445,  -445,
    -194,   105,  -445,  -445,  -445,  -445,  -445,  -445,     9,  -445,
    -226,  -445,   -74,  -333,   -46,  -445,    84,   163,  -445,   238,
    -125,   245,  -445,   322,  -445,   182,  -222,   362,   -42,  -165,
    -445,  -445,  -445,   330,  -445,   -77,  -445,  -124,   164
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -260
static const yytype_int16 yytable[] =
{
      88,   105,   263,   144,   185,   201,   407,   512,   -90,   155,
     280,   468,   460,   403,   108,   561,   197,   564,   222,   448,
       2,   186,     3,     4,   370,   371,   372,   373,   566,   128,
      22,   -40,   137,   303,   106,   304,     5,   401,   455,  -259,
     146,   100,    44,    59,   455,   401,    45,   161,   147,    46,
      47,   162,   443,   475,   276,   101,   475,   155,   130,   160,
     277,    50,    51,    52,    53,   135,   152,    88,   478,   449,
     192,   469,   -77,   193,   187,   142,   353,   109,   325,   363,
     327,   328,   562,   354,   565,   461,   470,   150,   471,   378,
     402,   456,   150,   260,    88,   567,   379,   458,   459,   382,
     383,   311,   -90,   269,   102,   374,   476,   202,   480,   580,
       9,   281,    60,    25,   -44,   203,   204,    54,   479,    64,
     155,    61,   517,   355,   356,   523,    69,   521,    24,    62,
      63,   524,   525,    34,   163,   164,   165,   166,    88,    26,
     150,   366,   534,   589,    33,   312,   313,   314,   315,   316,
     317,    31,   303,    64,   304,   444,   576,    36,   481,   446,
      69,   337,   318,    77,    78,    79,    80,   242,    81,   321,
      37,   357,    83,    84,   358,   359,    86,   261,    38,    39,
     364,   262,   368,   265,   267,   268,    40,   360,   361,   362,
     167,   518,   577,   -78,   168,   519,     2,    43,     3,     4,
      57,   389,    58,   150,   578,    73,   169,   337,    82,    83,
      84,    85,     5,   312,   313,   314,   315,   316,   317,    59,
      74,   407,   310,   508,   320,   509,    75,    94,   202,    97,
     322,    99,    60,   107,   155,   129,   203,   204,   127,   131,
     133,   134,   138,   477,   141,   145,   139,   140,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
     352,   588,   151,   365,   172,   176,   178,   497,   177,   181,
     264,   182,   189,   183,   184,   464,   337,   380,   188,   195,
     199,   384,   385,   211,   511,   213,     9,   392,    60,   214,
     -45,   215,   220,   223,   270,   273,   282,    61,    77,    78,
      79,    80,   -21,    81,   271,    62,    63,   284,   287,   288,
     309,    86,   410,   324,   537,   326,   539,   150,   414,   415,
     416,   329,   376,   377,   381,   332,   339,   386,   513,   514,
     400,     1,   390,     2,   391,     3,     4,   412,    77,    78,
      79,    80,   281,    81,  -257,   441,   334,  -258,   445,     5,
     447,    86,     6,   266,   442,   450,     7,    77,    78,    79,
      80,   454,    81,   451,   474,    82,    83,    84,    85,   452,
      86,   453,   467,   506,   507,   482,   483,   484,   485,   486,
     487,   488,   489,   490,   491,   492,   493,   494,   495,   496,
     587,   498,   499,   500,   501,   502,   503,   504,   505,   527,
     550,   528,   531,   553,     8,   535,   510,   544,    77,    78,
      79,    80,   515,    81,   545,   540,   465,   543,   542,   522,
     546,    86,   554,     9,   556,   560,    10,   530,   557,   563,
     558,   569,   532,   572,    11,   581,   536,   582,   538,   583,
      77,    78,    79,    80,   586,    81,   247,    35,    82,    83,
      84,    85,   585,    86,    98,   191,   552,   413,   200,   409,
      77,    78,    79,    80,   541,    81,   217,   210,   549,  -154,
      76,   174,   397,    86,   216,  -154,   529,  -154,  -154,  -154,
     570,   547,   548,   218,   555,   466,  -154,  -154,  -154,   369,
     285,   149,  -154,  -154,  -154,   398,     0,  -154,    77,    78,
      79,    80,   559,    81,   198,   323,    82,    83,    84,    85,
     196,    86,     0,     0,   571,     0,     0,     0,     0,   411,
     573,     0,     0,   574,     0,   575,  -154,     0,     0,  -154,
    -154,  -154,     0,     0,     0,     0,     0,     0,   224,  -154,
     225,   226,   227,  -154,     0,  -154,     0,     0,     0,   228,
     229,   230,     0,     0,     0,   231,   232,   233,     0,     0,
     234,     0,     0,    60,     0,     0,  -154,  -154,  -154,  -154,
    -154,  -154,     0,     0,  -154,     0,     0,  -154,  -154,  -154,
       0,     0,     0,     0,     0,     0,     0,     0,  -154,   235,
       0,     0,   236,   237,   238,     0,     0,   417,     0,     0,
       0,     0,   239,   418,   419,     0,   240,     0,   241,   420,
     421,   422,   423,   424,   425,   426,     0,     0,     0,     0,
       0,     0,     0,   427,   428,   429,   430,     0,     0,    77,
      78,    79,    80,   242,    81,     0,     0,   243,     0,     0,
     244,   245,    86,   290,   291,   292,   293,   294,   295,   296,
     297,   246,   298,   299,   300,   301,   302,     0,    77,    78,
      79,    80,   242,    81,     0,     0,   243,     0,     0,   244,
       0,    86,     0,     0,   431,     0,     0,   432,     0,     0,
     279,     0,   433,   434,   435,   436,   437,   438,   439,   440,
      77,    78,    79,    80,   146,    81,     0,     0,    82,    83,
      84,    85,   147,    86,    77,    78,    79,    80,    54,    81,
     153,     0,    82,    83,    84,    85,     0,    86,     0,     0,
       0,     0,     0,     0,   408,     0,     0,   303,     0,   304,
     305,   306,    77,    78,    79,    80,   146,    81,     0,     0,
      82,    83,    84,    85,   147,    86,    77,    78,    79,    80,
       0,    81,     0,     0,    82,    83,    84,    85,     0,    86,
      77,    78,    79,    80,     0,    81,     0,     0,   393,    83,
      84,    85,     0,    86,    77,    78,    79,    80,     0,    81,
       0,     0,   405,    83,    84,    85,     0,    86,    77,    78,
      79,    80,     0,    81,     0,     0,   516,    83,    84,    85,
       0,    86,    77,    78,    79,    80,     0,    81,     0,     0,
     533,    83,    84,    85,     0,    86,    77,    78,    79,    80,
      44,    81,     0,     0,   367,     0,     0,     0,    47,    86,
      77,    78,    79,    80,   242,    81,     0,     0,   243,     0,
       0,   244,     0,    86,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120
};

static const yytype_int16 yycheck[] =
{
      42,    71,   224,   127,   169,     5,   339,   451,     4,   134,
     236,     4,    11,   337,    71,     4,   181,     4,   212,    71,
       6,    71,     8,     9,    16,    17,    18,    19,     4,    95,
       7,     4,   109,   117,    76,   119,    22,    71,    71,   123,
     105,    14,   105,    29,    71,    71,   109,   105,   113,   112,
     113,   109,   376,    71,   103,    28,    71,   182,   100,   136,
     109,    49,    50,    51,    52,   107,   132,   109,    71,   121,
     109,    64,    72,   112,   124,    71,    14,   134,   272,   305,
     274,   275,    71,    21,    71,    84,    79,   129,    81,   311,
     124,   124,   134,   218,   136,    71,   318,   124,   124,   321,
     322,    10,    98,   228,    77,    97,   124,   107,    71,   124,
      96,   236,    98,   110,   100,   115,   116,   105,   121,    32,
     245,   107,   455,    61,    62,    76,    32,   460,   109,   115,
     116,    82,    83,     0,    49,    50,    51,    52,   180,   121,
     182,   306,   475,   587,     4,    54,    55,    56,    57,    58,
      59,   109,   117,    66,   119,   377,    27,     4,   121,   381,
      66,   286,    71,   101,   102,   103,   104,   105,   106,    10,
     110,   109,   110,   111,   112,   113,   114,   105,     4,    71,
     305,   109,   307,   225,   226,   227,    71,   125,   126,   127,
     105,    15,    63,    72,   109,    19,     6,     4,     8,     9,
     105,   326,     4,   245,    75,   109,   121,   332,   109,   110,
     111,   112,    22,    54,    55,    56,    57,    58,    59,    29,
     110,   554,   264,   445,   266,   447,   122,   105,   107,     4,
      71,   100,    98,    73,   359,   110,   115,   116,   120,   109,
       4,   113,   123,   408,     4,     4,   123,   123,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   585,    71,   305,   109,   120,    98,   432,   106,   121,
      14,    71,     4,   124,   124,   400,   401,   319,   124,   122,
     122,   323,   324,   122,   449,     4,    96,   329,    98,     4,
     100,    72,    72,     4,   105,   109,   123,   107,   101,   102,
     103,   104,   110,   106,   105,   115,   116,     4,     4,     4,
      20,   114,   354,    71,   479,    71,   481,   359,   360,   361,
     362,   120,   105,    10,    10,   123,   123,   105,   452,   453,
      20,     4,   105,     6,   105,     8,     9,   105,   101,   102,
     103,   104,   467,   106,   123,   122,   109,   123,    10,    22,
      10,   114,    25,    14,   123,    97,    29,   101,   102,   103,
     104,    20,   106,    71,    20,   109,   110,   111,   112,   120,
     114,   120,   120,   120,   109,   417,   418,   419,   420,   421,
     422,   423,   424,   425,   426,   427,   428,   429,   430,   431,
     584,   433,   434,   435,   436,   437,   438,   439,   440,     4,
     525,    20,     4,   528,    77,   122,   448,    20,   101,   102,
     103,   104,   454,   106,   123,   122,   109,   122,   124,   461,
       4,   114,   123,    96,    20,   109,    99,   469,   122,     4,
     122,     4,   474,   124,   107,     4,   478,     4,   480,     4,
     101,   102,   103,   104,     4,   106,   218,    13,   109,   110,
     111,   112,   577,   114,    66,   175,   526,   359,   186,   354,
     101,   102,   103,   104,   506,   106,     1,   191,   109,     4,
      73,   143,   331,   114,   207,    10,   467,    12,    13,    14,
     554,   523,   524,   208,   530,   401,    21,    22,    23,   307,
     245,   129,    27,    28,    29,   332,    -1,    32,   101,   102,
     103,   104,   544,   106,   182,   267,   109,   110,   111,   112,
     180,   114,    -1,    -1,   556,    -1,    -1,    -1,    -1,   355,
     562,    -1,    -1,   565,    -1,   567,    61,    -1,    -1,    64,
      65,    66,    -1,    -1,    -1,    -1,    -1,    -1,    10,    74,
      12,    13,    14,    78,    -1,    80,    -1,    -1,    -1,    21,
      22,    23,    -1,    -1,    -1,    27,    28,    29,    -1,    -1,
      32,    -1,    -1,    98,    -1,    -1,   101,   102,   103,   104,
     105,   106,    -1,    -1,   109,    -1,    -1,   112,   113,   114,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   123,    61,
      -1,    -1,    64,    65,    66,    -1,    -1,    41,    -1,    -1,
      -1,    -1,    74,    47,    48,    -1,    78,    -1,    80,    53,
      54,    55,    56,    57,    58,    59,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    68,    69,    70,    -1,    -1,   101,
     102,   103,   104,   105,   106,    -1,    -1,   109,    -1,    -1,
     112,   113,   114,    33,    34,    35,    36,    37,    38,    39,
      40,   123,    42,    43,    44,    45,    46,    -1,   101,   102,
     103,   104,   105,   106,    -1,    -1,   109,    -1,    -1,   112,
      -1,   114,    -1,    -1,   118,    -1,    -1,   121,    -1,    -1,
     123,    -1,   126,   127,   128,   129,   130,   131,   132,   133,
     101,   102,   103,   104,   105,   106,    -1,    -1,   109,   110,
     111,   112,   113,   114,   101,   102,   103,   104,   105,   106,
     121,    -1,   109,   110,   111,   112,    -1,   114,    -1,    -1,
      -1,    -1,    -1,    -1,   121,    -1,    -1,   117,    -1,   119,
     120,   121,   101,   102,   103,   104,   105,   106,    -1,    -1,
     109,   110,   111,   112,   113,   114,   101,   102,   103,   104,
      -1,   106,    -1,    -1,   109,   110,   111,   112,    -1,   114,
     101,   102,   103,   104,    -1,   106,    -1,    -1,   109,   110,
     111,   112,    -1,   114,   101,   102,   103,   104,    -1,   106,
      -1,    -1,   109,   110,   111,   112,    -1,   114,   101,   102,
     103,   104,    -1,   106,    -1,    -1,   109,   110,   111,   112,
      -1,   114,   101,   102,   103,   104,    -1,   106,    -1,    -1,
     109,   110,   111,   112,    -1,   114,   101,   102,   103,   104,
     105,   106,    -1,    -1,   109,    -1,    -1,    -1,   113,   114,
     101,   102,   103,   104,   105,   106,    -1,    -1,   109,    -1,
      -1,   112,    -1,   114,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     6,     8,     9,    22,    25,    29,    77,    96,
      99,   107,   136,   137,   138,   139,   141,   142,   153,   156,
     158,   173,     7,   140,   109,   110,   121,   157,   159,   143,
     174,   109,   154,     4,     0,   138,     4,   110,     4,    71,
      71,   244,   245,     4,   105,   109,   112,   113,   239,   240,
      49,    50,    51,    52,   105,   215,   216,   105,     4,    29,
      98,   107,   115,   116,   139,   144,   147,   148,   155,   156,
     205,   206,   207,   109,   110,   122,    73,   101,   102,   103,
     104,   106,   109,   110,   111,   112,   114,   235,   243,   248,
     250,   251,   252,   160,   105,   175,   145,     4,   148,   100,
      14,    28,    77,   149,   150,   207,   243,    73,    71,   134,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,   167,   168,   169,   181,   182,   183,   120,   181,   110,
     243,   109,   151,     4,   113,   243,   249,   250,   123,   123,
     123,     4,    71,   166,   252,     4,   105,   113,   241,   242,
     243,    71,   181,   121,   152,   235,   236,   237,   238,   242,
     250,   105,   109,    49,    50,    51,    52,   105,   109,   121,
     170,   171,   109,   161,   183,   176,   120,   106,    98,   246,
     247,   121,    71,   124,   124,   244,    71,   124,   124,     4,
     162,   162,   109,   112,   146,   122,   248,   244,   238,   122,
     171,     5,   107,   115,   116,   163,   172,   202,   203,   204,
     172,   122,   164,     4,     4,    72,   204,     1,   205,   208,
      72,   165,   215,     4,    10,    12,    13,    14,    21,    22,
      23,    27,    28,    29,    32,    61,    64,    65,    66,    74,
      78,    80,   105,   109,   112,   113,   123,   144,   177,   192,
     194,   198,   211,   217,   219,   221,   222,   223,   225,   233,
     235,   105,   109,   241,    14,   243,    14,   243,   243,   235,
     105,   105,   212,   109,   213,   214,   103,   109,   253,   123,
     225,   235,   123,   220,     4,   236,   218,     4,     4,   226,
      33,    34,    35,    36,    37,    38,    39,    40,    42,    43,
      44,    45,    46,   117,   119,   120,   121,   224,   190,    20,
     243,    10,    54,    55,    56,    57,    58,    59,    71,   234,
     243,    10,    71,   234,    71,   215,    71,   215,   215,   120,
     199,   200,   123,   178,   109,   231,   232,   235,   195,   123,
     243,   243,   243,   243,   243,   243,   243,   243,   243,   243,
     243,   243,   243,    14,    21,    61,    62,   109,   112,   113,
     125,   126,   127,   225,   235,   243,   244,   109,   235,   240,
      16,    17,    18,    19,    97,   191,   105,    10,   241,   241,
     243,    10,   241,   241,   243,   243,   105,   209,   210,   235,
     105,   105,   243,   109,   201,   228,   243,   201,   232,   185,
      20,    71,   124,   190,   196,   109,   227,   228,   121,   216,
     243,   253,   105,   152,   243,   243,   243,    41,    47,    48,
      53,    54,    55,    56,    57,    58,    59,    67,    68,    69,
      70,   118,   121,   126,   127,   128,   129,   130,   131,   132,
     133,   122,   123,   190,   241,    10,   241,    10,    71,   121,
      97,    71,   120,   120,    20,    71,   124,   229,   124,   124,
      11,    84,   180,   186,   235,   109,   231,   120,     4,    64,
      79,    81,   193,   197,    20,    71,   124,   244,    71,   121,
      71,   121,   243,   243,   243,   243,   243,   243,   243,   243,
     243,   243,   243,   243,   243,   243,   243,   244,   243,   243,
     243,   243,   243,   243,   243,   243,   120,   109,   241,   241,
     243,   244,   210,   252,   252,   243,   109,   228,    15,    19,
     230,   228,   243,    76,    82,    83,   184,     4,    20,   223,
     243,     4,   243,   109,   228,   122,   243,   244,   243,   244,
     122,   243,   124,   122,    20,   123,     4,   243,   243,   109,
     235,   179,   207,   235,   123,   229,    20,   122,   122,   243,
     109,     4,    71,     4,     4,    71,     4,    71,   187,     4,
     227,   243,   124,   243,   243,   243,    27,    63,    75,   188,
     124,     4,     4,     4,   189,   235,     4,   215,   190,   210
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (yyscanner, interp, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval, yyscanner, interp)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, yyscanner, interp); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, void *yyscanner, Parrot_Interp interp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yyscanner, interp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    void *yyscanner;
    Parrot_Interp interp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yyscanner);
  YYUSE (interp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, void *yyscanner, Parrot_Interp interp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yyscanner, interp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    void *yyscanner;
    Parrot_Interp interp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yyscanner, interp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule, void *yyscanner, Parrot_Interp interp)
#else
static void
yy_reduce_print (yyvsp, yyrule, yyscanner, interp)
    YYSTYPE *yyvsp;
    int yyrule;
    void *yyscanner;
    Parrot_Interp interp;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       , yyscanner, interp);
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule, yyscanner, interp); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, void *yyscanner, Parrot_Interp interp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yyscanner, interp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    void *yyscanner;
    Parrot_Interp interp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yyscanner);
  YYUSE (interp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void *yyscanner, Parrot_Interp interp);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */






/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *yyscanner, Parrot_Interp interp)
#else
int
yyparse (yyscanner, interp)
    void *yyscanner;
    Parrot_Interp interp;
#endif
#endif
{
  /* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;

  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 605 "imcc.y"
    { if (yynerrs) YYABORT; (yyval.i) = 0; ;}
    break;

  case 5:
#line 614 "imcc.y"
    { (yyval.i) = (yyvsp[(1) - (1)].i); ;}
    break;

  case 6:
#line 615 "imcc.y"
    { (yyval.i) = (yyvsp[(1) - (1)].i); ;}
    break;

  case 7:
#line 616 "imcc.y"
    { (yyval.i) = (yyvsp[(1) - (1)].i);
                     imc_close_unit(interp, IMCC_INFO(interp)->cur_unit);
                     IMCC_INFO(interp)->cur_unit = 0; ;}
    break;

  case 8:
#line 619 "imcc.y"
    { (yyval.i) = (yyvsp[(1) - (1)].i);
                     imc_close_unit(interp, IMCC_INFO(interp)->cur_unit);
                     IMCC_INFO(interp)->cur_unit = 0; ;}
    break;

  case 9:
#line 622 "imcc.y"
    { (yyval.i) = (yyvsp[(1) - (1)].i);
                     imc_close_unit(interp, IMCC_INFO(interp)->cur_unit);
                     IMCC_INFO(interp)->cur_unit = 0; ;}
    break;

  case 10:
#line 625 "imcc.y"
    { (yyval.i) = 0; ;}
    break;

  case 11:
#line 626 "imcc.y"
    { (yyval.i) = 0; ;}
    break;

  case 12:
#line 627 "imcc.y"
    { (yyval.i) = 0; ;}
    break;

  case 13:
#line 630 "imcc.y"
    { (yyval.i) = 0; ;}
    break;

  case 14:
#line 631 "imcc.y"
    { (yyval.i) = 0; ;}
    break;

  case 15:
#line 632 "imcc.y"
    { (yyval.i) = 0; do_loadlib(interp, (yyvsp[(2) - (3)].s)); ;}
    break;

  case 16:
#line 636 "imcc.y"
    { if ((yyvsp[(2) - (2)].s))
                          IMCC_INFO(interp)->state->pragmas |= PR_N_OPERATORS;
                      else
                          IMCC_INFO(interp)->state->pragmas &= ~PR_N_OPERATORS;
                    ;}
    break;

  case 17:
#line 644 "imcc.y"
    {
            STRING *hll_name = string_unescape_cstring(interp, (yyvsp[(2) - (4)].s) + 1, '"', NULL);
            STRING *hll_lib  = string_unescape_cstring(interp, (yyvsp[(4) - (4)].s) + 1, '"', NULL);
            PMC    *ignored;
            CONTEXT(((Interp*)interp)->ctx)->current_HLL =
                Parrot_register_HLL(interp, hll_name);
            ignored = Parrot_load_lib(interp, hll_lib, NULL);
            Parrot_register_HLL_lib(interp, hll_lib);
            IMCC_INFO(interp)->cur_namespace = NULL;
            (yyval.t) = 0;
         ;}
    break;

  case 18:
#line 656 "imcc.y"
    {
             Parrot_register_HLL_type(interp,
                CONTEXT(((Interp*)interp)->ctx)->current_HLL, atoi((yyvsp[(2) - (4)].s)), atoi((yyvsp[(4) - (4)].s)));
             (yyval.t) = 0;
         ;}
    break;

  case 19:
#line 664 "imcc.y"
    { is_def=1; ;}
    break;

  case 20:
#line 665 "imcc.y"
    { mk_const_ident(interp, (yyvsp[(4) - (6)].s), (yyvsp[(3) - (6)].t), (yyvsp[(6) - (6)].sr), 1); is_def=0; ;}
    break;

  case 21:
#line 669 "imcc.y"
    { is_def=1; ;}
    break;

  case 22:
#line 670 "imcc.y"
    { (yyval.i) = mk_pmc_const(interp, IMCC_INFO(interp)->cur_unit, (yyvsp[(3) - (6)].s), (yyvsp[(4) - (6)].sr), (yyvsp[(6) - (6)].s)); is_def=0; ;}
    break;

  case 27:
#line 683 "imcc.y"
    { (yyval.i) = 0;  ;}
    break;

  case 28:
#line 684 "imcc.y"
    { (yyval.i) = 0;  ;}
    break;

  case 29:
#line 685 "imcc.y"
    { (yyval.i) = 0;  ;}
    break;

  case 30:
#line 686 "imcc.y"
    { (yyval.i) = 0;  ;}
    break;

  case 31:
#line 687 "imcc.y"
    { (yyval.i) = (yyvsp[(1) - (1)].i); ;}
    break;

  case 34:
#line 692 "imcc.y"
    { clear_state(interp); ;}
    break;

  case 35:
#line 694 "imcc.y"
    { (yyval.i) = INS(interp, IMCC_INFO(interp)->cur_unit,
                              (yyvsp[(2) - (3)].s), 0, IMCC_INFO(interp)->regs,
                              IMCC_INFO(interp)->nargs, IMCC_INFO(interp) -> keyvec, 1);
                     free((yyvsp[(2) - (3)].s)); ;}
    break;

  case 36:
#line 699 "imcc.y"
    {
                    imc_close_unit(interp, IMCC_INFO(interp)->cur_unit);
                    IMCC_INFO(interp)->cur_unit = imc_open_unit(interp, IMC_PASM);
                    ;}
    break;

  case 37:
#line 704 "imcc.y"
    {
                     (yyval.i) = iSUBROUTINE(interp, IMCC_INFO(interp)->cur_unit,
                                mk_sub_label(interp, (yyvsp[(4) - (4)].s)));
                     IMCC_INFO(interp)->cur_call->pcc_sub->pragma = (yyvsp[(3) - (4)].t);
                   ;}
    break;

  case 38:
#line 710 "imcc.y"
    {  (yyval.i) =MK_I(interp, IMCC_INFO(interp)->cur_unit, "null", 1, (yyvsp[(2) - (2)].sr)); ;}
    break;

  case 39:
#line 712 "imcc.y"
    {
                       SymReg *r = mk_pasm_reg(interp, (yyvsp[(4) - (4)].s));
                       set_lexical(interp, r, (yyvsp[(2) - (4)].s)); (yyval.i) = 0;
                   ;}
    break;

  case 40:
#line 716 "imcc.y"
    { (yyval.i) = 0;;}
    break;

  case 42:
#line 724 "imcc.y"
    { IMCC_INFO(interp)->cur_unit = imc_open_unit(interp, IMC_PASM); ;}
    break;

  case 43:
#line 726 "imcc.y"
    { /*
                      if (optimizer_level & OPT_PASM)
                         imc_compile_unit(interp, IMCC_INFO(interp)->cur_unit);
                         emit_flush(interp);
                     */
                     (yyval.i)=0; ;}
    break;

  case 46:
#line 741 "imcc.y"
    {
                    int re_open = 0;
                    (yyval.i) = 0;
                    if (IMCC_INFO(interp)->state->pasm_file && IMCC_INFO(interp)->cur_namespace) {
                        imc_close_unit(interp, IMCC_INFO(interp)->cur_unit);
                        re_open = 1;
                    }
                    IMCC_INFO(interp)->cur_namespace = (yyvsp[(2) - (3)].sr);
                    if (re_open)
                        IMCC_INFO(interp)->cur_unit = imc_open_unit(interp, IMC_PASM);
                ;}
    break;

  case 47:
#line 755 "imcc.y"
    { (yyval.sr) = (yyvsp[(2) - (3)].sr); ;}
    break;

  case 48:
#line 756 "imcc.y"
    { (yyval.sr) = NULL; ;}
    break;

  case 49:
#line 761 "imcc.y"
    {
           IMCC_INFO(interp)->cur_unit = imc_open_unit(interp, IMC_PCCSUB);
        ;}
    break;

  case 50:
#line 765 "imcc.y"
    {
          iSUBROUTINE(interp, IMCC_INFO(interp)->cur_unit, (yyvsp[(3) - (3)].sr));
        ;}
    break;

  case 51:
#line 768 "imcc.y"
    { IMCC_INFO(interp)->cur_call->pcc_sub->pragma = (yyvsp[(5) - (6)].t); ;}
    break;

  case 52:
#line 770 "imcc.y"
    { (yyval.i) = 0; IMCC_INFO(interp)->cur_call = NULL; ;}
    break;

  case 53:
#line 774 "imcc.y"
    { (yyval.sr) = 0; ;}
    break;

  case 54:
#line 775 "imcc.y"
    { (yyval.sr) = 0; ;}
    break;

  case 55:
#line 776 "imcc.y"
    {
       if (IMCC_INFO(interp)->adv_named_id) {
             add_pcc_named_param(interp,IMCC_INFO(interp)->cur_call,
                                 IMCC_INFO(interp)->adv_named_id,(yyvsp[(2) - (3)].sr));
             IMCC_INFO(interp)->adv_named_id = NULL;
         }
         else add_pcc_param(IMCC_INFO(interp)->cur_call, (yyvsp[(2) - (3)].sr));
   ;}
    break;

  case 56:
#line 787 "imcc.y"
    { is_def=1; ;}
    break;

  case 57:
#line 787 "imcc.y"
    { (yyval.sr) = (yyvsp[(3) - (3)].sr); is_def=0; ;}
    break;

  case 58:
#line 791 "imcc.y"
    { if ((yyvsp[(3) - (3)].t) & VT_UNIQUE_REG)
                                             (yyval.sr) = mk_ident_ur(interp, (yyvsp[(2) - (3)].s), (yyvsp[(1) - (3)].t));
                                         else
                                             (yyval.sr) = mk_ident(interp, (yyvsp[(2) - (3)].s), (yyvsp[(1) - (3)].t));
                                         (yyval.sr)->type |= (yyvsp[(3) - (3)].t); ;}
    break;

  case 59:
#line 796 "imcc.y"
    {
                                         if ((yyvsp[(5) - (5)].t) & VT_UNIQUE_REG)
                                             (yyval.sr) = mk_ident_ur(interp, (yyvsp[(4) - (5)].s), (yyvsp[(1) - (5)].t));
                                         else
                                             (yyval.sr) = mk_ident(interp, (yyvsp[(4) - (5)].s), (yyvsp[(1) - (5)].t));
                                         (yyval.sr)->type |= (yyvsp[(5) - (5)].t);
                                         adv_named_set(interp,(yyvsp[(2) - (5)].s));;}
    break;

  case 60:
#line 806 "imcc.y"
    { (yyval.t) = 0;  ;}
    break;

  case 62:
#line 811 "imcc.y"
    { (yyval.t) = 0; ;}
    break;

  case 63:
#line 815 "imcc.y"
    { (yyval.t) = 0; IMCC_INFO(interp)->cur_unit->outer =
                     mk_sub_address_fromc(interp, (yyvsp[(3) - (4)].s)); ;}
    break;

  case 64:
#line 818 "imcc.y"
    { (yyval.t) = 0; IMCC_INFO(interp)->cur_unit->outer =
                     mk_const(interp, (yyvsp[(3) - (4)].s), 'S'); ;}
    break;

  case 65:
#line 823 "imcc.y"
    { (yyval.t) = 0;
                       IMCC_INFO(interp)->cur_unit->vtable_name = NULL;
                       IMCC_INFO(interp)->cur_unit->is_vtable_method = 1; ;}
    break;

  case 66:
#line 827 "imcc.y"
    { (yyval.t) = 0;
                       IMCC_INFO(interp)->cur_unit->vtable_name = strdup((yyvsp[(3) - (4)].s));
                       IMCC_INFO(interp)->cur_unit->is_vtable_method = 1; ;}
    break;

  case 67:
#line 833 "imcc.y"
    { add_pcc_multi(IMCC_INFO(interp)->cur_call, NULL); ;}
    break;

  case 68:
#line 834 "imcc.y"
    { (yyval.t) = 0; add_pcc_multi(IMCC_INFO(interp)->cur_call, (yyvsp[(3) - (3)].sr)); ;}
    break;

  case 69:
#line 835 "imcc.y"
    { (yyval.t) = 0;  add_pcc_multi(IMCC_INFO(interp)->cur_call, (yyvsp[(1) - (1)].sr));;}
    break;

  case 70:
#line 839 "imcc.y"
    { (yyval.sr) = mk_const(interp, str_dup("INTVAL"), 'S'); ;}
    break;

  case 71:
#line 840 "imcc.y"
    { (yyval.sr) = mk_const(interp, str_dup("FLOATVAL"), 'S'); ;}
    break;

  case 72:
#line 841 "imcc.y"
    { (yyval.sr) = mk_const(interp, str_dup("PMC"), 'S'); ;}
    break;

  case 73:
#line 842 "imcc.y"
    { (yyval.sr) = mk_const(interp, str_dup("STRING"), 'S'); ;}
    break;

  case 74:
#line 843 "imcc.y"
    {
                          SymReg *r;
                          if (strcmp((yyvsp[(1) - (1)].s), "_"))
                              r = mk_const(interp, (yyvsp[(1) - (1)].s), 'S');
                          else {
                              free((yyvsp[(1) - (1)].s)),
                              r = mk_const(interp, str_dup("PMC"), 'S');
                           }
                           (yyval.sr) = r;
                      ;}
    break;

  case 75:
#line 853 "imcc.y"
    {
                          SymReg *r;
                          if (strcmp((yyvsp[(1) - (1)].s), "_"))
                              r = mk_const(interp, (yyvsp[(1) - (1)].s), 'S');
                          else {
                              free((yyvsp[(1) - (1)].s)),
                              r = mk_const(interp, str_dup("PMC"), 'S');
                           }
                           (yyval.sr) = r;
                      ;}
    break;

  case 76:
#line 863 "imcc.y"
    { (yyval.sr) = (yyvsp[(2) - (3)].sr); ;}
    break;

  case 79:
#line 872 "imcc.y"
    { IMCC_INFO(interp)->cur_unit = imc_open_unit(interp, IMC_PCCSUB); ;}
    break;

  case 80:
#line 873 "imcc.y"
    { iSUBROUTINE(interp, IMCC_INFO(interp)->cur_unit, mk_sub_label(interp, (yyvsp[(3) - (3)].s))); ;}
    break;

  case 81:
#line 874 "imcc.y"
    { IMCC_INFO(interp)->cur_call->pcc_sub->pragma = (yyvsp[(5) - (6)].t); ;}
    break;

  case 82:
#line 876 "imcc.y"
    { (yyval.i) = 0; IMCC_INFO(interp)->cur_call = NULL; ;}
    break;

  case 83:
#line 881 "imcc.y"
    {
            char name[128];
            SymReg * r, *r1;
            Instruction *i;

            sprintf(name, "%cpcc_sub_call_%d",
                    IMCC_INTERNAL_CHAR, IMCC_INFO(interp)->cnr++);
            (yyval.sr) = r = mk_pcc_sub(interp, str_dup(name), 0);
            /* this mid rule action has the semantic value of the
             * sub SymReg.
             * This is used below to append args & results
             */
            i = iLABEL(interp, IMCC_INFO(interp)->cur_unit, r);
            IMCC_INFO(interp)->cur_call = r;
            i->type = ITPCCSUB;
            /*
             * if we are inside a pcc_sub mark the sub as doing a
             * sub call; the sub is in r[0] of the first ins
             */
            r1 = IMCC_INFO(interp)->cur_unit->instructions->r[0];
            if (r1 && r1->pcc_sub)
                r1->pcc_sub->calls_a_sub |= 1;
         ;}
    break;

  case 84:
#line 909 "imcc.y"
    { (yyval.i) = 0; IMCC_INFO(interp)->cur_call = NULL; ;}
    break;

  case 85:
#line 913 "imcc.y"
    { (yyval.i) = NULL;  IMCC_INFO(interp)->cur_call->pcc_sub->label = 0; ;}
    break;

  case 86:
#line 914 "imcc.y"
    { (yyval.i) = NULL;  IMCC_INFO(interp)->cur_call->pcc_sub->label = 1; ;}
    break;

  case 87:
#line 918 "imcc.y"
    { (yyval.i) = NULL; ;}
    break;

  case 88:
#line 920 "imcc.y"
    { (yyval.i) = NULL;  IMCC_INFO(interp)->cur_call->pcc_sub->object = (yyvsp[(2) - (3)].sr); ;}
    break;

  case 89:
#line 924 "imcc.y"
    { (yyval.t) = 0; ;}
    break;

  case 91:
#line 929 "imcc.y"
    { (yyval.t) = (yyvsp[(1) - (1)].t); ;}
    break;

  case 92:
#line 930 "imcc.y"
    { (yyval.t) = (yyvsp[(1) - (3)].t) | (yyvsp[(3) - (3)].t); ;}
    break;

  case 93:
#line 934 "imcc.y"
    {  (yyval.t) = P_LOAD; ;}
    break;

  case 94:
#line 935 "imcc.y"
    {  (yyval.t) = P_INIT; ;}
    break;

  case 95:
#line 936 "imcc.y"
    {  (yyval.t) = P_MAIN; ;}
    break;

  case 96:
#line 937 "imcc.y"
    {  (yyval.t) = P_IMMEDIATE; ;}
    break;

  case 97:
#line 938 "imcc.y"
    {  (yyval.t) = P_POSTCOMP; ;}
    break;

  case 98:
#line 939 "imcc.y"
    {  (yyval.t) = P_ANON; ;}
    break;

  case 99:
#line 940 "imcc.y"
    {  (yyval.t) = P_METHOD; ;}
    break;

  case 100:
#line 941 "imcc.y"
    {  (yyval.t) = P_NEED_LEX; ;}
    break;

  case 104:
#line 949 "imcc.y"
    {
            add_pcc_sub(IMCC_INFO(interp)->cur_call, (yyvsp[(2) - (5)].sr));
            add_pcc_cc(IMCC_INFO(interp)->cur_call, (yyvsp[(4) - (5)].sr));
         ;}
    break;

  case 105:
#line 954 "imcc.y"
    {  add_pcc_sub(IMCC_INFO(interp)->cur_call, (yyvsp[(2) - (3)].sr)); ;}
    break;

  case 106:
#line 956 "imcc.y"
    {
            add_pcc_sub(IMCC_INFO(interp)->cur_call, (yyvsp[(2) - (3)].sr));
            IMCC_INFO(interp)->cur_call->pcc_sub->flags |= isNCI;
         ;}
    break;

  case 107:
#line 961 "imcc.y"
    {  add_pcc_sub(IMCC_INFO(interp)->cur_call, (yyvsp[(2) - (3)].sr)); ;}
    break;

  case 108:
#line 963 "imcc.y"
    {  add_pcc_sub(IMCC_INFO(interp)->cur_call, mk_const(interp, (yyvsp[(2) - (3)].s),'S')); ;}
    break;

  case 109:
#line 965 "imcc.y"
    {  add_pcc_sub(IMCC_INFO(interp)->cur_call, (yyvsp[(2) - (5)].sr));
            add_pcc_cc(IMCC_INFO(interp)->cur_call, (yyvsp[(4) - (5)].sr));
         ;}
    break;

  case 110:
#line 969 "imcc.y"
    {  add_pcc_sub(IMCC_INFO(interp)->cur_call, mk_const(interp, (yyvsp[(2) - (5)].s),'S'));
            add_pcc_cc(IMCC_INFO(interp)->cur_call, (yyvsp[(4) - (5)].sr));
         ;}
    break;

  case 111:
#line 976 "imcc.y"
    {  (yyval.sr) = 0; ;}
    break;

  case 112:
#line 977 "imcc.y"
    {  add_pcc_arg(IMCC_INFO(interp)->cur_call, (yyvsp[(2) - (3)].sr)); ;}
    break;

  case 113:
#line 981 "imcc.y"
    {  (yyval.sr) = (yyvsp[(2) - (2)].sr); ;}
    break;

  case 114:
#line 986 "imcc.y"
    {  (yyval.sr) = 0; ;}
    break;

  case 115:
#line 987 "imcc.y"
    {  if ((yyvsp[(2) - (3)].sr)) add_pcc_result(IMCC_INFO(interp)->cur_call, (yyvsp[(2) - (3)].sr)); ;}
    break;

  case 116:
#line 991 "imcc.y"
    {  (yyval.sr) = (yyvsp[(2) - (3)].sr); (yyval.sr)->type |= (yyvsp[(3) - (3)].t); ;}
    break;

  case 117:
#line 992 "imcc.y"
    { is_def=1; ;}
    break;

  case 118:
#line 993 "imcc.y"
    {
         IdList* l = (yyvsp[(4) - (4)].idlist);
         if (l->unique_reg)
                 mk_ident_ur(interp, l->id, (yyvsp[(3) - (4)].t));
             else
                 mk_ident(interp, l->id, (yyvsp[(3) - (4)].t));
         is_def=0;
         (yyval.sr)=0;
     ;}
    break;

  case 119:
#line 1005 "imcc.y"
    {  (yyval.t) = 0; ;}
    break;

  case 120:
#line 1006 "imcc.y"
    {  (yyval.t) = (yyvsp[(1) - (2)].t) | (yyvsp[(2) - (2)].t); ;}
    break;

  case 121:
#line 1010 "imcc.y"
    {  (yyval.t) = VT_FLAT;   ;}
    break;

  case 122:
#line 1011 "imcc.y"
    {  (yyval.t) = VT_OPTIONAL; ;}
    break;

  case 123:
#line 1012 "imcc.y"
    {  (yyval.t) = VT_OPT_FLAG; ;}
    break;

  case 124:
#line 1013 "imcc.y"
    {  (yyval.t) = VT_NAMED; ;}
    break;

  case 125:
#line 1014 "imcc.y"
    {  adv_named_set(interp,(yyvsp[(3) - (4)].s)); (yyval.t) = 0; ;}
    break;

  case 126:
#line 1015 "imcc.y"
    {  (yyval.t) = VT_UNIQUE_REG; ;}
    break;

  case 127:
#line 1020 "imcc.y"
    { (yyval.t) = 0; ;}
    break;

  case 128:
#line 1021 "imcc.y"
    { (yyval.t) = 1; ;}
    break;

  case 131:
#line 1031 "imcc.y"
    { begin_return_or_yield(interp, (yyvsp[(1) - (2)].t)); ;}
    break;

  case 132:
#line 1034 "imcc.y"
    { (yyval.i) = 0;   IMCC_INFO(interp)->asm_state = AsmDefault; ;}
    break;

  case 133:
#line 1035 "imcc.y"
    {  IMCC_INFO(interp)->asm_state = AsmDefault; (yyval.i) = 0;  ;}
    break;

  case 134:
#line 1041 "imcc.y"
    {  (yyval.sr) = 0; ;}
    break;

  case 135:
#line 1042 "imcc.y"
    {
       if ((yyvsp[(1) - (2)].sr)) add_pcc_return(IMCC_INFO(interp)->sr_return, (yyvsp[(1) - (2)].sr));
   ;}
    break;

  case 136:
#line 1045 "imcc.y"
    {
       if ((yyvsp[(2) - (3)].sr)) add_pcc_return(IMCC_INFO(interp)->sr_return, (yyvsp[(2) - (3)].sr));
   ;}
    break;

  case 137:
#line 1051 "imcc.y"
    {  (yyval.sr) = (yyvsp[(2) - (3)].sr); (yyval.sr)->type |= (yyvsp[(3) - (3)].t); ;}
    break;

  case 138:
#line 1056 "imcc.y"
    {
            if ( IMCC_INFO(interp)->asm_state == AsmDefault)
                begin_return_or_yield(interp, 0);
        ;}
    break;

  case 139:
#line 1061 "imcc.y"
    {  IMCC_INFO(interp)->asm_state = AsmDefault; (yyval.t) = 0;  ;}
    break;

  case 140:
#line 1063 "imcc.y"
    {
            if ( IMCC_INFO(interp)->asm_state == AsmDefault)
                begin_return_or_yield(interp, 1);
        ;}
    break;

  case 141:
#line 1068 "imcc.y"
    {  IMCC_INFO(interp)->asm_state = AsmDefault; (yyval.t) = 0;  ;}
    break;

  case 142:
#line 1072 "imcc.y"
    { (yyval.i) = 0; ;}
    break;

  case 143:
#line 1073 "imcc.y"
    {
      if (IMCC_INFO(interp)->adv_named_id) {
          add_pcc_named_return(interp,IMCC_INFO(interp)->sr_return,
                               IMCC_INFO(interp)->adv_named_id, (yyvsp[(1) - (1)].sr));
          IMCC_INFO(interp)->adv_named_id = NULL;
      }
      else add_pcc_return(IMCC_INFO(interp)->sr_return, (yyvsp[(1) - (1)].sr)); ;}
    break;

  case 144:
#line 1080 "imcc.y"
    {
      add_pcc_named_return(interp,IMCC_INFO(interp)->sr_return,(yyvsp[(1) - (3)].s),(yyvsp[(3) - (3)].sr));;}
    break;

  case 145:
#line 1082 "imcc.y"
    {
      if (IMCC_INFO(interp)->adv_named_id) {
          add_pcc_named_return(interp,IMCC_INFO(interp)->sr_return,
                               IMCC_INFO(interp)->adv_named_id,(yyvsp[(3) - (3)].sr));
           IMCC_INFO(interp)->adv_named_id = NULL;
      }
      else add_pcc_return(IMCC_INFO(interp)->sr_return, (yyvsp[(3) - (3)].sr));    ;}
    break;

  case 146:
#line 1089 "imcc.y"
    {
      add_pcc_named_return(interp,IMCC_INFO(interp)->sr_return,(yyvsp[(3) - (5)].s),(yyvsp[(5) - (5)].sr));;}
    break;

  case 149:
#line 1108 "imcc.y"
    { clear_state(interp); ;}
    break;

  case 150:
#line 1113 "imcc.y"
    {  (yyval.i) = (yyvsp[(2) - (2)].i); ;}
    break;

  case 151:
#line 1114 "imcc.y"
    {  (yyval.i) = 0; ;}
    break;

  case 152:
#line 1115 "imcc.y"
    {  (yyval.i) = 0; ;}
    break;

  case 153:
#line 1116 "imcc.y"
    {  (yyval.i) = 0; ;}
    break;

  case 154:
#line 1120 "imcc.y"
    {  (yyval.i) = NULL; ;}
    break;

  case 158:
#line 1130 "imcc.y"
    {
         (yyval.i) = iLABEL(interp, IMCC_INFO(interp)->cur_unit, mk_local_label(interp, (yyvsp[(1) - (1)].s)));
                   ;}
    break;

  case 159:
#line 1139 "imcc.y"
    { (yyval.i) = (yyvsp[(2) - (3)].i); ;}
    break;

  case 160:
#line 1141 "imcc.y"
    { if (yynerrs >= PARROT_MAX_RECOVER_ERRORS) {
                           IMCC_warning(interp, "Too many errors. Correct some first.\n");
                           YYABORT;
                       }
                       yyerrok; ;}
    break;

  case 161:
#line 1150 "imcc.y"
    {
         IdList* l = (yyvsp[(1) - (1)].idlist);
         l->next = NULL;
         (yyval.idlist) = l;
     ;}
    break;

  case 162:
#line 1157 "imcc.y"
    {
         IdList* l = (yyvsp[(3) - (3)].idlist);
         l->next = (yyvsp[(1) - (3)].idlist);
         (yyval.idlist) = l;
     ;}
    break;

  case 163:
#line 1166 "imcc.y"
    {
         IdList* l = (IdList*)malloc(sizeof(IdList));
         l->id = (yyvsp[(1) - (2)].s);
         l->unique_reg = 1;
         (yyval.idlist) = l;
     ;}
    break;

  case 164:
#line 1174 "imcc.y"
    {
         IdList* l = (IdList*)malloc(sizeof(IdList));
         l->id = (yyvsp[(1) - (1)].s);
         l->unique_reg = 0;
         (yyval.idlist) = l;
     ;}
    break;

  case 167:
#line 1185 "imcc.y"
    { push_namespace((yyvsp[(2) - (2)].s)); ;}
    break;

  case 168:
#line 1186 "imcc.y"
    { pop_namespace((yyvsp[(2) - (2)].s)); ;}
    break;

  case 169:
#line 1187 "imcc.y"
    { is_def=1; ;}
    break;

  case 170:
#line 1188 "imcc.y"
    {
         IdList* l = (yyvsp[(4) - (4)].idlist);
         while (l) {
             IdList* l1;
             if (l->unique_reg)
                 mk_ident_ur(interp, l->id, (yyvsp[(3) - (4)].t));
             else
                 mk_ident(interp, l->id, (yyvsp[(3) - (4)].t));
             l1 = l;
             l = l->next;
             free(l1);
         }
         is_def=0; (yyval.i)=0;
     ;}
    break;

  case 171:
#line 1203 "imcc.y"
    {
                       set_lexical(interp, (yyvsp[(4) - (4)].sr), (yyvsp[(2) - (4)].s)); (yyval.i) = 0;
                    ;}
    break;

  case 172:
#line 1206 "imcc.y"
    { is_def=1; ;}
    break;

  case 173:
#line 1207 "imcc.y"
    { mk_const_ident(interp, (yyvsp[(4) - (6)].s), (yyvsp[(3) - (6)].t), (yyvsp[(6) - (6)].sr), 0);is_def=0; ;}
    break;

  case 175:
#line 1209 "imcc.y"
    { is_def=1; ;}
    break;

  case 176:
#line 1210 "imcc.y"
    { mk_const_ident(interp, (yyvsp[(4) - (6)].s), (yyvsp[(3) - (6)].t), (yyvsp[(6) - (6)].sr), 1);is_def=0; ;}
    break;

  case 177:
#line 1211 "imcc.y"
    { (yyval.i) = NULL;
                           IMCC_INFO(interp)->cur_call->pcc_sub->flags |= isTAIL_CALL;
                           IMCC_INFO(interp)->cur_call = NULL;
                        ;}
    break;

  case 178:
#line 1215 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "branch",1, (yyvsp[(2) - (2)].sr)); ;}
    break;

  case 179:
#line 1217 "imcc.y"
    { (yyval.i) = INS(interp, IMCC_INFO(interp)->cur_unit, (yyvsp[(1) - (2)].s), 0,
                              IMCC_INFO(interp) -> regs,
                              IMCC_INFO(interp) -> nargs,
                              IMCC_INFO(interp) -> keyvec, 1);
                       free((yyvsp[(1) - (2)].s)); ;}
    break;

  case 180:
#line 1223 "imcc.y"
    {  (yyval.i) =MK_I(interp, IMCC_INFO(interp)->cur_unit, "null", 1, (yyvsp[(2) - (2)].sr)); ;}
    break;

  case 181:
#line 1224 "imcc.y"
    {  (yyval.i) = 0; IMCC_INFO(interp)->cur_call = NULL; ;}
    break;

  case 182:
#line 1225 "imcc.y"
    {  (yyval.i) = 0; ;}
    break;

  case 184:
#line 1227 "imcc.y"
    { (yyval.i) = 0;;}
    break;

  case 185:
#line 1231 "imcc.y"
    { (yyval.t) = 'I'; ;}
    break;

  case 186:
#line 1232 "imcc.y"
    { (yyval.t) = 'N'; ;}
    break;

  case 187:
#line 1233 "imcc.y"
    { (yyval.t) = 'S'; ;}
    break;

  case 188:
#line 1234 "imcc.y"
    { (yyval.t) = 'P'; ;}
    break;

  case 189:
#line 1235 "imcc.y"
    { (yyval.t) = 'P'; free((yyvsp[(1) - (1)].s)); ;}
    break;

  case 190:
#line 1240 "imcc.y"
    {
             if (( IMCC_INFO(interp)->cur_pmc_type = pmc_type(interp,
                  string_from_cstring(interp, (yyvsp[(1) - (1)].s), 0))) <= 0) {
                IMCC_fataly(interp, E_SyntaxError,
                   "Unknown PMC type '%s'\n", (yyvsp[(1) - (1)].s));
            }
         ;}
    break;

  case 191:
#line 1251 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "set", 2, (yyvsp[(1) - (3)].sr), (yyvsp[(3) - (3)].sr));      ;}
    break;

  case 192:
#line 1253 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "not", 2, (yyvsp[(1) - (4)].sr), (yyvsp[(4) - (4)].sr));      ;}
    break;

  case 193:
#line 1255 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "neg", 2, (yyvsp[(1) - (4)].sr), (yyvsp[(4) - (4)].sr));      ;}
    break;

  case 194:
#line 1257 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "bnot", 2, (yyvsp[(1) - (4)].sr), (yyvsp[(4) - (4)].sr));     ;}
    break;

  case 195:
#line 1259 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "add", 3, (yyvsp[(1) - (5)].sr), (yyvsp[(3) - (5)].sr), (yyvsp[(5) - (5)].sr));  ;}
    break;

  case 196:
#line 1261 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "sub", 3, (yyvsp[(1) - (5)].sr), (yyvsp[(3) - (5)].sr), (yyvsp[(5) - (5)].sr));  ;}
    break;

  case 197:
#line 1263 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "mul", 3, (yyvsp[(1) - (5)].sr), (yyvsp[(3) - (5)].sr), (yyvsp[(5) - (5)].sr));  ;}
    break;

  case 198:
#line 1265 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "pow", 3, (yyvsp[(1) - (5)].sr), (yyvsp[(3) - (5)].sr), (yyvsp[(5) - (5)].sr));  ;}
    break;

  case 199:
#line 1267 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "div", 3, (yyvsp[(1) - (5)].sr), (yyvsp[(3) - (5)].sr), (yyvsp[(5) - (5)].sr));  ;}
    break;

  case 200:
#line 1269 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "fdiv", 3, (yyvsp[(1) - (5)].sr), (yyvsp[(3) - (5)].sr), (yyvsp[(5) - (5)].sr)); ;}
    break;

  case 201:
#line 1271 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "mod", 3, (yyvsp[(1) - (5)].sr), (yyvsp[(3) - (5)].sr), (yyvsp[(5) - (5)].sr));  ;}
    break;

  case 202:
#line 1273 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "concat", 3, (yyvsp[(1) - (5)].sr),(yyvsp[(3) - (5)].sr),(yyvsp[(5) - (5)].sr)); ;}
    break;

  case 203:
#line 1275 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "iseq", 3, (yyvsp[(1) - (5)].sr), (yyvsp[(3) - (5)].sr), (yyvsp[(5) - (5)].sr)); ;}
    break;

  case 204:
#line 1277 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "isne", 3, (yyvsp[(1) - (5)].sr), (yyvsp[(3) - (5)].sr), (yyvsp[(5) - (5)].sr)); ;}
    break;

  case 205:
#line 1279 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "isgt", 3, (yyvsp[(1) - (5)].sr), (yyvsp[(3) - (5)].sr), (yyvsp[(5) - (5)].sr)); ;}
    break;

  case 206:
#line 1281 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "islt", 3, (yyvsp[(1) - (5)].sr), (yyvsp[(3) - (5)].sr), (yyvsp[(5) - (5)].sr)); ;}
    break;

  case 207:
#line 1283 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "isle", 3, (yyvsp[(1) - (5)].sr), (yyvsp[(3) - (5)].sr), (yyvsp[(5) - (5)].sr)); ;}
    break;

  case 208:
#line 1285 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "isge", 3, (yyvsp[(1) - (5)].sr), (yyvsp[(3) - (5)].sr), (yyvsp[(5) - (5)].sr)); ;}
    break;

  case 209:
#line 1287 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "shl", 3, (yyvsp[(1) - (5)].sr), (yyvsp[(3) - (5)].sr), (yyvsp[(5) - (5)].sr));  ;}
    break;

  case 210:
#line 1289 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "shr", 3, (yyvsp[(1) - (5)].sr), (yyvsp[(3) - (5)].sr), (yyvsp[(5) - (5)].sr));  ;}
    break;

  case 211:
#line 1291 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "lsr", 3, (yyvsp[(1) - (5)].sr), (yyvsp[(3) - (5)].sr), (yyvsp[(5) - (5)].sr));  ;}
    break;

  case 212:
#line 1293 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "and", 3, (yyvsp[(1) - (5)].sr), (yyvsp[(3) - (5)].sr), (yyvsp[(5) - (5)].sr));  ;}
    break;

  case 213:
#line 1295 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "or", 3, (yyvsp[(1) - (5)].sr), (yyvsp[(3) - (5)].sr), (yyvsp[(5) - (5)].sr));   ;}
    break;

  case 214:
#line 1297 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "xor", 3, (yyvsp[(1) - (5)].sr), (yyvsp[(3) - (5)].sr), (yyvsp[(5) - (5)].sr));  ;}
    break;

  case 215:
#line 1299 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "band", 3, (yyvsp[(1) - (5)].sr), (yyvsp[(3) - (5)].sr), (yyvsp[(5) - (5)].sr)); ;}
    break;

  case 216:
#line 1301 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "bor", 3, (yyvsp[(1) - (5)].sr), (yyvsp[(3) - (5)].sr), (yyvsp[(5) - (5)].sr));  ;}
    break;

  case 217:
#line 1303 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "bxor", 3, (yyvsp[(1) - (5)].sr), (yyvsp[(3) - (5)].sr), (yyvsp[(5) - (5)].sr)); ;}
    break;

  case 218:
#line 1305 "imcc.y"
    { (yyval.i) = iINDEXFETCH(interp, IMCC_INFO(interp)->cur_unit, (yyvsp[(1) - (6)].sr), (yyvsp[(3) - (6)].sr), (yyvsp[(5) - (6)].sr)); ;}
    break;

  case 219:
#line 1307 "imcc.y"
    { (yyval.i) = iINDEXSET(interp, IMCC_INFO(interp)->cur_unit, (yyvsp[(1) - (6)].sr), (yyvsp[(3) - (6)].sr), (yyvsp[(6) - (6)].sr)); ;}
    break;

  case 220:
#line 1309 "imcc.y"
    { (yyval.i) = iNEW(interp, IMCC_INFO(interp)->cur_unit, (yyvsp[(1) - (6)].sr), (yyvsp[(4) - (6)].s), (yyvsp[(6) - (6)].sr), 1); ;}
    break;

  case 221:
#line 1311 "imcc.y"
    { (yyval.i) = iNEW(interp, IMCC_INFO(interp)->cur_unit, (yyvsp[(1) - (7)].sr), (yyvsp[(4) - (7)].s), (yyvsp[(6) - (7)].sr), 1); ;}
    break;

  case 222:
#line 1313 "imcc.y"
    { (yyval.i) = iNEW(interp, IMCC_INFO(interp)->cur_unit, (yyvsp[(1) - (4)].sr), (yyvsp[(4) - (4)].s), NULL, 1); ;}
    break;

  case 223:
#line 1315 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "new", 2, (yyvsp[(1) - (4)].sr), (yyvsp[(4) - (4)].sr)); ;}
    break;

  case 224:
#line 1317 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "new", 2, (yyvsp[(1) - (6)].sr), (yyvsp[(5) - (6)].sr)); ;}
    break;

  case 225:
#line 1319 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "new", 3, (yyvsp[(1) - (6)].sr), (yyvsp[(4) - (6)].sr), (yyvsp[(6) - (6)].sr)); ;}
    break;

  case 226:
#line 1321 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "new", 3, (yyvsp[(1) - (7)].sr), (yyvsp[(4) - (7)].sr), (yyvsp[(6) - (7)].sr)); ;}
    break;

  case 227:
#line 1323 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "set_addr",
                        2, (yyvsp[(1) - (4)].sr), mk_label_address(interp, (yyvsp[(4) - (4)].s))); ;}
    break;

  case 228:
#line 1326 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "find_global",2,(yyvsp[(1) - (4)].sr),(yyvsp[(4) - (4)].sr));;}
    break;

  case 229:
#line 1328 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "store_global",2, (yyvsp[(2) - (4)].sr),(yyvsp[(4) - (4)].sr)); ;}
    break;

  case 230:
#line 1332 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "new", 2, (yyvsp[(2) - (4)].sr), (yyvsp[(4) - (4)].sr)); ;}
    break;

  case 231:
#line 1334 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "new", 3, (yyvsp[(2) - (6)].sr), (yyvsp[(4) - (6)].sr), (yyvsp[(6) - (6)].sr)); ;}
    break;

  case 232:
#line 1336 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "new", 3, (yyvsp[(2) - (7)].sr), (yyvsp[(4) - (7)].sr), (yyvsp[(6) - (7)].sr)); ;}
    break;

  case 233:
#line 1339 "imcc.y"
    {
            add_pcc_result((yyvsp[(3) - (3)].i)->r[0], (yyvsp[(1) - (3)].sr));
            IMCC_INFO(interp)->cur_call = NULL;
            (yyval.i) = 0;
         ;}
    break;

  case 234:
#line 1345 "imcc.y"
    {
            (yyval.i) = IMCC_create_itcall_label(interp);
         ;}
    break;

  case 235:
#line 1349 "imcc.y"
    {
           IMCC_itcall_sub(interp, (yyvsp[(6) - (9)].sr));
           IMCC_INFO(interp)->cur_call = NULL;
         ;}
    break;

  case 239:
#line 1357 "imcc.y"
    {  (yyval.i) =MK_I(interp, IMCC_INFO(interp)->cur_unit, "null", 1, (yyvsp[(1) - (3)].sr)); ;}
    break;

  case 240:
#line 1360 "imcc.y"
    { (yyval.i) = IMCC_create_itcall_label(interp);
                           (yyval.i)->type &= ~ITCALL; (yyval.i)->type |= ITRESULT; ;}
    break;

  case 241:
#line 1362 "imcc.y"
    {  (yyval.i) = 0; ;}
    break;

  case 242:
#line 1367 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "add", 2, (yyvsp[(1) - (3)].sr), (yyvsp[(3) - (3)].sr)); ;}
    break;

  case 243:
#line 1369 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "sub", 2, (yyvsp[(1) - (3)].sr), (yyvsp[(3) - (3)].sr)); ;}
    break;

  case 244:
#line 1371 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "mul", 2, (yyvsp[(1) - (3)].sr), (yyvsp[(3) - (3)].sr)); ;}
    break;

  case 245:
#line 1373 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "div", 2, (yyvsp[(1) - (3)].sr), (yyvsp[(3) - (3)].sr)); ;}
    break;

  case 246:
#line 1375 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "mod", 2, (yyvsp[(1) - (3)].sr), (yyvsp[(3) - (3)].sr)); ;}
    break;

  case 247:
#line 1377 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "fdiv", 2, (yyvsp[(1) - (3)].sr), (yyvsp[(3) - (3)].sr)); ;}
    break;

  case 248:
#line 1379 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "concat", 2, (yyvsp[(1) - (3)].sr), (yyvsp[(3) - (3)].sr)); ;}
    break;

  case 249:
#line 1381 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "band", 2, (yyvsp[(1) - (3)].sr), (yyvsp[(3) - (3)].sr)); ;}
    break;

  case 250:
#line 1383 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "bor", 2, (yyvsp[(1) - (3)].sr), (yyvsp[(3) - (3)].sr)); ;}
    break;

  case 251:
#line 1385 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "bxor", 2, (yyvsp[(1) - (3)].sr), (yyvsp[(3) - (3)].sr)); ;}
    break;

  case 252:
#line 1387 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "shr", 2, (yyvsp[(1) - (3)].sr), (yyvsp[(3) - (3)].sr)); ;}
    break;

  case 253:
#line 1389 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "shl", 2, (yyvsp[(1) - (3)].sr), (yyvsp[(3) - (3)].sr)); ;}
    break;

  case 254:
#line 1391 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "lsr", 2, (yyvsp[(1) - (3)].sr), (yyvsp[(3) - (3)].sr)); ;}
    break;

  case 255:
#line 1396 "imcc.y"
    { (yyval.i) = func_ins(interp, IMCC_INFO(interp)->cur_unit, (yyvsp[(1) - (4)].sr), (yyvsp[(3) - (4)].s),
                                   IMCC_INFO(interp) -> regs,
                                   IMCC_INFO(interp) -> nargs,
                                   IMCC_INFO(interp) -> keyvec, 1);
                     free((yyvsp[(3) - (4)].s));
                   ;}
    break;

  case 256:
#line 1404 "imcc.y"
    { (yyval.sr) = mk_sub_address(interp, (yyvsp[(1) - (1)].s)); ;}
    break;

  case 257:
#line 1405 "imcc.y"
    { (yyval.sr) = mk_sub_address_fromc(interp, (yyvsp[(1) - (1)].s)); ;}
    break;

  case 258:
#line 1406 "imcc.y"
    { (yyval.sr) = mk_sub_address_u(interp, (yyvsp[(1) - (1)].s)); ;}
    break;

  case 259:
#line 1407 "imcc.y"
    { (yyval.sr) = (yyvsp[(1) - (1)].sr);
                       if ((yyvsp[(1) - (1)].sr)->set != 'P')
                            IMCC_fataly(interp, E_SyntaxError,
                                  "Sub isn't a PMC");
                     ;}
    break;

  case 260:
#line 1412 "imcc.y"
    { IMCC_INFO(interp)->cur_obj = (yyvsp[(1) - (3)].sr); (yyval.sr) = (yyvsp[(3) - (3)].sr); ;}
    break;

  case 261:
#line 1413 "imcc.y"
    { IMCC_INFO(interp)->cur_obj = (yyvsp[(1) - (3)].sr); (yyval.sr) = mk_const(interp, (yyvsp[(3) - (3)].s), 'S'); ;}
    break;

  case 262:
#line 1414 "imcc.y"
    { IMCC_INFO(interp)->cur_obj = (yyvsp[(1) - (3)].sr); (yyval.sr) = (yyvsp[(3) - (3)].sr); ;}
    break;

  case 263:
#line 1417 "imcc.y"
    { (yyval.t)=0; ;}
    break;

  case 264:
#line 1418 "imcc.y"
    { (yyval.t)=0; ;}
    break;

  case 265:
#line 1423 "imcc.y"
    {
           (yyval.i) = IMCC_create_itcall_label(interp);
           IMCC_itcall_sub(interp, (yyvsp[(1) - (1)].sr));
        ;}
    break;

  case 266:
#line 1428 "imcc.y"
    {  (yyval.i) = (yyvsp[(2) - (5)].i); ;}
    break;

  case 267:
#line 1432 "imcc.y"
    {  (yyval.sr) = 0; ;}
    break;

  case 268:
#line 1433 "imcc.y"
    {  (yyval.sr) = 0;
       if (IMCC_INFO(interp)->adv_named_id) {
           add_pcc_named_arg(interp, IMCC_INFO(interp)->cur_call, IMCC_INFO(interp)->adv_named_id, (yyvsp[(3) - (3)].sr));
           IMCC_INFO(interp)->adv_named_id = NULL;
       }
       else add_pcc_arg(IMCC_INFO(interp)->cur_call, (yyvsp[(3) - (3)].sr));
   ;}
    break;

  case 269:
#line 1440 "imcc.y"
    {  (yyval.sr) = 0;
       if (IMCC_INFO(interp)->adv_named_id) {
           add_pcc_named_arg(interp, IMCC_INFO(interp)->cur_call,IMCC_INFO(interp)->adv_named_id,(yyvsp[(1) - (1)].sr));
           IMCC_INFO(interp)->adv_named_id = NULL;
       }
       else add_pcc_arg(IMCC_INFO(interp)->cur_call, (yyvsp[(1) - (1)].sr));
   ;}
    break;

  case 270:
#line 1447 "imcc.y"
    { (yyval.sr) = 0;
                                     add_pcc_named_arg(interp,IMCC_INFO(interp)->cur_call,(yyvsp[(3) - (5)].s),(yyvsp[(5) - (5)].sr));;}
    break;

  case 271:
#line 1449 "imcc.y"
    { (yyval.sr) = 0; add_pcc_named_arg(interp,IMCC_INFO(interp)->cur_call,(yyvsp[(1) - (3)].s),(yyvsp[(3) - (3)].sr));;}
    break;

  case 272:
#line 1453 "imcc.y"
    {  (yyval.sr) = (yyvsp[(1) - (2)].sr); (yyval.sr)->type |= (yyvsp[(2) - (2)].t); ;}
    break;

  case 273:
#line 1457 "imcc.y"
    {  (yyval.t) = 0; ;}
    break;

  case 274:
#line 1458 "imcc.y"
    {  (yyval.t) = (yyvsp[(1) - (2)].t) | (yyvsp[(2) - (2)].t); ;}
    break;

  case 275:
#line 1462 "imcc.y"
    { (yyval.t) = VT_FLAT; ;}
    break;

  case 276:
#line 1463 "imcc.y"
    { (yyval.t) = VT_NAMED; ;}
    break;

  case 277:
#line 1464 "imcc.y"
    { adv_named_set(interp,(yyvsp[(3) - (4)].s)); (yyval.t) = 0; ;}
    break;

  case 278:
#line 1467 "imcc.y"
    { (yyval.sr) = (yyvsp[(1) - (2)].sr); (yyval.sr)->type |= (yyvsp[(2) - (2)].t); ;}
    break;

  case 279:
#line 1471 "imcc.y"
    {
         (yyval.sr) = 0;
         if (IMCC_INFO(interp)->adv_named_id) {
             add_pcc_named_result(interp,IMCC_INFO(interp)->cur_call,IMCC_INFO(interp)->adv_named_id,(yyvsp[(3) - (3)].sr));
             IMCC_INFO(interp)->adv_named_id = NULL;
         }
         else add_pcc_result(IMCC_INFO(interp)->cur_call, (yyvsp[(3) - (3)].sr)); ;}
    break;

  case 280:
#line 1478 "imcc.y"
    {
        add_pcc_named_result(interp,IMCC_INFO(interp)->cur_call,(yyvsp[(3) - (5)].s),(yyvsp[(5) - (5)].sr)); ;}
    break;

  case 281:
#line 1480 "imcc.y"
    {
       (yyval.sr) = 0;
       if (IMCC_INFO(interp)->adv_named_id) {
           add_pcc_named_result(interp,IMCC_INFO(interp)->cur_call,IMCC_INFO(interp)->adv_named_id,(yyvsp[(1) - (1)].sr));
           IMCC_INFO(interp)->adv_named_id = NULL;
       }
       else add_pcc_result(IMCC_INFO(interp)->cur_call, (yyvsp[(1) - (1)].sr)); ;}
    break;

  case 282:
#line 1487 "imcc.y"
    { add_pcc_named_result(interp,IMCC_INFO(interp)->cur_call,(yyvsp[(1) - (3)].s),(yyvsp[(3) - (3)].sr)); ;}
    break;

  case 283:
#line 1488 "imcc.y"
    {  (yyval.sr) = 0; ;}
    break;

  case 284:
#line 1493 "imcc.y"
    { (yyval.i) =MK_I(interp, IMCC_INFO(interp)->cur_unit, (yyvsp[(3) - (6)].s), 3, (yyvsp[(2) - (6)].sr), (yyvsp[(4) - (6)].sr), (yyvsp[(6) - (6)].sr)); ;}
    break;

  case 285:
#line 1495 "imcc.y"
    { (yyval.i) =MK_I(interp, IMCC_INFO(interp)->cur_unit, inv_op((yyvsp[(3) - (6)].s)), 3, (yyvsp[(2) - (6)].sr),(yyvsp[(4) - (6)].sr), (yyvsp[(6) - (6)].sr)); ;}
    break;

  case 286:
#line 1497 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "if_null", 2, (yyvsp[(3) - (5)].sr), (yyvsp[(5) - (5)].sr)); ;}
    break;

  case 287:
#line 1499 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "unless_null", 2, (yyvsp[(3) - (5)].sr), (yyvsp[(5) - (5)].sr)); ;}
    break;

  case 288:
#line 1501 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "if", 2, (yyvsp[(2) - (4)].sr), (yyvsp[(4) - (4)].sr)); ;}
    break;

  case 289:
#line 1503 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "unless",2, (yyvsp[(2) - (4)].sr), (yyvsp[(4) - (4)].sr)); ;}
    break;

  case 290:
#line 1505 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "if", 2, (yyvsp[(2) - (4)].sr), (yyvsp[(4) - (4)].sr)); ;}
    break;

  case 291:
#line 1507 "imcc.y"
    { (yyval.i) = MK_I(interp, IMCC_INFO(interp)->cur_unit, "unless", 2, (yyvsp[(2) - (4)].sr), (yyvsp[(4) - (4)].sr)); ;}
    break;

  case 292:
#line 1511 "imcc.y"
    {  (yyval.s) = "eq"; ;}
    break;

  case 293:
#line 1512 "imcc.y"
    {  (yyval.s) = "ne"; ;}
    break;

  case 294:
#line 1513 "imcc.y"
    {  (yyval.s) = "gt"; ;}
    break;

  case 295:
#line 1514 "imcc.y"
    {  (yyval.s) = "ge"; ;}
    break;

  case 296:
#line 1515 "imcc.y"
    {  (yyval.s) = "lt"; ;}
    break;

  case 297:
#line 1516 "imcc.y"
    {  (yyval.s) = "le"; ;}
    break;

  case 300:
#line 1525 "imcc.y"
    {  (yyval.sr) = NULL; ;}
    break;

  case 301:
#line 1526 "imcc.y"
    {  (yyval.sr) = (yyvsp[(1) - (1)].sr); ;}
    break;

  case 302:
#line 1530 "imcc.y"
    { (yyval.sr) = IMCC_INFO(interp)->regs[0]; ;}
    break;

  case 304:
#line 1535 "imcc.y"
    {  IMCC_INFO(interp)->regs[IMCC_INFO(interp)->nargs++] = (yyvsp[(1) - (1)].sr); ;}
    break;

  case 305:
#line 1537 "imcc.y"
    {
                      IMCC_INFO(interp) -> regs[IMCC_INFO(interp)->nargs++] = (yyvsp[(1) - (4)].sr);
                      IMCC_INFO(interp) -> keyvec |= KEY_BIT(IMCC_INFO(interp)->nargs);
                      IMCC_INFO(interp) -> regs[IMCC_INFO(interp)->nargs++] = (yyvsp[(3) - (4)].sr);
                      (yyval.sr) = (yyvsp[(1) - (4)].sr);
                   ;}
    break;

  case 306:
#line 1544 "imcc.y"
    {
                      IMCC_INFO(interp) -> regs[IMCC_INFO(interp)->nargs++] = (yyvsp[(2) - (3)].sr);
                      (yyval.sr) = (yyvsp[(2) - (3)].sr);
                   ;}
    break;

  case 308:
#line 1551 "imcc.y"
    { (yyval.sr) = mk_sub_address_fromc(interp, (yyvsp[(1) - (1)].s)); ;}
    break;

  case 309:
#line 1552 "imcc.y"
    { (yyval.sr) = mk_sub_address_u(interp, (yyvsp[(1) - (1)].s)); ;}
    break;

  case 310:
#line 1556 "imcc.y"
    { (yyval.sr) = mk_sub_address(interp, (yyvsp[(1) - (1)].s)); ;}
    break;

  case 311:
#line 1557 "imcc.y"
    { (yyval.sr) = mk_sub_address(interp, (yyvsp[(1) - (1)].s)); ;}
    break;

  case 312:
#line 1561 "imcc.y"
    { (yyval.sr) = mk_label_address(interp, (yyvsp[(1) - (1)].s)); ;}
    break;

  case 313:
#line 1562 "imcc.y"
    { (yyval.sr) = mk_label_address(interp, (yyvsp[(1) - (1)].s)); ;}
    break;

  case 318:
#line 1575 "imcc.y"
    {  IMCC_INFO(interp)->nkeys = 0;
                      IMCC_INFO(interp)->in_slice = 0; ;}
    break;

  case 319:
#line 1577 "imcc.y"
    {  (yyval.sr) = link_keys(interp,
                                     IMCC_INFO(interp)->nkeys,
                                     IMCC_INFO(interp)->keys, 0); ;}
    break;

  case 320:
#line 1582 "imcc.y"
    {  IMCC_INFO(interp)->nkeys = 0;
                      IMCC_INFO(interp)->in_slice = 0; ;}
    break;

  case 321:
#line 1584 "imcc.y"
    {  (yyval.sr) = link_keys(interp,
                                     IMCC_INFO(interp)->nkeys,
                                     IMCC_INFO(interp)->keys, 1); ;}
    break;

  case 322:
#line 1590 "imcc.y"
    {  IMCC_INFO(interp)->keys[IMCC_INFO(interp)->nkeys++] = (yyvsp[(1) - (1)].sr); ;}
    break;

  case 323:
#line 1592 "imcc.y"
    {  IMCC_INFO(interp)->keys[IMCC_INFO(interp)->nkeys++] = (yyvsp[(3) - (3)].sr);
                      (yyval.sr) = IMCC_INFO(interp)->keys[0]; ;}
    break;

  case 324:
#line 1594 "imcc.y"
    { IMCC_INFO(interp)->in_slice = 1; ;}
    break;

  case 325:
#line 1595 "imcc.y"
    { IMCC_INFO(interp)->keys[IMCC_INFO(interp)->nkeys++] = (yyvsp[(4) - (4)].sr);
                       (yyval.sr) = IMCC_INFO(interp)->keys[0]; ;}
    break;

  case 326:
#line 1600 "imcc.y"
    { if (IMCC_INFO(interp)->in_slice) {
                         (yyvsp[(1) - (1)].sr)->type |= VT_START_SLICE | VT_END_SLICE;
                     }
                     (yyval.sr) = (yyvsp[(1) - (1)].sr);
                   ;}
    break;

  case 327:
#line 1606 "imcc.y"
    { (yyvsp[(1) - (3)].sr)->type |= VT_START_SLICE;
                     (yyvsp[(3) - (3)].sr)->type |= VT_END_SLICE;
                     IMCC_INFO(interp)->keys[IMCC_INFO(interp)->nkeys++] = (yyvsp[(1) - (3)].sr);
                     (yyval.sr) = (yyvsp[(3) - (3)].sr); ;}
    break;

  case 328:
#line 1610 "imcc.y"
    { (yyvsp[(2) - (2)].sr)->type |= VT_START_ZERO | VT_END_SLICE; (yyval.sr) = (yyvsp[(2) - (2)].sr); ;}
    break;

  case 329:
#line 1611 "imcc.y"
    { (yyvsp[(1) - (2)].sr)->type |= VT_START_SLICE | VT_END_INF; (yyval.sr) = (yyvsp[(1) - (2)].sr); ;}
    break;

  case 330:
#line 1615 "imcc.y"
    {  (yyval.sr) = mk_symreg(interp, (yyvsp[(1) - (1)].s), 'I'); ;}
    break;

  case 331:
#line 1616 "imcc.y"
    {  (yyval.sr) = mk_symreg(interp, (yyvsp[(1) - (1)].s), 'N'); ;}
    break;

  case 332:
#line 1617 "imcc.y"
    {  (yyval.sr) = mk_symreg(interp, (yyvsp[(1) - (1)].s), 'S'); ;}
    break;

  case 333:
#line 1618 "imcc.y"
    {  (yyval.sr) = mk_symreg(interp, (yyvsp[(1) - (1)].s), 'P'); ;}
    break;

  case 334:
#line 1619 "imcc.y"
    {  (yyval.sr) = mk_pasm_reg(interp, (yyvsp[(1) - (1)].s));    ;}
    break;

  case 335:
#line 1623 "imcc.y"
    {  (yyval.sr) = mk_const(interp, (yyvsp[(1) - (1)].s), 'I'); ;}
    break;

  case 336:
#line 1624 "imcc.y"
    {  (yyval.sr) = mk_const(interp, (yyvsp[(1) - (1)].s), 'N'); ;}
    break;

  case 337:
#line 1625 "imcc.y"
    {  (yyval.sr) = mk_const(interp, (yyvsp[(1) - (1)].s), 'S'); ;}
    break;

  case 338:
#line 1626 "imcc.y"
    {  (yyval.sr) = mk_const(interp, (yyvsp[(1) - (1)].s), 'U'); ;}
    break;

  case 339:
#line 1630 "imcc.y"
    {  (yyval.sr) = mk_symreg(interp, (yyvsp[(1) - (1)].s), 'S'); ;}
    break;

  case 340:
#line 1631 "imcc.y"
    {  (yyval.sr) = mk_const(interp, (yyvsp[(1) - (1)].s), 'S');  ;}
    break;


/* Line 1267 of yacc.c.  */
#line 4516 "imcc.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (yyscanner, interp, YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yyscanner, interp, yymsg);
	  }
	else
	  {
	    yyerror (yyscanner, interp, YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, yyscanner, interp);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yyscanner, interp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (yyscanner, interp, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, yyscanner, interp);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yyscanner, interp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 1636 "imcc.y"


/* I need this prototype somewhere... */
char *yyget_text (yyscan_t yyscanner );

/* I do not like this function, but, atm, it is the only way I can
 * make the code in yyerror work without segfault on some specific
 * cases.
 */
/* int yyholds_char(yyscan_t yyscanner ); */

int yyerror(void *yyscanner, PARROT_INTERP, char * s)
{
    /* If the error occurr in the end of the buffer (I mean, the last
     * token was already read), yyget_text will return a pointer
     * outside the bison buffer, and thus, not "accessible" by
     * us. This means it may segfault. */
    char *chr = yyget_text((yyscan_t)yyscanner);

    /* IMCC_fataly(interp, E_SyntaxError, s); */
    /* --- This was called before, not sure if I should call some
           similar function that does not die like this one. */


    /* Basically, if current token is a newline, it mean the error was
     * before the newline, and thus, line is the line *after* the
     * error.
     */
    if (!at_eof(yyscanner) && *chr == '\n') {
        IMCC_INFO(interp)->line--;
        IMCC_warning(interp, "error:imcc:%s", s);
        IMCC_print_inc(interp);
        IMCC_INFO(interp)->line++;
    }
    else {
        IMCC_warning(interp, "error:imcc:%s", s);
        IMCC_print_inc(interp);
    }

    return 0;
}

/*
 * Local variables:
 *   c-file-style: "parrot"
 * End:
 * vim: expandtab shiftwidth=4:
 */

