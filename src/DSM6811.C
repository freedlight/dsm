// dsm6811.c - module to handle 6811 codes for DSM
// copyright (c) 1994, Freedlight Software

#include "dsm.h"

/*
	10 opr
	11	opr A
	12	opr B

	21	opr $nn
	22 rel br
	23 opr #$nn
	24 opr $nn,X
	25 opr $nn,Y

	31 opr $nnnn
	32 opr #$nnnn
	33 opr #$nn,$nn
	34 opr $nn,#$nn
	35 opr $nn,X,#$nn
	36 opr $nn,Y,#$nn

	41 opr $nn,#$nn,$nn
	42 opr $nn,X,#$nn,$nn
	43 opr $nn,Y,#$nn,$nn
*/
static char otyp6811[] = {
	10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,	// 00 - 0F
	10,10,41,41,34,34,10,10,90,10,90,10,35,35,42,42,	// 10 - 1F
	22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,	// 20 - 2F
	10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,	// 30 - 3F
	11,00,00,11,11,00,11,11,11,11,11,00,11,11,00,11,	// 40 - 4F
	12,00,00,12,12,00,12,12,12,12,12,00,12,12,00,12,	// 50 - 5F
	24,00,00,24,24,00,24,24,24,24,24,00,24,24,24,24,	// 60 - 6F
	31,00,00,31,31,00,31,31,31,31,31,00,31,31,31,31,	// 70 - 7F
	23,23,23,32,23,23,23,00,23,23,23,23,32,22,32,10,	// 80 - 8F
	21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,	// 90 - 9F
	24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,	// A0 - AF
	31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,	// B0 - BF
	23,23,23,32,23,23,23,00,23,23,23,23,32,90,32,10,	// C0 - CF
	21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,	// D0 - DF
	24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,	// E0 - EF
	31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31		// F0 - FF
};

static char *onam6811[] = {
// 00 - 07
	"TEST" ,"NOP"  ,"IDIV" ,"FDIV" ,"LSRD" ,"ASLD" ,"TAP"  ,"TPA",
// 08 - 0F
	"INX"  ,"DEX"  ,"CLV"  ,"SEV"  ,"CLC"  ,"SEC"  ,"CLI"  ,"SEI",
// 10 - 17
	"SBA"  ,"CBA"  ,"BRSET","BRCLR","BSET" ,"BCLR" ,"TAB"  ,"TBA",
// 18 - 1F
	""     ,"DAA"  ,""     ,"ABA"  ,"BSET" ,"BCLR" ,"BRSET","BRCLR",
// 20 - 27
	"BRA"  ,"BRN"  ,"BHI"  ,"BLS"  ,"BCC"  ,"BCS"  ,"BNE"  ,"BEQ",
// 28 - 2F
	"BVC"  ,"BVS"  ,"BPL"  ,"BMI"  ,"BGE"  ,"BLT"  ,"BGT"  ,"BLE",
// 30 - 37
	"TSX"  ,"INS"  ,"PULA" ,"PULB" ,"DES"  ,"TXS"  ,"PSHA" ,"PSHB",
// 38 - 3F
	"PULX" ,"RTS"  ,"ABX"  ,"RTI"  ,"PSHX" ,"MUL"  ,"WAIT" ,"SWI",
// 40 - 47
	"NEG"  ,""     ,""     ,"COM"  ,"LSR"  ,""     ,"ROR"  ,"ASR",
// 48 - 4F
	"ASL"  ,"ROL"  ,"DEC"  ,""     ,"INC"  ,"TST"  ,""     ,"CLR",
// 50 - 57
	"NEG"  ,""     ,""     ,"COM"  ,"LSR"  ,""     ,"ROR"  ,"ASR",
// 58 - 5F
	"ASL"  ,"ROL"  ,"DEC"  ,""     ,"INC"  ,"TST"  ,""     ,"CLR",
// 60 - 67
	"NEG"  ,""     ,""     ,"COM"  ,"LSR"  ,""     ,"ROR"  ,"ASR",
// 68 - 6F
	"ASL"  ,"ROL"  ,"DEC"  ,""     ,"INC"  ,"TST"  ,"JMP"  ,"CLR",
// 70 - 77
	"NEG"  ,""     ,""     ,"COM"  ,"LSR"  ,""     ,"ROR"  ,"ASR",
// 78 - 7F
	"ASL"  ,"ROL"  ,"DEC"  ,""     ,"INC"  ,"TST"  ,"JMP"  ,"CLR",
// 80 - 87
	"SUBA" ,"CMPA" ,"SBCA" ,"SUBD" ,"ANDA" ,"BITA" ,"LDAA" ,"",
// 88 - 8F
	"EORA" ,"ADCA" ,"ORAA" ,"ADDA" ,"CPX"  ,"BSR"  ,"LDS"  ,"XGDX",
// 90 - 97
	"SUBA" ,"CMPA" ,"SBCA" ,"SUBD" ,"ANDA" ,"BITA" ,"LDAA" ,"STAA",
// 98 - 9F
	"EORA" ,"ADCA" ,"ORAA" ,"ADDA" ,"CPX"  ,"JSR"  ,"LDS"  ,"STS",
// A0 - A7
	"SUBA" ,"CMPA" ,"SBCA" ,"SUBD" ,"ANDA" ,"BITA" ,"LDAA" ,"STAA",
// A8 - AF
	"EORA" ,"ADCA" ,"ORAA" ,"ADDA" ,"CPX"  ,"JSR"  ,"LDS"  ,"STS",
// B0 - B7
	"SUBA" ,"CMPA" ,"SBCA" ,"SUBD" ,"ANDA" ,"BITA" ,"LDAA" ,"STAA",
// B8 - BF
	"EORA" ,"ADCA" ,"ORAA" ,"ADDA" ,"CPX"  ,"JSR"  ,"LDS"  ,"STS",
// C0 - C7
	"SUBB" ,"CMPB" ,"SBCB" ,"ADDD" ,"ANDB" ,"BITB" ,"LDAB" ,"",
// C8 - CF
	"EORB" ,"ADCB" ,"ORAB" ,"ADDB" ,"LDD"  ,""     ,"LDX"  ,"STOP",
// D0 - D7
	"SUBB" ,"CMPB" ,"SBCB" ,"ADDD" ,"ANDB" ,"BITB" ,"LDAB" ,"STAB",
// D8 - DF
	"EORB" ,"ADCB" ,"ORAB" ,"ADDB" ,"LDD"  ,"STD"  ,"LDX"  ,"STX",
// E0 - E7
	"SUBB" ,"CMPB" ,"SBCB" ,"ADDD" ,"ANDB" ,"BITB" ,"LDAB" ,"STAB",
// E8 - EF
	"EORB" ,"ADCB" ,"ORAB" ,"ADDB" ,"LDD"  ,"STD"  ,"LDX"  ,"STX",
// F0 - F7
	"SUBB" ,"CMPB" ,"SBCB" ,"ADDD" ,"ANDB" ,"BITB" ,"LDAB" ,"STAB",
// F8 - FF
	"EORB" ,"ADCB" ,"ORAB" ,"ADDB" ,"LDD"  ,"STD"  ,"LDX"  ,"STX"
};

