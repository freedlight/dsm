// dsmio.c - I/O routines for DSM
// copyright (c) 1994, Freedlight Software

#include "dsm.h"

//****************
// input routines
//****************

// get next input byte - may or may not be EOF
boolean getn(void)
{
	buf = getc(infil);
	if (buf == EOF)
		return FALSE;
	buf &= 0xFF;
	return TRUE;
}

// get next input byte - cannot be EOF
short getnxt(void)
{
	if (!getn())
	{
		eoferr();
		return 0;
	}
	return buf;
}

void eoferr(void)
{
	fprintf(stderr, "Unexpected EOF\n");
	endflg = TRUE;
}

//****************************
// high level output routines
//****************************

// output current address
void putpc(void)
{
	STAB * sp;
	char adstr[16];

	if (maxpc > 0xFFFFFF)
		sprintf(adstr, "L%08lX", pc);
	else if (maxpc > 0xFFFF)
		sprintf(adstr, "L%06lX", pc);
	else
		sprintf(adstr, "L%04X", pc);
	if ((sp = (STAB *)findsym(htab,adstr)) != 0)
	{
		outs(adstr);
		sp->used = TRUE;
		outc(':');
	}
	else
	{
		outc(' ');
		if (maxpc > 0xFFFFFF)
			putword32(pc);
		else if (maxpc > 0xFFFF)
			putword24(pc);
		else
			putword(pc);
		outc(' ');
	}
}

// output opcode string
void putopc(char *s)
{
	outs(s);
	putsp(argsp-strlen(s));
	spcnt = 0;
}

// output register name
void putreg(char *s)
{
	outs(s);
}

// output opcode argument string
void putarg(char *s)
{
	outs(s);
}

// output 1-byte address
void putadr1(short n)
{
	char adstr[10];

	sprintf(adstr,"D%02X",n);
	if (apass == 1)
		addaddr(adstr,n);
	else
	{
		if ((STAB *)findsym(htab,adstr) != 0)
			outs(adstr);
		else
			puthexbyte(n);
	}
}

// output 2-byte address
void putadr2(short hi, short lo)
{
	putaddr((hi * 256) + lo);
}

// output 1-word address
void putaddr(ADDRESS n)
{
	char adstr[10];

	sprintf(adstr,"L%04X",n);
	if (apass == 1)
		addaddr(adstr,n);
	else
	{
		if ((STAB *)findsym(htab,adstr) != 0)
			outs(adstr);
		else
			puthexword(n);
	}
}

// output 4-byte address
void putadr4(short a, short b, short c, short d)
{
	putladdr(((long)a * 65536L * 256L) + ((long)b * 65536L) + (c * 256L) + d);
}

// output 3-byte address
void putadr3(short a, short b, short c)
{
	putladdr(((long)a * 65536L) + (b * 256L) + c);
}

// output 32-bit address
void putladdr(ADDRESS n)
{
	char adstr[16];

	if (maxpc > 0xFFFFFF)
		sprintf(adstr,"L%08lX",n);
	else
		sprintf(adstr,"L%06lX",n);
	if (apass == 1)
		addaddr(adstr,n);
	else
	{
		if ((STAB *)findsym(htab,adstr) != 0)
			outs(adstr);
		else
			puthexdword(n);
	}
}

void addaddr(char *s, ADDRESS n)
{
	STAB * sp;

	if (apass > 1)
		return;
	if ((STAB *)findsym(htab,s) == 0)
	{
		sp = (STAB *)addsym(htab,s,sizeof(STAB));
		sp->syma = n;
		sp->used = FALSE;
	}
}

// output a data byte
void putdb(short n)
{
	putsp(opcsp);
	putopc(".DB");
	puthexbyte(n);
}

// output to comment area
void discom(short n)
{
	while (n++ < cmtsp)
		outc(' ');
	outc(';');
}

// output ASCII value of char
void disch(short n)
{
	if ((n < 0x20) || (n > 0x7E))
		outc('.');
	else
		outc(n);
	pc++;
}

