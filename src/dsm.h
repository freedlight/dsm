/* dsm.h - equates amd globals for dsm.c */
/* copyright (c) 1987, Freedlight Software */

#include <stdio.h>
#include <ctype.h>
#include <alloc.h>
#include <string.h>
#include <stdlib.h>
#include <dir.h>

typedef unsigned char	boolean;
typedef unsigned short	WORD;

#ifndef TRUE
#define TRUE	1
#define FALSE	0
#endif

#include "hash.h"
#include "cputype.h"

#define DEBUG	FALSE
#define HTABSIZ 401	/* size of hash table */

#define MAXC	500		/* number of code sections */
#define MAXD	500		/* number of data sections */

typedef unsigned long ADDRESS;

#define ADDR0	0L		/* zero address */

/* symbol storage */
typedef struct {
	unsigned long syma;	/* symbol value */
	boolean	used;		/* flag if located in object */
} STAB;

//***********
// macros
//***********

#define dim(s)			(sizeof(s)/sizeof(s[0]))
#define streq(s1,s2)	(strcmp((s1),(s2)) == 0)
#define atoh(s)			(strtol(s, NULL, 16))

//***********
// variables
//***********

#ifdef __MAIN
#define	GLOBAL	
#else
#define	GLOBAL	extern
#endif

GLOBAL FILE		*infil;			/* input object file */
GLOBAL FILE		*outfil;		/* output text file */
GLOBAL FILE		*parfil;		/* parameter text file */

GLOBAL short	buf;			/* byte buffer */
GLOBAL short	mach;			/* cpu class */
GLOBAL short	submach;		/* cpu subclass */
GLOBAL short	curlin;			/* line of data block output */
GLOBAL short	outnxt;			/* output module counter */
GLOBAL short	maxdat;			/* max data limit array poshorter */
GLOBAL short	maxcod;			/* max data limit array poshorter */
GLOBAL short	opcsp;			/* output spacing params */
GLOBAL short	argsp;			/*	"	*/
GLOBAL short	cmtsp;			/*	"	*/
GLOBAL short	omod;			/* CPU parsing variables */
GLOBAL short	ofmt;			/*	"	*/
GLOBAL short	oext;			/*	"	*/
GLOBAL short	apass;			/* analysis pass */
GLOBAL short	spcnt;			/* count of arg chars */

GLOBAL boolean	invnxt;			/* already fetched next */
GLOBAL boolean	init;			/* cpu parser initialized */
GLOBAL boolean	parms;			/* got input params */
GLOBAL boolean	noout;			/* output on/off flag */
GLOBAL boolean	codflg;			/* TRUE if in code section */
GLOBAL boolean	datflg;			/* TRUE if in data section */
GLOBAL boolean	endflg;			/* TRUE if end of file seen */

GLOBAL ADDRESS	pc;				/* current pc pointer */
GLOBAL ADDRESS	orgpc;			/* starting pc value */
GLOBAL ADDRESS	maxpc;			/* maximum pc value */
GLOBAL ADDRESS	offset;			/* offset to starting pc value */
GLOBAL ADDRESS	curblk;			/* chars currently output */
GLOBAL ADDRESS	blksiz;			/* chars output per module */
GLOBAL ADDRESS	endlst;			/* ending pc value */
GLOBAL ADDRESS	datlst[MAXD];	/* data section list */
GLOBAL ADDRESS	datsav[MAXD];
GLOBAL ADDRESS	codlst[MAXC];	/* code section list */
GLOBAL ADDRESS	codsav[MAXC];

GLOBAL HASH_TAB *htab;			/* hashtable pointer */

GLOBAL char		outnam[40];
GLOBAL char		*scanptr;

/***********************/
/* function prototypes */
/***********************/

/* dsm.c */
void checkmod(void);
void initmain(void);
void initpass(void);
void openall(char *name);
void outcod(short n);
void outdat(short n);
void inval(short n);
void handleparm(void);
char *gettok(void);
void cpupars(char *cpu);
void opennxt(void);
void prsym(char *sym, void *sp);
void symlist(void);
void error(char *s);
void defext(char *s, char *ext);
void rmext(char *s);
ADDRESS makenum(char *s);
void data1(short a);
void data2(short a, short b);
void data3(short a, short b, short c);
void data4(short a, short b, short c, short d);
void data5(short a, short b, short c, short d, short e);
void data6(short a, short b, short c, short d, short e, short f);

/* dsmio.c */
short	getnxt(void);
boolean	getn(void);
void	eoferr(void);
void	disch(short n);
void	discom(short n);
void	enddata1(short a);
void	enddata2(short a, short b);
void	enddata3(short a, short b, short c);
void	enddata4(short a, short b, short c, short d);
void	enddata5(short a, short b, short c, short d, short e);
void	enddata6(short a, short b, short c, short d, short e, short f);
void	putpc(void);
void	putopc(char *s);
void	putreg(char *s);
void	putarg(char *s);
void	putadr1(short n);
void	putadr2(short hi, short lo);
void	putadr3(short a, short b, short c);
void	putadr4(short a, short b, short c, short d);
void	putaddr(ADDRESS n);
void	putladdr(ADDRESS n);
void	addaddr(char *s, ADDRESS n);
void	putdb(short n);
void	putimm(short n);
void	putimm4(short n1, short n2);
void	putimm6(short n1, short n2, short n3);
void	putimm8(short n1, short n2, short n3, short n4);
void	putword(unsigned n);
void	putword24(unsigned long n);
void	putword32(unsigned long n);
void	puthexword(unsigned n);
void	puthexdword(unsigned long n);
void	putbyte(short n);
void	puthexbyte(short n);
void	putnum(short n);
void	putsp(short n);
void	putcr(void);
void	putdoll(void);
void	putincr(void);
void	putdecr(void);
void	putopn(void);
void	putclo(void);
void	putcomma(void);
void	putpound(void);
void	putat(void);
void	outs(char *s);
void	outc(short c);

/* cpu files */
void	dsm6502(short n);
void	dsm6801(short n);
void	dsm6805(short n);
void	dsm6809(short n);
void	dsm6811(short n);
void	dsm8051(short n);
void	dsm8080(short n);
void	dsmH8(short n);
void	dsmRSC(short n);
void	dsmZ80(short n);

