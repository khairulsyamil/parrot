typedef union {
    int t;
    char * s;
    SymReg * sr;
    Instruction *i;
} YYSTYPE;
#define	CALL	258
#define	GOTO	259
#define	ARG	260
#define	RET	261
#define	PRINT	262
#define	IF	263
#define	UNLESS	264
#define	NEW	265
#define	END	266
#define	SAVEALL	267
#define	RESTOREALL	268
#define	SUB	269
#define	NAMESPACE	270
#define	CLASS	271
#define	ENDCLASS	272
#define	SYM	273
#define	LOCAL	274
#define	PARAM	275
#define	PUSH	276
#define	POP	277
#define	INC	278
#define	DEC	279
#define	SHIFT_LEFT	280
#define	SHIFT_RIGHT	281
#define	INTV	282
#define	FLOATV	283
#define	STRINGV	284
#define	DEFINED	285
#define	LOG_XOR	286
#define	RELOP_EQ	287
#define	RELOP_NE	288
#define	RELOP_GT	289
#define	RELOP_GTE	290
#define	RELOP_LT	291
#define	RELOP_LTE	292
#define	GLOBAL	293
#define	ADDR	294
#define	CLONE	295
#define	RESULT	296
#define	RETURN	297
#define	POW	298
#define	SHIFT_RIGHT_U	299
#define	LOG_AND	300
#define	LOG_OR	301
#define	COMMA	302
#define	LABEL	303
#define	EMIT	304
#define	EOM	305
#define	IREG	306
#define	NREG	307
#define	SREG	308
#define	PREG	309
#define	IDENTIFIER	310
#define	STRINGC	311
#define	INTC	312
#define	FLOATC	313
#define	REG	314
#define	MACRO	315
#define	PARROT_OP	316
#define	VAR	317


extern YYSTYPE yylval;
