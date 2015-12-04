// dsmz80.c - module to handle Z80 codes for DSM
// copyright (c) 1994, Freedlight Software

#include "dsm.h"

static char tmp_nam[20];
static char tmp_arg[20];

static char otypZ80[] = {
	10,30,10,10,10,10,20,10,10,10,10,10,10,10,20,10,	// 00 - 0F
	21,30,10,10,10,10,20,10,21,10,10,10,10,10,20,10,	// 10 - 1F
	21,30,31,10,10,10,20,10,21,10,32,10,10,10,20,10,	// 20 - 2F
	21,30,31,10,10,10,20,10,21,10,32,10,10,10,20,10,	// 30 - 3F
	10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,	// 40 - 4F
	10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,	// 50 - 5F
	10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,	// 60 - 6F
	10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,	// 70 - 7F
	10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,	// 80 - 8F
	10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,	// 90 - 9F
	10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,	// A0 - AF
	10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,	// B0 - BF
	10,10,30,30,30,10,20,10,10,10,30,40,30,30,20,10,	// C0 - CF
	10,10,30,22,30,10,20,10,10,10,30,23,30,50,20,10,	// D0 - DF
	10,10,30,10,30,10,20,10,10,10,30,10,30,60,20,10,	// E0 - EF
	10,10,30,10,30,10,20,10,10,10,30,10,30,70,20,10		// F0 - FF
};

static char otypZ80DF[] = {
	00,00,00,00,00,00,00,00,00,20,00,00,00,00,00,00,	// 00 - 0F
	00,00,00,00,00,00,00,00,00,20,00,00,00,00,00,00,	// 10 - 1F
	00,40,41,20,00,00,00,00,00,20,43,20,00,00,00,00,	// 20 - 2F
	00,00,00,00,30,30,42,00,00,20,00,00,00,00,00,00,	// 30 - 3F
	00,00,00,00,00,00,30,00,00,00,00,00,00,00,30,00,	// 40 - 4F
	00,00,00,00,00,00,30,00,00,00,00,00,00,00,30,00,	// 50 - 5F
	00,00,00,00,00,00,30,00,00,00,00,00,00,00,30,00,	// 60 - 6F
	31,31,31,31,31,31,00,31,00,00,00,00,00,00,30,00,	// 70 - 7F
	00,00,00,00,00,00,30,00,00,00,00,00,00,00,30,00,	// 80 - 8F
	00,00,00,00,00,00,30,00,00,00,00,00,00,00,30,00,	// 90 - 9F
	00,00,00,00,00,00,30,00,00,00,00,00,00,00,30,00,	// A0 - AF
	00,00,00,00,00,00,30,00,00,00,00,00,00,00,30,00,	// B0 - BF
	00,00,00,00,00,00,00,00,00,00,00,44,00,00,00,00,	// C0 - CF
	00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,	// D0 - DF
	00,20,00,20,00,20,00,00,00,20,00,00,00,00,00,00,	// E0 - EF
	00,00,00,00,00,00,00,00,00,20,00,00,00,00,00,00		// F0 - FF
};

static char otypZ80ED[] = {
	00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,	// 00 - 0F
	00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,	// 10 - 1F
	00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,	// 20 - 2F
	00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,	// 30 - 3F
	20,20,20,41,20,20,20,20,20,20,20,42,00,20,00,20,	// 40 - 4F
	20,20,20,41,00,00,20,20,20,20,20,42,00,00,20,20,	// 50 - 5F
	20,20,20,00,00,00,00,20,20,20,20,00,00,00,00,20,	// 60 - 6F
	00,00,20,41,00,00,00,00,20,20,20,42,00,00,00,00,	// 70 - 7F
	00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,	// 80 - 8F
	00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,	// 90 - 9F
	20,20,20,20,00,00,00,00,20,20,20,20,00,00,00,00,	// A0 - AF
	20,20,20,20,00,00,00,00,20,20,20,20,00,00,00,00,	// B0 - BF
	00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,	// C0 - CF
	00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,	// D0 - DF
	00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,	// E0 - EF
	00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00		// F0 - FF
};

