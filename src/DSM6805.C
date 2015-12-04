// dsm6805.c - module to handle 6805 codes for DSM
// copyright (c) 1994, Freedlight Software

#include "dsm.h"

static char otyp6805[] = {
	31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,	// 00 - 0F
	21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,	// 10 - 1F
	22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,	// 20 - 2F
	23,00,00,23,23,00,23,23,23,23,23,00,23,23,00,23,	// 30 - 3F
	11,00,00,11,11,00,11,11,11,11,11,00,11,11,00,11,	// 40 - 4F
	12,00,00,12,12,00,12,12,12,12,12,00,12,12,00,12,	// 50 - 5F
	25,00,00,25,25,00,25,25,25,25,25,00,25,25,00,25,	// 60 - 6F
	13,00,00,13,13,00,13,13,13,13,13,00,13,13,00,13,	// 70 - 7F
	10,10,00,10,00,00,00,00,00,00,00,00,00,00,10,10,	// 80 - 8F
	00,00,00,00,00,00,00,10,10,10,10,10,10,10,00,10,	// 90 - 9F
	24,24,24,24,24,24,24,00,24,24,24,24,00,24,24,00,	// A0 - AF
	23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,	// B0 - BF
	32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,	// C0 - CF
	33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,	// D0 - DF
	25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,	// E0 - EF
	13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13		// F0 - FF
};

static char *onam6805[] = {
// 00 - 07
	"BRSET","BRCLR","BRSET","BRCLR","BRSET","BRCLR","BRSET","BRCLR",
// 08 - 0F
	"BRSET","BRCLR","BRSET","BRCLR","BRSET","BRCLR","BRSET","BRCLR",
// 10 - 17
	"BSET" ,"BCLR" ,"BSET" ,"BCLR" ,"BSET" ,"BCLR" ,"BSET" ,"BCLR",
// 18 - 1F
	"BSET" ,"BCLR" ,"BSET" ,"BCLR" ,"BSET" ,"BCLR" ,"BSET" ,"BCLR",
// 20 - 27
	"BRA"  ,"BRN"  ,"BHI"  ,"BLS"  ,"BCC"  ,"BCS"  ,"BNE"  ,"BEQ",
// 28 - 2F
	"BHCC" ,"BHCS" ,"BPL"  ,"BMI"  ,"BMC"  ,"BMS"  ,"BIL"  ,"BIH",
// 30 - 37
	"NEG"  ,""     ,""     ,"COM"  ,"LSR"  ,""     ,"ROR"  ,"ASR",
// 38 - 3F
	"LSL"  ,"ROL"  ,"DEC"  ,""     ,"INC"  ,"TST"  ,""     ,"CLR",
// 40 - 47
	"NEG"  ,""     ,""     ,"COM"  ,"LSR"  ,""     ,"ROR"  ,"ASR",
// 48 - 4F
	"LSL"  ,"ROL"  ,"DEC"  ,""     ,"INC"  ,"TST"  ,""     ,"CLR",
// 50 - 57
	"NEG"  ,""     ,""     ,"COM"  ,"LSR"  ,""     ,"ROR"  ,"ASR",
// 58 - 5F
	"LSL"  ,"ROL"  ,"DEC"  ,""     ,"INC"  ,"TST"  ,""     ,"CLR",
// 60 - 67
	"NEG"  ,""     ,""     ,"COM"  ,"LSR"  ,""     ,"ROR"  ,"ASR",
// 68 - 6F
	"LSL"  ,"ROL"  ,"DEC"  ,""     ,"INC"  ,"TST"  ,""     ,"CLR",
// 70 - 77
	"NEG"  ,""     ,""     ,"COM"  ,"LSR"  ,""     ,"ROR"  ,"ASR",
// 78 - 7F
	"LSL"  ,"ROL"  ,"DEC"  ,""     ,"INC"  ,"TST"  ,""     ,"CLR",
// 80 - 87
	"RTI"  ,"RTS"  ,""     ,"SWI"  ,""     ,""     ,""     ,"",
// 88 - 8F
	""     ,""     ,""     ,""     ,""     ,""     ,"STOP" ,"WAIT",
// 90 - 97
	""     ,""     ,""     ,""     ,""     ,""     ,""     ,"TAX",
// 98 - 9F
	"CLC"  ,"SEC"  ,"CLI"  ,"SEI"  ,"RSP"  ,"NOP"  ,""     ,"TXA",
// A0 - A7
	"SUB"  ,"CMP"  ,"SBC"  ,"CPX"  ,"AND"  ,"BIT"  ,"LDA"  ,"",
// A8 - AF
	"EOR"  ,"ADC"  ,"ORA"  ,"ADD"  ,""     ,"BSR"  ,"LDX"  ,"",
// B0 - B7
	"SUB"  ,"CMP"  ,"SBC"  ,"CPX"  ,"AND"  ,"BIT"  ,"LDA"  ,"STA",
// B8 - BF
	"EOR"  ,"ADC"  ,"ORA"  ,"ADD"  ,"JMP"  ,"JSR"  ,"LDX"  ,"STX",
// C0 - C7
	"SUB"  ,"CMP"  ,"SBC"  ,"CPX"  ,"AND"  ,"BIT"  ,"LDA"  ,"STA",
// C8 - CF
	"EOR"  ,"ADC"  ,"ORA"  ,"ADD"  ,"JMP"  ,"JSR"  ,"LDX"  ,"STX",
// D0 - D7
	"SUB"  ,"CMP"  ,"SBC"  ,"CPX"  ,"AND"  ,"BIT"  ,"LDA"  ,"STA",
// D8 - DF
	"EOR"  ,"ADC"  ,"ORA"  ,"ADD"  ,"JMP"  ,"JSR"  ,"LDX"  ,"STX",
// E0 - E7
	"SUB"  ,"CMP"  ,"SBC"  ,"CPX"  ,"AND"  ,"BIT"  ,"LDA"  ,"STA",
// E8 - EF
	"EOR"  ,"ADC"  ,"ORA"  ,"ADD"  ,"JMP"  ,"JSR"  ,"LDX"  ,"STX",
// F0 - F7
	"SUB"  ,"CMP"  ,"SBC"  ,"CPX"  ,"AND"  ,"BIT"  ,"LDA"  ,"STA",
// F8 - FF
	"EOR"  ,"ADC"  ,"ORA"  ,"ADD"  ,"JMP"  ,"JSR"  ,"LDX"  ,"STX"
};