void enddata1(short a)
{
	discom(spcnt);
	disch(a);
	putcr();
	curblk += 16;
}

void enddata2(short a, short b)
{
	discom(spcnt);
	disch(a);
	disch(b);
	putcr();
	curblk += 16;
}

void enddata3(short a, short b, short c)
{
	discom(spcnt);
	disch(a);
	disch(b);
	disch(c);
	putcr();
	curblk += 16;
}

void enddata4(short a, short b, short c, short d)
{
	discom(spcnt);
	disch(a);
	disch(b);
	disch(c);
	disch(d);
	putcr();
	curblk += 16;
}

void enddata5(short a, short b, short c, short d, short e)
{
	discom(spcnt);
	disch(a);
	disch(b);
	disch(c);
	disch(d);
	disch(e);
	putcr();
	curblk += 16;
}

void enddata6(short a, short b, short c, short d, short e, short f)
{
	discom(spcnt);
	disch(a);
	disch(b);
	disch(c);
	disch(d);
	disch(e);
	disch(f);
	putcr();
	curblk += 16;
}

//************************************
// intermediate level output routines
//************************************

// output a hex word
void putword32(unsigned long n)
{
	char buf[16];

	sprintf(buf,"%08lX",n);
	outs(buf);
}

// output a hex word
void putword24(unsigned long n)
{
	char buf[16];

	sprintf(buf,"%06lX",n);
	outs(buf);
}

// output a hex word
void putword(unsigned n)
{
	char buf[6];

	sprintf(buf,"%04X",n);
	outs(buf);
}

void puthexword(unsigned n)
{
	putdoll();
	putword(n);
}

void puthexdword(unsigned long n)
{
	putdoll();
	putword(n / 65536L);
	putword(n % 65536L);
}

// output a hex byte
void putbyte(short n)
{
	char buf[4];

	sprintf(buf,"%02X",n);
	outs(buf);
}

void puthexbyte(short n)
{
	putdoll();
	putbyte(n);
}

// output a small decimal number
void putnum(short n)
{
	char buf[4];

	sprintf(buf,"%d",n);
	outs(buf);
}

// output immediate data word value
void putimm8(short n1, short n2, short n3, short n4)
{
	putpound();
	putdoll();
	putbyte(n1);
	putbyte(n2);
	putbyte(n3);
	putbyte(n4);
}

// output immediate data word value
void putimm6(short n1, short n2, short n3)
{
	putpound();
	putdoll();
	putbyte(n1);
	putbyte(n2);
	putbyte(n3);
}

// output immediate data word value
void putimm4(short n1, short n2)
{
	putpound();
	putdoll();
	putbyte(n1);
	putbyte(n2);
}

// output immediate data byte value
void putimm(short n)
{
	putpound();
	puthexbyte(n);
}

// output n spaces
void putsp(short n)
{
	short i;

	for (i=0; i<n; i++)
		outc(' ');
}

// output a return
void putcr(void)
{
	outc('\n');
	curblk++;	// for implicit LF
}

// output a hex indicator
void putdoll(void)
{
	outc('$');
}

// output a open paren
void putopn(void)
{
	outc('(');
}

// output a close paren
void putclo(void)
{
	outc(')');
}

// output a comma
void putcomma(void)
{
	outc(',');
}

// output a number sign
void putpound(void)
{
	outc('#');
}

// output an at sign
void putat(void)
{
	outc('@');
}

// output a decrement
void putdecr(void)
{
	outc('-');
	outc('-');
}

// output an increment
void putincr(void)
{
	outc('+');
	outc('+');
}

//***************************
// low level output routines
//***************************

// output a string
void outs(char *s)
{
	if (apass == 1)
		return;
	fprintf(outfil, "%s", s);
	curblk += strlen(s);
	spcnt += strlen(s);
}

// output a character
void outc(short c)
{
	if (apass == 1)
		return;
	putc(c,outfil);
	curblk++;
	spcnt++;
}