static char *onamZ80[] = {
// 00 - 07
	"NOP" ,"LD"  ,"LD"  ,"INC" ,"INC" ,"DEC" ,"LD"  ,"RLCA",
// 08 - 0F
	"EX"  ,"ADD" ,"LD"  ,"DEC" ,"INC" ,"DEC" ,"LD"  ,"RRCA",
// 10 - 17
	"DJNZ","LD"  ,"LD"  ,"INC" ,"INC" ,"DEC" ,"LD"  ,"RLA",
// 18 - 1F
	"JR"  ,"ADD" ,"LD"  ,"DEC" ,"INC" ,"DEC" ,"LD"  ,"RRA",
// 20 - 27
	"JR"  ,"LD"  ,"LD"  ,"INC" ,"INC" ,"DEC" ,"LD"  ,"DAA",
// 28 - 2F
	"JR"  ,"ADD" ,"LD"  ,"DEC" ,"INC" ,"DEC" ,"LD"  ,"CPL",
// 30 - 37
	"JR"  ,"LD"  ,"LD"  ,"INC" ,"INC" ,"DEC" ,"LD"  ,"SCF",
// 38 - 3F
	"JR"  ,"ADD" ,"LD"  ,"DEC" ,"INC" ,"DEC" ,"LD"  ,"CCF",
// 40 - 47
	"LD"  ,"LD"  ,"LD"  ,"LD"  ,"LD"  ,"LD"  ,"LD"  ,"LD",
// 48 - 4F
	"LD"  ,"LD"  ,"LD"  ,"LD"  ,"LD"  ,"LD"  ,"LD"  ,"LD",
// 50 - 57
	"LD"  ,"LD"  ,"LD"  ,"LD"  ,"LD"  ,"LD"  ,"LD"  ,"LD",
// 58 - 5F
	"LD"  ,"LD"  ,"LD"  ,"LD"  ,"LD"  ,"LD"  ,"LD"  ,"LD",
// 60 - 67
	"LD"  ,"LD"  ,"LD"  ,"LD"  ,"LD"  ,"LD"  ,"LD"  ,"LD",
// 68 - 6F
	"LD"  ,"LD"  ,"LD"  ,"LD"  ,"LD"  ,"LD"  ,"LD"  ,"LD",
// 70 - 77
	"LD"  ,"LD"  ,"LD"  ,"LD"  ,"LD"  ,"LD"  ,"HALT","LD",
// 78 - 7F
	"LD"  ,"LD"  ,"LD"  ,"LD"  ,"LD"  ,"LD"  ,"LD"  ,"LD",
// 80 - 87
	"ADD" ,"ADD" ,"ADD" ,"ADD" ,"ADD" ,"ADD" ,"ADD" ,"ADD",
// 88 - 8F
	"ADC" ,"ADC" ,"ADC" ,"ADC" ,"ADC" ,"ADC" ,"ADC" ,"ADC",
// 90 - 97
	"SUB" ,"SUB" ,"SUB" ,"SUB" ,"SUB" ,"SUB" ,"SUB" ,"SUB",
// 98 - 9F
	"SBC" ,"SBC" ,"SBC" ,"SBC" ,"SBC" ,"SBC" ,"SBC" ,"SBC",
// A0 - A7
	"AND" ,"AND" ,"AND" ,"AND" ,"AND" ,"AND" ,"AND" ,"AND",
// A8 - AF
	"XOR" ,"XOR" ,"XOR" ,"XOR" ,"XOR" ,"XOR" ,"XOR" ,"XOR",
// B0 - B7
	"OR"  ,"OR"  ,"OR"  ,"OR"  ,"OR"  ,"OR"  ,"OR"  ,"OR",
// B8 - BF
	"CP"  ,"CP"  ,"CP"  ,"CP"  ,"CP"  ,"CP"  ,"CP"  ,"CP",
// C0 - C7
	"RET" ,"POP" ,"JP"  ,"JP"  ,"CALL","PUSH","ADD" ,"RST",
// C8 - CF
	"RET" ,"RET" ,"JP"  ,"?CB?","CALL","CALL","ADC" ,"RST",
// D0 - D7
	"RET" ,"POP" ,"JP"  ,"OUT" ,"CALL","PUSH","SUB" ,"RST",
// D8 - DF
	"RET" ,"EXX" ,"JP"  ,"IN"  ,"CALL","?DD?","SBC" ,"RST",
// E0 - E7
	"RET" ,"POP" ,"JP"  ,"EX"  ,"CALL","PUSH","AND" ,"RST",
// E8 - EF
	"RET" ,"JP"  ,"JP"  ,"EX"  ,"CALL","?ED?","XOR" ,"RST",
// F0 - F7
	"RET" ,"POP" ,"JP"  ,"DI"  ,"CALL","PUSH","OR"  ,"RST",
// F8 - FF
	"RET" ,"LD"  ,"JP"  ,"EI"  ,"CALL","?FD?","CP"  ,"RST"
};

