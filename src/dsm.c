// dsm - disassemble an object file
// copyright (c) 1994, Freedlight Software

#define __MAIN
#include "dsm.h"
#include <conio.h>

void error(char *s)
{
	fprintf(stderr, "%s\n", s);
	exit(3);
}

void main(short argc, char *argv[])
{
	char *cp;

	if (argc < 2)
		error("usage: dsm [parfile] [[-mn][-snnnn] objfile]");
	++argv;
	initmain();
	while (**argv == '-')
	{
		cp = *argv + 1;
		if (*cp == 's')
			offset = atoh(++cp);
		else if (*cp == 'm')
			mach = atoh(++cp);
		else
		{
			fprintf(stderr, "invalid option %s\n", *argv);
			exit(3);
		}
		++argv;
	}
	openall(*argv);
	initpass();
	if (!mach)
		error("must specify CPU type");
	for (;;)
	{
		if (!invnxt)		// already got next ?
			if (!getn())	// EOF ?
				endflg = TRUE;
		if (endflg)			// end of disassembly region ?
		{
			if (++apass > 2)
				break;
			initpass();
			continue;
		}
		checkmod();			// check if we are doing data or code
		if (!datflg)
		{
			putpc();
			putsp(1);
		}
		if (invnxt)			// not valid for object code - must be data
			inval(buf);
		else if (datflg)	// are we outputting data ?
			outdat(buf);
		else					// no - must be object code
			outcod(buf);
		if (!noout)			// check output limit
			if (curblk > blksiz)
				opennxt();
	}
	fclose(infil);
	symlist();
	outc('\n');
	fclose(outfil);
}

void initmain(void)
{
	outfil = stdout; // defaults
	codflg = noout = parms = TRUE;
	endflg = datflg = FALSE;
	mach = Xnone;
	pc = offset = ADDR0;
	curblk = 0L;
	maxdat = maxcod = 0;
	curlin = outnxt = 1;
	blksiz = 1000000L;
	opcsp = 14;
	apass = 1;
	htab = maketab(HTABSIZ); // allocate symbol table
}

void initpass(void)
{
	short i;

	if (offset > ADDR0)			// go to start of region
		fseek(infil, (long) offset, 0);
	else
		rewind(infil);
	pc = orgpc;
	codflg = TRUE;
	invnxt = endflg = datflg = FALSE;
	curblk = 0L;
	curlin = outnxt = 1;
	for (i=0; i<maxcod; i++)
		codlst[i] = codsav[i];
	for (i=0; i<maxdat; i++)
		datlst[i] = datsav[i];
}

// open input file
void openall(char *name)
{
	char filename[20];

	strcpy(filename,name);
	defext(filename,".par");
	if ((parfil = fopen(filename,"rt")) != NULL)
	{
		handleparm();
		return;
	}
	parms = FALSE;
	rmext(filename);
	defext(filename,".obj");
	if ((infil = fopen(filename,"rb")) == NULL)
		error("Can't open input file");
}

void checkmod(void)
{
	short i;

	for (i=0; i<maxdat; i++)
	{
		if (pc >= datlst[i])
		{
			datflg = TRUE;
			codflg = FALSE;
			datlst[i] = 0xFFFFFFFF;
			curlin = 8; // force first line
		}
	}
	for (i=0; i<maxcod; i++)
	{
		if (pc >= codlst[i])
		{
			codflg = TRUE;
			datflg = FALSE;
			codlst[i] = 0xFFFFFFFF;
			outc('\n');
			outc('\n');
		}
	}
}

