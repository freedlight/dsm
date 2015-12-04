// dsm6801.c - module to handle 6801 codes for DSM
// copyright (c) 1994, Freedlight Software

#include "dsm.h"

static char otyp6801[] = {
	00,10,00,00,10,10,10,10,10,10,10,10,10,10,10,10,	// 00 - 0F
	10,10,00,00,00,00,10,10,10,10,10,10,00,00,00,00,	// 10 - 1F
	22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,	// 20 - 2F
	10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,	// 30 - 3F
	11,00,00,11,11,00,11,11,11,11,11,00,11,11,00,11,	// 40 - 4F
	12,00,00,12,12,00,12,12,12,12,12,00,12,12,00,12,	// 50 - 5F
	24,34,34,24,24,34,24,24,24,24,24,34,24,24,24,24,	// 60 - 6F
	31,33,33,31,31,33,31,31,31,31,31,33,31,31,31,31,	// 70 - 7F
	23,23,23,32,23,23,23,00,23,23,23,23,32,22,32,00,	// 80 - 8F
	21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,	// 90 - 9F
	24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,	// A0 - AF
	31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,	// B0 - BF
	23,23,23,32,23,23,23,00,23,23,23,23,32,00,32,00,	// C0 - CF
	21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,	// D0 - DF
	24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,	// E0 - EF
	31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31		// F0 - FF
};

static char *onam6801[] = {
// 00 - 07
	""     ,"NOP"  ,""     ,""     ,"LSRD" ,"ASLD" ,"TAP"  ,"TPA",
// 08 - 0F
	"INX"  ,"DEX"  ,"CLV"  ,"SEV"  ,"CLC"  ,"SEC"  ,"CLI"  ,"SEI",
// 10 - 17
	"SBA"  ,"CBA"  ,""     ,""     ,""     ,""     ,"TAB"  ,"TBA",
// 18 - 1F
	"XGDX" ,"DAA"  ,"SLEEP","ABA"  ,""     ,""     ,""     ,"",
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
	"NEG"  ,"AIM"  ,"OIM"  ,"COM"  ,"LSR"  ,"EIM"  ,"ROR"  ,"ASR",
// 68 - 6F
	"ASL"  ,"ROL"  ,"DEC"  ,"TIM"  ,"INC"  ,"TST"  ,"JMP"  ,"CLR",
// 70 - 77
	"NEG"  ,"AIM"  ,"OIM"  ,"COM"  ,"LSR"  ,"EIM"  ,"ROR"  ,"ASR",
// 78 - 7F
	"ASL"  ,"ROL"  ,"DEC"  ,"TIM"  ,"INC"  ,"TST"  ,"JMP"  ,"CLR",
// 80 - 87
	"SUBA" ,"CMPA" ,"SBCA" ,"SUBD" ,"ANDA" ,"BITA" ,"LDAA" ,"",
// 88 - 8F
	"EORA" ,"ADCA" ,"ORAA" ,"ADDA" ,"CPX"  ,"BSR"  ,"LDS"  ,"",
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
	"EORB" ,"ADCB" ,"ORAB" ,"ADDB" ,"LDD"  ,""     ,"LDX"  ,"",
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

static void d6801init(void)
{
	opcsp = 10;
	argsp = 6;
	cmtsp = 12;
	init = TRUE;
}

static void d1_6801(short x)
{
	data1(x);
	putopc(onam6801[x]);
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

static void d2_6801(short x, short y)
{
	short adr;

	data2(x, y);
	putopc(onam6801[x]);
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
	}
	enddata2(x, y);
}

static void d3_6801(short x, short y, short z)
{
	data3(x, y, z);
	putopc(onam6801[x]);
	switch(ofmt)
	{
		case 1:		// opr $nnnn
			putadr2(y,z);
			break;
		case 2:		// opr #$nnnn
			putimm4(y,z);
			break;
		case 3:		// opr #$nn,$nn,X
			putimm(y);
			putcomma();
			putadr1(z);
			putcomma();
			putreg("X");
			break;
		case 4:		// opr #$nn,nn
			putimm(y);
			putcomma();
			putadr1(z);
			break;
	}
	enddata3(x, y, z);
}

void dsm6801(short n)
{
	short x,y;

	if (!init)
		d6801init();
	if (!otyp6801[n])
	{
		inval(n);
		return;
	}
#if DEBUG
	printf("op=%d pval=%d\n",n,otyp6801[n]);
#endif
	omod = otyp6801[n] / 10;
	ofmt = otyp6801[n] % 10;
	if (omod == 1)
		d1_6801(n);
	else if (omod == 2)
	{
		x = getnxt();
		d2_6801(n,x);
	}
	else if (omod == 3)
	{
		x = getnxt();
		y = getnxt();
		d3_6801(n,x,y);
	}
}