static char *oargZ80[] = {
// 00 - 07
	" "     ,"BC,"   ,"(BC),A","BC"     ,"B"     ,"B"     ,"B,"    ," ",
// 08 - 0F
	"AF,AF'","HL,BC" ,"A,(BC)","BC"     ,"C"     ,"C"     ,"C,"    ," ",
// 10 - 17
	""      ,"DE,"   ,"(DE),A","DE"     ,"D"     ,"D"     ,"D,"    ," ",
// 18 - 1F
	""      ,"HL,DE" ,"A,(DE)","DE"     ,"E"     ,"E"     ,"E,"    ," ",
// 20 - 27
	"NZ,"   ,"HL,"   ,",HL"   ,"HL"     ,"H"     ,"H"     ,"H,"    ," ",
// 28 - 2F
	"Z,"    ,"HL,HL" ,"HL,"   ,"HL"     ,"L"     ,"L"     ,"L,"    ," ",
// 30 - 37
	"NC,"   ,"SP,"   ,",A"    ,"SP"     ,"(HL)"  ,"(HL)"  ,"(HL)," ," ",
// 38 - 3F
	"C,"    ,"HL,SP" ,"A,"    ,"SP"     ,"A"     ,"A"     ,"A,"    ," ",
// 40 - 47
	"B,B"   ,"B,C"   ,"B,D"   ,"B,E"    ,"B,H"   ,"B,L"   ,"B,(HL)","B,A",
// 48 - 4F
	"C,B"   ,"C,C"   ,"C,D"   ,"C,E"    ,"C,H"   ,"C,L"   ,"C,(HL)","C,A",
// 50 - 57
	"D,B"   ,"D,C"   ,"D,D"   ,"D,E"    ,"D,H"   ,"D,L"   ,"D,(HL)","D,A",
// 58 - 5F
	"E,B"   ,"E,C"   ,"E,D"   ,"E,E"    ,"E,H"   ,"E,L"   ,"E,(HL)","E,A",
// 60 - 67
	"H,B"   ,"H,C"   ,"H,D"   ,"H,E"    ,"H,H"   ,"H,L"   ,"H,(HL)","H,A",
// 68 - 6F
	"L,B"   ,"L,C"   ,"L,D"   ,"L,E"    ,"L,H"   ,"L,L"   ,"L,(HL)","L,A",
// 70 - 77
	"(HL),B","(HL),C","(HL),D","(HL),E" ,"(HL),H","(HL),L"," "     ,"(HL),A",
// 78 - 7F
	"A,B"   ,"A,C"   ,"A,D"   ,"A,E"    ,"A,H"   ,"A,L"   ,"A,(HL)","A,A",
// 80 - 87
	"A,B"   ,"A,C"   ,"A,D"   ,"A,E"    ,"A,H"   ,"A,L"   ,"A,(HL)","A,A",
// 88 - 8F
	"A,B"   ,"A,C"   ,"A,D"   ,"A,E"    ,"A,H"   ,"A,L"   ,"A,(HL)","A,A",
// 90 - 97
	"B"     ,"C"     ,"D"     ,"E"      ,"H"     ,"L"     ,"(HL)"  ,"A",
// 98 - 9F
	"A,B"   ,"A,C"   ,"A,D"   ,"A,E"    ,"A,H"   ,"A,L"   ,"A,(HL)","A,A",
// A0 - A7
	"B"     ,"C"     ,"D"     ,"E"      ,"H"     ,"L"     ,"(HL)"  ,"A",
// A8 - AF
	"B"     ,"C"     ,"D"     ,"E"      ,"H"     ,"L"     ,"(HL)"  ,"A",
// B0 - B7
	"B"     ,"C"     ,"D"     ,"E"      ,"H"     ,"L"     ,"(HL)"  ,"A",
// B8 - BF
	"B"     ,"C"     ,"D"     ,"E"      ,"H"     ,"L"     ,"(HL)"  ,"A",
// C0 - C7
	"NZ"    ,"BC"    ,"NZ,"   ,""       ,"NZ,"   ,"BC"    ,"A,"    ,"00H",
// C8 - CF
	"Z"     ," "     ,"Z,"    ,""       ,"Z,"    ,""      ,"A,"    ,"08H",
// D0 - D7
	"NC"    ,"DE"    ,"NC,"   ,",A"     ,"NC,"   ,"DE"    ,""      ,"10H",
// D8 - DF
	"C"     ," "     ,"C,"    ,"A,"     ,"C,"    ,""      ,"A,"    ,"18H",
// E0 - E7
	"PO"    ,"HL"    ,"PO,"   ,"(SP),HL","PO,"   ,"HL"    ,""      ,"20H",
// E8 - EF
	"PE"    ,"(HL)"  ,"PE,"   ,"DE,HL"  ,"PE,"   ,""      ,""      ,"28H",
// F0 - F7
	"P"     ,"AF"    ,"P,"    ,""       ,"P,"    ,"AF"    ,""      ,"30H",
// F8 - FF
	"M"     ,"SP,HL" ,"M,"    ,""       ,"M,"    ,""      ,""      ,"38H"
};