// output object code byte
void outcod(short n)
{
	switch(mach)
	{
// implemented
		case X6502	: dsm6502(n);	break;
		case X6801	: dsm6801(n);	break;
		case X6805	: dsm6805(n);	break;
		case X6809	: dsm6809(n);	break;
		case X6811	: dsm6811(n);	break;
		case X8051	: dsm8051(n);	break;
		case X8080	: dsm8080(n);	break;
		case XH8	: dsmH8(n);		break;
		case XRSC	: dsmRSC(n);	break;
		case XZ80	: dsmZ80(n);	break;
// un-implemented
		case X1800	: // dsm1800(n);	break;
		case X32000	: // dsm32000(n);	break;
		case X34000	: // dsm34000(n);	break;
		case X3800	: // dsm3800(n);	break;
		case X56000	: // dsm56000(n);	break;
		case X62800	: // dsm62800(n);	break;
		case X6800	: // dsm6800(n);	break;
		case X6804	: // dsm6804(n);	break;
		case X68000	: // dsm68000(n);	break;
		case X7500	: // dsm7500(n);	break;
		case X7700	: // dsm7700(n);	break;
		case X7800	: // dsm7800(n);	break;
		case X8086	: // dsm8086(n);	break;
		case X8096	: // dsm8096(n);	break;
		case XCOP400: // dsmCOP400(n);	break;
		case XNCR32	: // dsmNCR32(n);	break;
		case XNOVA	: // dsmNOVA(n);	break;
		case XPDP8	: // dsmPDP8(n);	break;
		case XPDP11	: // dsmPDP11(n);	break;
		case XZ8		: // dsmZ8(n);		break;
		case XZ8000	: // dsmZ8000(n);	break;
						error("unimplemented CPU specified");
		default		:	error("invalid CPU specified");
	}
	if (pc >= endlst)
		endflg = TRUE;
}

// output data byte
void outdat(short n)
{
	if (curlin++ >= 8)
	{
		curlin = 1;
		putcr();
		putpc();
		putdb(n);
		curblk += 27L;
	}
	else
	{
		putcomma();
		puthexbyte(n);
		curblk += 4L;
	}
	pc++;
	if (pc >= endlst)
		endflg = TRUE;
}

void data1(short a)
{
	putbyte(a);
	putsp(opcsp-2);
}

void data2(short a, short b)
{
	putbyte(a);
	putsp(1);
	putbyte(b);
	putsp(opcsp - 5);
}

void data3(short a, short b, short c)
{
	putbyte(a);
	putsp(1);
	putbyte(b);
	putsp(1);
	putbyte(c);
	putsp(opcsp - 8);
}

void data4(short a, short b, short c, short d)
{
	putbyte(a);
	putsp(1);
	putbyte(b);
	putsp(1);
	putbyte(c);
	putsp(1);
	putbyte(d);
	putsp(opcsp - 11);
}

void data5(short a, short b, short c, short d, short e)
{
	putbyte(a);
	putsp(1);
	putbyte(b);
	putsp(1);
	putbyte(c);
	putsp(1);
	putbyte(d);
	putsp(1);
	putbyte(e);
	putsp(opcsp - 14);
}

void data6(short a, short b, short c, short d, short e, short f)
{
	putbyte(a);
	putsp(1);
	putbyte(b);
	putsp(1);
	putbyte(c);
	putsp(1);
	putbyte(d);
	putsp(1);
	putbyte(e);
	putsp(1);
	putbyte(f);
	putsp(opcsp - 17);
}

// record invalid opcode byte
void inval(short n)
{
	data1(n);
	putopc(".DB");
	puthexbyte(n);
	curblk += 21L;
	discom(spcnt);
	disch(n);
	putcr();
	invnxt = FALSE; // in case
}

//********************
// auxiliary file I/O
//********************