static void d6811init(void)
{
	opcsp = 13;
	argsp = 6;
	cmtsp = 18;
	init = TRUE;
}

static void d1_6811(short x, char *opc)
{
	data1(x);
	putopc(opc);
	switch (ofmt)
	{
		case 0:		// opr
			break;
		case 1:		// opr A
			putreg("A");
			break;
		case 2:		// opr B
			putreg("B");
			break;
	}
	enddata1(x);
	if ((x == 0x39) || (x == 0x3B))	// RTS, RTI
		putcr();
}

static void d2_6811(short x, short y, char *opc)
{
	short adr;

	data2(x, y);
	putopc(opc);
	switch (ofmt)
	{
		case 1:		// opr $nn
			putadr1(y);
			break;
		case 2:		// pc relative
			if (y > 0x80)
				adr = (pc + 2) - (0x100 - y);
			else
				adr = (pc + 2) + y;
			putaddr(adr);
			break;
		case 3:		// opr #$nn
			putimm(y);
			break;
		case 4:		// opr $nn,X
			putadr1(y);
			putcomma();
			putreg("X");
			break;
		case 5:		// opr $nn,Y
			putadr1(y);
			putcomma();
			putreg("Y");
			break;
	}
	enddata2(x, y);
}

static void d3_6811(short x, short y, short z, char *opc)
{
	data3(x, y, z);
	putopc(opc);
	switch(ofmt)
	{
		case 1:		// opr $nnnn
			if (y == 0)
				putadr1(z);
			else
				putadr2(y,z);
			break;
		case 2:		// opr #$nnnn
			putimm4(y,z);
			break;
		case 3:		// opr #$nn,$nn
			putimm(y);
			putcomma();
			putadr1(z);
			break;
		case 4:		// opr $nn,#$nn
			putadr1(y);
			putcomma();
			putimm(z);
			break;
		case 5:		// opr $nn,X,#$nn
			putadr1(y);
			putcomma();
			putreg("X");
			putcomma();
			putimm(z);
			break;
		case 6:		// opr $nn,Y,#$nn
			putadr1(y);
			putcomma();
			putreg("Y");
			putcomma();
			putimm(z);
			break;
	}
	enddata3(x, y, z);
}