void dZ80init(void)
{
	onamZ80[0xCB] = tmp_nam;
	oargZ80[0xCB] = tmp_arg;
	onamZ80[0xDD] = tmp_nam;
	oargZ80[0xDD] = tmp_arg;
	onamZ80[0xED] = tmp_nam;
	oargZ80[0xED] = tmp_arg;
	onamZ80[0xFD] = tmp_nam;
	oargZ80[0xFD] = tmp_arg;
	opcsp = 14;
	argsp = 6;
	cmtsp = 15;
	init = TRUE;
}

static void d1_Z80(short x)
{
	data1(x);
	putopc(onamZ80[x]);
	putarg(oargZ80[x]);
	enddata1(x);
	if (x == 0xC9)	// RET
		putcr();
}

static void d2_Z80(short x, short y)
{
	short adr;

	data2(x, y);
	putopc(onamZ80[x]);
	if (oext) // CB,DD,ED,FD
		putarg(oargZ80[x]);
	else
	switch (ofmt)
	{
		case 0:		// opc arg,nn
			putarg(oargZ80[x]);
			putadr1(y);
			break;
		case 1:		// pc relative
			if (y > 0x80)
				adr = (pc + 2) - (0x100 - y);
			else
				adr = (pc + 2) + y;
			putarg(oargZ80[x]);
			putaddr(adr);
			break;
		case 2:		// opc (nn)arg
			putopn();
			putadr1(y);
			putclo();
			putarg(oargZ80[x]);
			break;
		case 3:		// opc arg(nn)
			putarg(oargZ80[x]);
			putopn();
			putadr1(y);
			putclo();
			break;
	}
	enddata2(x, y);
}