// parse parameter input file
void handleparm(void)
{
	char s[82], *op, *arg, *gettok();

	parms =  TRUE;
	while (fgets(s,80,parfil))
	{
		if (strlen(s) < 3)	// handle blank lines
			continue;
		if (s[0] == '*')	// handle comments
			continue;
		if (s[0] == ';')	// handle comments
			continue;
		scanptr = s;
		gettok();			// discard any leading space
		op = gettok();
		arg = gettok();
		if (*op != '.')	// directives must start with period
			continue;
		if (streq(op,".IN"))
		{
			if ((infil = fopen(arg,"rb")) == 0)
				error("Can't open input file");
		}
		else if (streq(op,".OUT"))
		{
			if ((outfil = fopen(arg,"wt")) == 0)
				error("Can't open output file");
			strcpy(outnam,arg);
			noout = FALSE;
			curblk = 0L;
		}
		else if (streq(op,".CPU"))
			cpupars(arg);
		else if (streq(op,".CODE"))
		{
			codsav[maxcod++] = makenum(arg);
			if (maxcod > MAXC)
				error("too many code sections");
		}
		else if (streq(op,".DATA"))
		{
			datsav[maxdat++] = makenum(arg);
			if (maxdat > MAXD)
				error("too many data sections");
		}
		else if (streq(op,".END"))
			endlst = makenum(arg);
		else if (streq(op,".PC") || streq(op,".ORG"))
			orgpc = makenum(arg);
		else if (streq(op,".OFFSET") || streq(op,".START"))
			offset = makenum(arg);
		else if (streq(op,".BLKSIZ"))
			blksiz = makenum(arg);
		else
			error("invalid command in param file");
	}
	fclose(parfil);
}

// search XASM.CPU file for cpu desired
void cpupars(char *cpu)
{
	FILE *f;
	char *p,fsp[64];
	scpu x;

	if (mach != Xnone)
		return;
	if ((p = getenv("XASM")) == NULL)
		strcpy(fsp,".");
	else
		strcpy(fsp,p);
	strcat(fsp,"\\xasm.cpu");
	if ((f = fopen(fsp,"rb")) == NULL)
		error("Can't open CPU file");
	while (fread(&x,sizeof(scpu),1,f))
	{
		if (streq(x.name,cpu))
			break;
	}
	fclose(f);
	mach = x.sclass;
	submach = x.subclass;
	maxpc = x.maxmem;
	if (!x.dactive)
		error("CPU specified not included");
}

char *gettok(void)
{
	char *pt;

	pt = scanptr;
	while (*scanptr && (!isspace(*scanptr)))
		scanptr++;
	while (*scanptr && isspace(*scanptr))
		*scanptr++ = 0;
	return(pt);
}

// open next output file
void opennxt(void)
{
	char fnam[64];

	if (apass == 1)
		return;
	outc('\n');
	fclose(outfil);
	rmext(outnam);
	sprintf(fnam, "%s.A%02d", outnam, outnxt++);
	strcpy(outnam, fnam);
	if ((outfil = fopen(outnam, "wt")) == 0)
		error("Can't open new output file");
	curblk = 0L;
}

void prsym(char *sym, void *sp)
{
	if (!((STAB *)sp)->used)
	{
		if (maxpc > 0xFFFF)
			fprintf(outfil,"%-8s\t%lX\n",sym,((STAB *)sp)->syma);
		else
			fprintf(outfil,"%-8s\t%X\n",sym,((STAB *)sp)->syma);
	}
}

void symlist(void)
{
	if (outnxt > 5)
		opennxt();
	fprintf(outfil,"\n\nleftover symbols\n\n");
	hash_print(htab,prsym);
}

void defext(char *s, char *ext)
{
	if (strchr(s, '.') == NULL)
		strcat(s, ext);
}

void rmext(char *s)
{
	char *p;

	if ((p = strchr(s, '.')) != NULL)
		*p = 0;
}

ADDRESS makenum(register char *s)
{
	char *p;

// number format - $xxxx
	if (s[0] == '$')
	{
		s++;
		return atoh(s);
	}
// number format - xxxx:xxxx (8086)
	else if ((p = strchr(s,':')) != 0)
	{
		*p++ = 0;
		return((atoh(s) * 16L) + atoh(p));
	}
// number format - xxxxh (Microsoft)
	else if (toupper(s[strlen(s)-1]) == 'H')
		return atoh(s);
// number format - decimal
	else
		return atol(s);
}