static void d4_6811(short w, short x, short y, short z, char *opc)
{
	short adr;

	data4(w, x, y, z);
	putopc(opc);
	switch (ofmt)
	{
		case 1:		// opr $nn,#$nn,$nn
			putadr1(x);
			putcomma();
			putimm(y);
			putcomma();
			if (z > 0x80)
				adr = (pc + 4) - (0x100 - z);
			else
				adr = (pc + 4) + z;
			putaddr(adr);
			break;
		case 2:		// opr $nn,X,#$nn,$nn
			putadr1(x);
			putcomma();
			putreg("X");
			putcomma();
			putimm(y);
			putcomma();
			if (z > 0x80)
				adr = (pc + 4) - (0x100 - z);
			else
				adr = (pc + 4) + z;
			putaddr(adr);
			break;
		case 3:		// opr $nn,Y,#$nn,$nn
			putadr1(x);
			putcomma();
			putreg("Y");
			putcomma();
			putimm(y);
			putcomma();
			if (z > 0x80)
				adr = (pc + 4) - (0x100 - z);
			else
				adr = (pc + 4) + z;
			putaddr(adr);
			break;
	}
	enddata3(x, y, z);
}

void do1_6811(short n, short fmt, char *opc)
{
	ofmt = fmt;
	d1_6811(n, opc);
}

void do2_6811(short n, short fmt, char *opc)
{
	short x;

	x = getnxt();
	ofmt = fmt;
	d2_6811(n, x, opc);
}

void do3_6811(short n, short fmt, char *opc)
{
	short x,y;

	x = getnxt();
	y = getnxt();
	ofmt = fmt;
	d3_6811(n, x, y, opc);
}

void do4_6811(short n, short fmt, char *opc)
{
	short x,y,z;

	x = getnxt();
	y = getnxt();
	z = getnxt();
	ofmt = fmt;
	d4_6811(n, x, y, z, opc);
}

static void inval_6811(short n, short x)
{
	inval(n);
	pc--;	// because of correction below
	putpc();
	putsp(1);
	inval(x);
}