static void d3_Z80(short x, short y, short z)
{
	short adr;

	data3(x, y, z);
	putopc(onamZ80[x]);
	if (oext) // DD,FD
	{
		if (z > 0x80)
			adr = (pc + 3) - (0x100 - z);
		else
			adr = (pc + 3) + z;
		if (ofmt == 1)
		{
			if (x == 0xDD)	// opc (IX+nnnn)arg
			{
				putopn();
				putreg("IX+");
				putaddr(adr);
				putclo();
				putarg(oargZ80[x]);
			}
			else if (x == 0xFD)	// opc (IY+nnnn)arg
			{
				putopn();
				putreg("IY+");
				putaddr(adr);
				putclo();
				putarg(oargZ80[x]);
			}
		}
		else			// opc arc,(relbr)
		{
			putarg(oargZ80[x]);
			putaddr(adr);
			putclo();
		}
	}
	else
	switch (ofmt)
	{
		case 0:		// opc arg,nnnn
			putarg(oargZ80[x]);
			putadr2(z,y);
			break;
		case 1:		// opc (nnnn)arg
			putopn();
			putadr2(z,y);
			putclo();
			putarg(oargZ80[x]);
			break;
		case 2:		// opc arg(nnnn)
			putarg(oargZ80[x]);
			putopn();
			putadr2(z,y);
			putclo();
			break;
	}
	enddata3(x, y, z);
}

static void d4_Z80(short n, short x, short y, short z)
{
	short adr;

	data4(n, x, y, z);
	putopc(onamZ80[n]);
	if ((n==0xDD) || (n==0xFD))
	{
		if (y > 0x80)
			adr = (pc + 4) - (0x100 - y);
		else
			adr = (pc + 4) + y;
		switch (ofmt)
		{
			case 1:		// opc (nnnn)arg
				putopn();
				putadr2(z,y);
				putclo();
				putarg(oargZ80[n]);
				break;
			case 2:		// opc arg(relbr),nn
				putarg(oargZ80[n]);
				putaddr(adr);
				putclo();
				putcomma();
				putbyte(z);
				break;
			case 3:		// opc arg(nnnn)
				putarg(oargZ80[n]);
				putopn();
				putadr2(z,y);
				putclo();
				break;
			case 4:		// opc arg(relbr)
				putarg(oargZ80[n]);
				putaddr(adr);
				putclo();
				break;
			default:		// opc arg,nnnn
				putarg(oargZ80[n]);
				putadr2(z,y);
				break;
		}
	}
	else if (n==0xED)
	{
		switch (ofmt)
		{
			case 1:		// opc (nnnn)arg
				putopn();
				putadr2(z,y);
				putclo();
				putarg(oargZ80[n]);
				break;
			case 2:		// opc arg(nnnn)
				putarg(oargZ80[n]);
				putopn();
				putadr2(z,y);
				putclo();
				break;
			default:		// opc arg,nnnn
				putarg(oargZ80[n]);
				putadr2(z,y);
				break;
		}
	}
	else					// opc arg,nnnn
	{
		putarg(oargZ80[n]);
		putadr2(z,y);
	}
	enddata4(n, x, y, z);
}

