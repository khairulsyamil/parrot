#ifndef __IMC_H
#define __IMC_H

#include <stdio.h>
#include <stdlib.h>

#ifdef PARROT_HAS_HEADER_SYSEXITS
#  include <sysexits.h>
#else
#  define EX_DATAERR 1
#  define EX_SOFTWARE 1
#  define EX_NOINPUT 1
#  define EX_IOERR 1
#  define EX_USAGE 1
#  define EX_UNAVAILABLE 1
#endif  /* PARROT_HAS_HEADER_SYSEXITS */

#include "parrot/parrot.h"

#define IMCC_MAX_REGS PARROT_MAX_ARGS
#if IMCC_MAX_REGS > 16
#error: flags wont fit
#endif

#ifdef MAIN
#define EXTERN
#else
#define EXTERN extern
#endif


#include "symreg.h"
#include "instructions.h"
#include "symbol.h"
#include "class.h"
#include "sets.h"
#include "cfg.h"
#include "stacks.h"
#include "unit.h"
#include "debug.h"


/* Ok, this won't scale to architectures like i386, but thats not
 * the goal right now.
 */
#define MAX_COLOR NUM_REGISTERS

void imc_compile_unit(struct Parrot_Interp *, Instruction * unit);
void free_reglist(struct Parrot_Interp *);

const char * get_neg_op(char *op, int *nargs);

int check_op(struct Parrot_Interp *, char * fullname, char *op, SymReg *r[],
    int narg, int keyvec);
int get_keyvec(Parrot_Interp, int opnum);
int is_op(struct Parrot_Interp *, char *);
void init_tables(struct Parrot_Interp * interp);

int imcc_vfprintf(FILE *fd, const char *format, va_list ap);
int imcc_fprintf(FILE *fd, const char *fmt, ...);

/* pcc protos */
void expand_pcc_sub(Parrot_Interp interpreter, Instruction *ins);
void expand_pcc_sub_call(Parrot_Interp interpreter, Instruction *ins);
void expand_pcc_sub_ret(Parrot_Interp interpreter, Instruction *ins);
void pcc_optimize(Parrot_Interp interpreter);

int pcc_sub_reads(Instruction* ins, SymReg* r);
int pcc_sub_writes(Instruction* ins, SymReg* r);

/* This should be common with Cola */

char *str_dup(const char *);
char *str_cat(const char *, const char *);

/* globals */



EXTERN char * sourcefile;	/* current file */
EXTERN char * function;	/* current function */
EXTERN int        line;	/* and line */
EXTERN int optimizer_level;
EXTERN int dont_optimize;
EXTERN int has_compile;
EXTERN int allocated;


EXTERN enum {
	OPT_NONE,
	OPT_PRE,
	OPT_CFG = 	0x002,
	OPT_SUB = 	0x004,
	OPT_PASM =      0x100,
	OPT_J = 	0x200
} enum_opt;

struct imcc_ostat {
	int deleted_labels;
	int if_branch;
	int branch_branch;
	int invariants_moved;
	int deleted_ins;
	int used_once;
} ;

EXTERN struct imcc_ostat ostat;

typedef struct {
    int imcc_warn;
    int verbose;
    int debug;
    /* CFG stuff */
    int bb_list_size;
    int n_basic_blocks;
    Basic_block **bb_list;
    Set** dominators;
    int n_loops;
    Loop_info ** loop_info;
    Edge * edge_list;
    /* register allocation */
    int n_spilled;
    SymReg * p31;
    SymReg** interference_graph;
    SymReg** reglist;
    int n_symbols;
} imcc_info_t;

#define IMCC_INFO(i) ((imcc_info_t*) (i)->imcc_info)
#endif


/*
 * Local variables:
 * c-indentation-style: bsd
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 *
 * vim: expandtab shiftwidth=4:
*/