static void d9_6811(short n)
{
	short x;

	x = getnxt();
	pc++;	// pc is 1 more than it seems
	if (n == 0x18)
	{
		switch (x)
		{
			case 0x08: do1_6811(n, 0, "INY");	break;
			case 0x09: do1_6811(n, 0, "DEY");	break;
			case 0x1C: do3_6811(n, 6, "BSET");	break;
			case 0x1D: do3_6811(n, 6, "BCLR");	break;
			case 0x1E: do4_6811(n, 3, "BRSET");	break;
			case 0x1F: do4_6811(n, 3, "BRCLR");	break;
			case 0x30: do1_6811(n, 0, "TSY");	break;
			case 0x35: do1_6811(n, 0, "TYS");	break;
			case 0x38: do1_6811(n, 0, "PULY");	break;
			case 0x3A: do1_6811(n, 0, "ABY");	break;
			case 0x3C: do1_6811(n, 0, "PSHY");	break;
			case 0x60: do2_6811(n, 5, "NEG");	break;
			case 0x63: do2_6811(n, 5, "COM");	break;
			case 0x64: do2_6811(n, 5, "LSR");	break;
			case 0x66: do2_6811(n, 5, "ROR");	break;
			case 0x67: do2_6811(n, 5, "ASR");	break;
			case 0x68: do2_6811(n, 5, "ASL");	break;
			case 0x69: do2_6811(n, 5, "ROL");	break;
			case 0x6A: do2_6811(n, 5, "DEC");	break;
			case 0x6C: do2_6811(n, 5, "INC");	break;
			case 0x6D: do2_6811(n, 5, "TST");	break;
			case 0x6E: do2_6811(n, 5, "JMP");	break;
			case 0x6F: do2_6811(n, 5, "CLR");	break;
			case 0x8C: do3_6811(n, 2, "CPY");	break;
			case 0x8F: do1_6811(n, 0, "XGDY");	break;
			case 0x9C: do2_6811(n, 1, "CPY");	break;
			case 0xA0: do2_6811(n, 5, "SUBA");	break;
			case 0xA1: do2_6811(n, 5, "CMPA");	break;
			case 0xA2: do2_6811(n, 5, "SBCA");	break;
			case 0xA3: do2_6811(n, 5, "SUBD");	break;
			case 0xA4: do2_6811(n, 5, "ANDA");	break;
			case 0xA5: do2_6811(n, 5, "BITA");	break;
			case 0xA6: do2_6811(n, 5, "LDAA");	break;
			case 0xA7: do2_6811(n, 5, "STAA");	break;
			case 0xA8: do2_6811(n, 5, "EORA");	break;
			case 0xA9: do2_6811(n, 5, "ADCA");	break;
			case 0xAA: do2_6811(n, 5, "ORAA");	break;
			case 0xAB: do2_6811(n, 5, "ADDA");	break;
			case 0xAC: do2_6811(n, 5, "CPY");	break;
			case 0xAD: do2_6811(n, 5, "JSR");	break;
			case 0xAE: do2_6811(n, 5, "LDS");	break;
			case 0xAF: do2_6811(n, 5, "STS");	break;
			case 0xBC: do3_6811(n, 1, "CPY");	break;
			case 0xCE: do3_6811(n, 2, "LDY");	break;
			case 0xDE: do2_6811(n, 1, "LDY");	break;
			case 0xDF: do2_6811(n, 1, "STY");	break;
			case 0xE0: do2_6811(n, 5, "SUBB");	break;
			case 0xE1: do2_6811(n, 5, "CMPB");	break;
			case 0xE2: do2_6811(n, 5, "SBCB");	break;
			case 0xE3: do2_6811(n, 5, "ADDD");	break;
			case 0xE4: do2_6811(n, 5, "ANDB");	break;
			case 0xE5: do2_6811(n, 5, "BITB");	break;
			case 0xE6: do2_6811(n, 5, "LDAB");	break;
			case 0xE7: do2_6811(n, 5, "STAB");	break;
			case 0xE8: do2_6811(n, 5, "EORB");	break;
			case 0xE9: do2_6811(n, 5, "ADCB");	break;
			case 0xEA: do2_6811(n, 5, "ORAB");	break;
			case 0xEB: do2_6811(n, 5, "ADDB");	break;
			case 0xEC: do2_6811(n, 5, "LDD");	break;
			case 0xED: do2_6811(n, 5, "STD");	break;
			case 0xEE: do2_6811(n, 5, "LDY");	break;
			case 0xEF: do2_6811(n, 5, "STY");	break;
			case 0xFE: do3_6811(n, 1, "LDY");	break;
			case 0xFF: do3_6811(n, 1, "STY");	break;	
			default:	inval_6811(n, x); break;
		}
	}
	else if (n == 0x1A)
	{
		switch (x)
		{
			case 0x83: do3_6811(n, 2, "CPD");	break;	
			case 0x93: do2_6811(n, 1, "CPD");	break;	
			case 0xA3: do2_6811(n, 4, "CPD");	break;	
			case 0xAC: do2_6811(n, 4, "CPY");	break;	
			case 0xB3: do3_6811(n, 1, "CPD");	break;	
			case 0xEE: do2_6811(n, 4, "LDY");	break;	
			case 0xEF: do2_6811(n, 4, "STY");	break;	
			default:	inval_6811(n, x); break;
		}
	}
	else if (n == 0xCD)
	{
		switch (x)
		{
			case 0xA3: do2_6811(n, 5, "CPD");	break;	
			case 0xAC: do2_6811(n, 5, "CPX");	break;	
			case 0xEE: do2_6811(n, 5, "LDX");	break;	
			case 0xEF: do2_6811(n, 5, "STX");	break;	
			default:	inval_6811(n, x); break;
		}
	}
}

void dsm6811(short n)
{
	short x,y,z;

	if (!init)
		d6811init();
	if (!otyp6811[n])
	{
		inval(n);
		return;
	}
#if DEBUG
	printf("op=%d pval=%d\n",n,otyp6811[n]);
#endif
	omod = otyp6811[n] / 10;
	ofmt = otyp6811[n] % 10;
	if (omod == 1)
		d1_6811(n, onam6811[n]);
	else if (omod == 2)
	{
		x = getnxt();
		d2_6811(n, x, onam6811[n]);
	}
	else if (omod == 3)
	{
		x = getnxt();
		y = getnxt();
		d3_6811(n, x, y, onam6811[n]);
	}
	else if (omod == 4)
	{
		x = getnxt();
		y = getnxt();
		z = getnxt();
		d4_6811(n, x, y, z, onam6811[n]);
	}
	else if (omod == 9)
		d9_6811(n);
}