// module to handle Z80 CB xx codes
static void d_Z80CB(void)
{
	short x,savx;
	char *cp;

	oext = TRUE;
	savx = x = getnxt();
	if (x >= 0xC0)
		strcpy(tmp_nam,"SET");
	else if (x >= 0x80)
		strcpy(tmp_nam,"RES");
	else if (x >= 0x40)
		strcpy(tmp_nam,"BIT");
	else if (x >= 0x38)
		strcpy(tmp_nam,"SRL");
	else if (x >= 0x30)
	{
		inval(0xCB);
		buf = x;
		invnxt = TRUE;
		return;
	}
	else if (x >= 0x28)
		strcpy(tmp_nam,"SRA");
	else if (x >= 0x20)
		strcpy(tmp_nam,"SLA");
	else if (x >= 0x18)
		strcpy(tmp_nam,"RR");
	else if (x >= 0x10)
		strcpy(tmp_nam,"RL");
	else if (x >= 0x08)
		strcpy(tmp_nam,"RRC");
	else
		strcpy(tmp_nam,"RLC");
	if (x >= 0x40)
	{
		x &= 0x3F;
		if (x >= 0x38)
			strcpy(tmp_arg,"7,    ");
		else if (x >= 0x30)
			strcpy(tmp_arg,"6,    ");
		else if (x >= 0x28)
			strcpy(tmp_arg,"5,    ");
		else if (x >= 0x20)
			strcpy(tmp_arg,"4,    ");
		else if (x >= 0x18)
			strcpy(tmp_arg,"3,    ");
		else if (x >= 0x10)
			strcpy(tmp_arg,"2,    ");
		else if (x >= 0x08)
			strcpy(tmp_arg,"1,    ");
		else
			strcpy(tmp_arg,"0,    ");
		cp = tmp_arg + 2;
	}
	else
	{
		strcpy(tmp_arg,"    ");
		cp = tmp_arg;
	}
	x &= 07;
	switch (x)
	{
		case 0x00: *cp++ = 'B'; *cp = 0; break;
		case 0x01: *cp++ = 'C'; *cp = 0; break;
		case 0x02: *cp++ = 'D'; *cp = 0; break;
		case 0x03: *cp++ = 'E'; *cp = 0; break;
		case 0x04: *cp++ = 'H'; *cp = 0; break;
		case 0x05: *cp++ = 'L'; *cp = 0; break;
		case 0x06: *cp++ = '('; *cp++ = 'H'; *cp++ = 'L'; *cp = ')'; break;
		case 0x07: *cp++ = 'A'; *cp = 0; break;
	}
	d2_Z80(0xCB,savx);
}

static void maketxt(char *nam, char *arg)
{
	strcpy(tmp_nam,nam);
	strcpy(tmp_arg,arg);
}