static char *oarg6805[] = {
// 00 - 07
	"0,", "0,", "1,", "1,", "2,", "2,", "3,", "3,",
// 08 - 0F
	"4,", "4,", "5,", "5,", "6,", "6,", "7,", "7,",
// 10 - 17
	"0,", "0,", "1,", "1,", "2,", "2,", "3,", "3,",
// 18 - 1F
	"4,", "4,", "5,", "5,", "6,", "6,", "7,", "7,"
};

static void d6805init(void)
{
	opcsp = 10;
	argsp = 6;
	cmtsp = 12;
	init = TRUE;
}

static void d1_6805(short x)
{
	data1(x);
	putopc(onam6805[x]);
	switch (ofmt)
	{
		case 0:		// opr
			break;
		case 1:		// opr A
			putreg("A");
			break;
		case 2:		// opr X
			putreg("X");
			break;
		case 3:		// opr ,X
			putcomma();
			putreg("X");
			break;
	}
	enddata1(x);
	if ((x == 0x80) || (x == 0x81))	// RTS, RTI
		putcr();
}

static void d2_6805(short x, short y)
{
	short adr;

	data2(x, y);
	putopc(onam6805[x]);
	switch (ofmt)
	{
		case 1:		// opr bit,$nn
			putarg(oarg6805[x]);
			putadr1(y);
			break;
		case 2:		// pc relative
			if (y > 0x80)
				adr = (pc + 2) - (0x100 - y);
			else
				adr = (pc + 2) + y;
			putaddr(adr);
			break;
		case 3:		// opr $nn
			putadr1(y);
			break;
		case 4:		// opr #$nn
			putimm(y);
			break;
		case 5:		// opr $nn,X
			putadr1(y);
			putcomma();
			putreg("X");
			break;
	}
	enddata2(x, y);
}

static void d3_6805(short x, short y, short z)
{
	short adr;

	data3(x, y, z);
	putopc(onam6805[x]);
	switch (ofmt)
	{
		case 1:		// opr bit,$nn,$nnnn
			if (z > 0x80)
				adr = (pc + 2) - (0x100 - z);
			else
				adr = (pc + 2) + z;
			putarg(oarg6805[x]);
			putadr1(y);
			putcomma();
			putaddr(adr);
			break;
		case 2:		// opr $nnnn
			putadr2(y,z);
			break;
		case 3:		// opr $nnnn,X
			putadr2(y,z);
			putcomma();
			putreg("X");
			break;
	}
	enddata3(x, y, z);
}

void dsm6805(short n)
{
	short x,y;

	if (!init)
		d6805init();
	if (!otyp6805[n])
	{
		inval(n);
		return;
	}
#if DEBUG
	printf("op=%d pval=%d\n",n,otyp6805[n]);
#endif
	omod = otyp6805[n] / 10;
	ofmt = otyp6805[n] % 10;
	if (omod == 1)
		d1_6805(n);
	else if (omod == 2)
	{
		x = getnxt();
		d2_6805(n,x);
	}
	else if (omod == 3)
	{
		x = getnxt();
		y = getnxt();
		d3_6805(n,x,y);
	}
}