// module to handle Z80 DD xx & FD xx codes
// flag=FALSE, 0xDD; flag=TRUE, 0xFD
static void d_Z80DF( boolean flag)
{
	short x,y,z,opc;
	char *cp;

	if (flag)
		opc = 0xFD;
	else
		opc = 0xDD;
	x = getnxt();
	omod = otypZ80DF[x] / 10;
	ofmt = otypZ80DF[x] % 10;
	oext = TRUE;
	if (!omod)
	{
		inval(opc);
		buf = x;
		invnxt = TRUE;
		return;
	}
	if (omod == 3)
		y = getnxt();
	if (omod == 4)
	{
		y = getnxt();
		z = getnxt();
	}
	switch(x)
	{
		case 0x09: maketxt("ADD","IX,BC");	break;
		case 0x19: maketxt("ADD","IX,DE");	break;
		case 0x21: maketxt("LD","IX,");		break;
		case 0x22: maketxt("LD",",IX");		break;
		case 0x23: maketxt("INC","IX");		break;
		case 0x29: maketxt("ADD","IX,IX");	break;
		case 0x2A: maketxt("LD","IX,");		break;
		case 0x2B: maketxt("DEC","IX");		break;
		case 0x34: maketxt("INC","(IX+");	break;
		case 0x35: maketxt("DEC","(IX+");	break;
		case 0x36: maketxt("LD","(IX+");	break;
		case 0x39: maketxt("ADD","IX,SP");	break;
		case 0x46: maketxt("LD","B,(IX+");	break;
		case 0x4E: maketxt("LD","C,(IX+");	break;
		case 0x56: maketxt("LD","D,(IX+");	break;
		case 0x5E: maketxt("LD","E,(IX+");	break;
		case 0x66: maketxt("LD","H,(IX+");	break;
		case 0x6E: maketxt("LD","L,(IX+");	break;
		case 0x70: maketxt("LD",",B");		break;
		case 0x71: maketxt("LD",",C");		break;
		case 0x72: maketxt("LD",",D");		break;
		case 0x73: maketxt("LD",",E");		break;
		case 0x74: maketxt("LD",",H");		break;
		case 0x75: maketxt("LD",",L");		break;
		case 0x77: maketxt("LD",",A");		break;
		case 0x7E: maketxt("LD","A,(IX+");	break;
		case 0x86: maketxt("ADD","A,(IX+");	break;
		case 0x8E: maketxt("ADC","A,(IX+");	break;
		case 0x96: maketxt("SUB","(IX+");	break;
		case 0x9E: maketxt("SBC","A,(IX+");	break;
		case 0xA6: maketxt("AND","(IX+");	break;
		case 0xAE: maketxt("XOR","(IX+");	break;
		case 0xB6: maketxt("OR","(IX+");	break;
		case 0xBE: maketxt("CP","(IX+");	break;
		case 0xCB:
			switch(z)
			{
				case 0x06: maketxt("RLC","(IX+");	break;
				case 0x0E: maketxt("RRC","(IX+");	break;
				case 0x16: maketxt("RL","(IX+");	break;
				case 0x1E: maketxt("RR","(IX+");	break;
				case 0x26: maketxt("SLA","(IX+");	break;
				case 0x2E: maketxt("SRA","(IX+");	break;
				case 0x3E: maketxt("SRL","(IX+");	break;
				case 0x46: maketxt("BIT","0,(IX+");	break;
				case 0x4E: maketxt("BIT","1,(IX+");	break;
				case 0x56: maketxt("BIT","2,(IX+");	break;
				case 0x5E: maketxt("BIT","3,(IX+");	break;
				case 0x66: maketxt("BIT","4,(IX+");	break;
				case 0x6E: maketxt("BIT","5,(IX+");	break;
				case 0x76: maketxt("BIT","6,(IX+");	break;
				case 0x7E: maketxt("BIT","7,(IX+");	break;
				case 0x86: maketxt("RES","0,(IX+");	break;
				case 0x8E: maketxt("RES","1,(IX+");	break;
				case 0x96: maketxt("RES","2,(IX+");	break;
				case 0x9E: maketxt("RES","3,(IX+");	break;
				case 0xA6: maketxt("RES","4,(IX+");	break;
				case 0xAE: maketxt("RES","5,(IX+");	break;
				case 0xB6: maketxt("RES","6,(IX+");	break;
				case 0xBE: maketxt("RES","7,(IX+");	break;
				case 0xC6: maketxt("SET","0,(IX+");	break;
				case 0xCE: maketxt("SET","1,(IX+");	break;
				case 0xD6: maketxt("SET","2,(IX+");	break;
				case 0xDE: maketxt("SET","3,(IX+");	break;
				case 0xE6: maketxt("SET","4,(IX+");	break;
				case 0xEE: maketxt("SET","5,(IX+");	break;
				case 0xF6: maketxt("SET","6,(IX+");	break;
				case 0xFE: maketxt("SET","7,(IX+");	break;
			}
			break;
		case 0xE1: maketxt("POP","IX");		break;
		case 0xE3: maketxt("EX","(SP),IX");	break;
		case 0xE5: maketxt("PUSH","IX");	break;
		case 0xE9: maketxt("JP","(IX)");	break;
		case 0xF9: maketxt("LD","SP,IX");	break;
	}
	if (flag)
	{
		while ((cp = strchr(tmp_arg,'X')) != NULL)
			*cp = 'Y';
	}
	if (omod == 2)
		d2_Z80(opc,x);
	else if (omod == 3)
		d3_Z80(opc,x,y);
	else if (omod == 4)
		d4_Z80(opc,x,y,z);
}

// module to handle Z80 ED xx codes
static void d_Z80ED(void)
{
	short x,y,z;

	x = getnxt();
	omod = otypZ80ED[x] / 10;
	ofmt = otypZ80ED[x] % 10;
	oext = TRUE;
	if (!omod)
	{
		inval(0xED);
		buf = x;
		invnxt = TRUE;
		return;
	}
	if (omod == 4)
	{
		y = getnxt();
		z = getnxt();
	}
	switch(x)
	{
		case 0x40: maketxt("IN","B,(C)");	break;
		case 0x41: maketxt("OUT","(C),B");	break;
		case 0x42: maketxt("SBC","HL,BC");	break;
		case 0x43: maketxt("LD",",BC");		break;
		case 0x44: maketxt("NEG"," ");		break;
		case 0x45: maketxt("RETN"," ");		break;
		case 0x46: maketxt("IM","0");		break;
		case 0x47: maketxt("LD","I,A");		break;
		case 0x48: maketxt("IN","C,(C)");	break;
		case 0x49: maketxt("OUT","(C),C");	break;
		case 0x4A: maketxt("ADC","HL,BC");	break;
		case 0x4B: maketxt("LD","BC,");		break;
		case 0x4D: maketxt("RETI"," ");		break;
		case 0x4F: maketxt("LD","R,A");		break;
		case 0x50: maketxt("IN","D,(C)");	break;
		case 0x51: maketxt("OUT","(C),D");	break;
		case 0x52: maketxt("SBC","HL,DE");	break;
		case 0x53: maketxt("LD",",DE");		break;
		case 0x56: maketxt("IM","1");		break;
		case 0x57: maketxt("LD","A,I");		break;
		case 0x58: maketxt("IN","E,(C)");	break;
		case 0x59: maketxt("OUT","(C),E");	break;
		case 0x5A: maketxt("ADC","HL,DE");	break;
		case 0x5B: maketxt("LD","DE,");		break;
		case 0x5E: maketxt("IM","2");		break;
		case 0x5F: maketxt("LD","A,R");		break;
		case 0x60: maketxt("IN","H,(C)");	break;
		case 0x61: maketxt("OUT","(C),H");	break;
		case 0x62: maketxt("SBC","HL,HL");	break;
		case 0x67: maketxt("RRD"," ");		break;
		case 0x68: maketxt("IN","L,(C)");	break;
		case 0x69: maketxt("OUT","(C),L");	break;
		case 0x6A: maketxt("ADC","HL,HL");	break;
		case 0x6F: maketxt("RLD"," ");		break;
		case 0x72: maketxt("SBC","HL,SP");	break;
		case 0x73: maketxt("LD",",SP");		break;
		case 0x78: maketxt("IN","A,(C)");	break;
		case 0x79: maketxt("OUT","(C),A");	break;
		case 0x7A: maketxt("ADC","HL,SP");	break;
		case 0x7B: maketxt("LD","SP,");		break;
		case 0xA0: maketxt("LDI"," ");		break;
		case 0xA1: maketxt("CPI"," ");		break;
		case 0xA2: maketxt("INI"," ");		break;
		case 0xA3: maketxt("OUTI"," ");		break;
		case 0xA8: maketxt("LDD"," ");		break;
		case 0xA9: maketxt("CPD"," ");		break;
		case 0xAA: maketxt("IND"," ");		break;
		case 0xAB: maketxt("OUTD"," ");		break;
		case 0xB0: maketxt("LDIR"," ");		break;
		case 0xB1: maketxt("CPIR"," ");		break;
		case 0xB2: maketxt("INIR"," ");		break;
		case 0xB3: maketxt("OTIR"," ");		break;
		case 0xB8: maketxt("LDDR"," ");		break;
		case 0xB9: maketxt("CPDR"," ");		break;
		case 0xBA: maketxt("INDR"," ");		break;
		case 0xBB: maketxt("OTDR"," ");		break;
	}
	if (omod == 2)
		d2_Z80(0xED,x);
	else if (omod == 4)
		d4_Z80(0xED,x,y,z);
}

void dsmZ80(short n)
{
	short x,y;

	if (!init)
		dZ80init();
	if (!otypZ80[n])
	{
		inval(n);
		return;
	}
#if DEBUG
	printf("op=%d pval=%d\n",n,otypZ80[n]);
#endif
	omod = otypZ80[n] / 10;
	ofmt = otypZ80[n] % 10;
	oext = FALSE;
	if (omod == 1)
		d1_Z80(n);
	else if (omod == 2)
	{
		x = getnxt();
		d2_Z80(n,x);
	}
	else if (omod == 3)
	{
		x = getnxt();
		y = getnxt();
		d3_Z80(n,x,y);
	}
	else if (omod == 4)
		d_Z80CB();
	else if (omod == 5)
		d_Z80DF(FALSE);
	else if (omod == 6)
		d_Z80ED();
	else if (omod == 7)
		d_Z80DF(TRUE);
	else
		inval(n);
}

