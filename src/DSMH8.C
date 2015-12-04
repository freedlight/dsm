// dsmH8.c - module to handle H8/300 codes for DSM
// copyright (c) 1994, Freedlight Software

#include "dsm.h"

static char otypH8[] = {
	0x20,0x20,0x2F,0x2F,0x21,0x21,0x21,0x21,	//00-07
	0x25,0x25,0x24,0x2C,0x25,0x25,0x25,0x24,	//08-0F
	0x24,0x24,0x24,0x24,0x25,0x25,0x25,0x24,	//10-17
	0x25,0x25,0x24,0x2C,0x25,0x25,0x25,0x24,	//18-1F
	0x2D,0x2D,0x2D,0x2D,0x2D,0x2D,0x2D,0x2D,	//20-27
	0x2D,0x2D,0x2D,0x2D,0x2D,0x2D,0x2D,0x2D,	//28-2F
	0x2D,0x2D,0x2D,0x2D,0x2D,0x2D,0x2D,0x2D,	//30-37
	0x2D,0x2D,0x2D,0x2D,0x2D,0x2D,0x2D,0x2D,	//38-3F
	0x23,0x23,0x23,0x23,0x23,0x23,0x23,0x23,	//40-47
	0x23,0x23,0x23,0x23,0x23,0x23,0x23,0x23,	//48-4F
	0x25,0x25,0x25,0x25,0x20,0x23,0x20,0x2C,	//50-57
	0x46,0x27,0x41,0x28,0x46,0x27,0x41,0x28,	//58-5F
	0x2E,0x2E,0x2E,0x2E,0x25,0x25,0x25,0x2E,	//60-67
	0x2E,0x2E,0x42,0x42,0x2A,0x2B,0x43,0x43,	//68-6F
	0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,	//70-77
	0x77,0x47,0x67,0x40,0x45,0x45,0x45,0x45,	//78-7F
	0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,	//80-87
	0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,	//88-8F
	0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,	//90-97
	0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,	//98-9F
	0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,	//A0-A7
	0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,	//A8-AF
	0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,	//B0-B7
	0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,	//B8-BF
	0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,	//C0-C7
	0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,	//C8-CF
	0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,	//D0-D7
	0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,	//D8-DF
	0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,	//E0-E7
	0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,	//E8-EF
	0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,	//F0-F7
	0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22		//F8-FF
};

static char *onamH8[] = {
//00-07
	"NOP"   ,"SLEEP" ,"STC.B" ,"LDC.B" ,"ORC"   ,"XORC"  ,"ANDC"  ,"LDC"   ,
//08-0F
	"ADD.B" ,"ADD.W" ,"INC.B" ,"ADDS"  ,"MOV.B" ,"MOV.W" ,"ADDX"  ,"DAA"   ,
//10-17
	"SHLL"  ,"SHLR"  ,"ROTXL" ,"ROTXR" ,"OR.B"  ,"XOR.B" ,"AND.B" ,"NOT"   ,
//18-1F
	"SUB.B" ,"SUB.W" ,"DEC.B" ,"SUBS"  ,"CMP.B" ,"CMP.W" ,"SUBX"  ,"DAS"   ,
//20-27
	"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,
//28-2F
	"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,
//30-37
	"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,
//38-3F
	"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,
//40-47
	"BRA"   ,"BRN"   ,"BHI"   ,"BLS"   ,"BCC"   ,"BCS"   ,"BNE"   ,"BEQ"   ,
//48-4F
	"BVC"   ,"BVS"   ,"BPL"   ,"BMI"   ,"BGE"   ,"BLT"   ,"BGT"   ,"BLE"   ,
//50-57
	"MULXU.B","DIVXU.B","MULXU.W","DIVXU.W","RTS" ,"BSR" ,"RTE" ,"TRAPA"   ,
//58-5F
	""      ,"JMP"   ,"JMP"   ,"JMP"   ,"BSR"   ,"JSR"   ,"JSR"   ,"JSR"   ,
//60-67
	"BSET"  ,"BNOT"  ,"BCLR"  ,"BTST"  ,"OR.W"  ,"XOR.W" ,"AND.W" ,"BST"   ,
//68-6F
	"MOV.B" ,"MOV.W" ,"MOV.B" ,"MOV.W" ,"MOV.B" ,"MOV.W" ,"MOV.B" ,"MOV.W" ,
//70-77
	"BSET"  ,"BNOT"  ,"BCLR"  ,"BTST"  ,"BOR"   ,"BXOR"  ,"BAND"  ,"BLD"   ,
//78-7F
	""      ,"MOV.W" ,""      ,""      ,""      ,""      ,""      ,""      ,
//80-87
	"ADD.B" ,"ADD.B" ,"ADD.B" ,"ADD.B" ,"ADD.B" ,"ADD.B" ,"ADD.B" ,"ADD.B" ,
//88-8F
	"ADD.B" ,"ADD.B" ,"ADD.B" ,"ADD.B" ,"ADD.B" ,"ADD.B" ,"ADD.B" ,"ADD.B" ,
//90-97
	"ADDX"  ,"ADDX"  ,"ADDX"  ,"ADDX"  ,"ADDX"  ,"ADDX"  ,"ADDX"  ,"ADDX"  ,
//98-9F
	"ADDX"  ,"ADDX"  ,"ADDX"  ,"ADDX"  ,"ADDX"  ,"ADDX"  ,"ADDX"  ,"ADDX"  ,
//A0-A7
	"CMP.B" ,"CMP.B" ,"CMP.B" ,"CMP.B" ,"CMP.B" ,"CMP.B" ,"CMP.B" ,"CMP.B" ,
//A8-AF
	"CMP.B" ,"CMP.B" ,"CMP.B" ,"CMP.B" ,"CMP.B" ,"CMP.B" ,"CMP.B" ,"CMP.B" ,
//B0-B7
	"SUBX"  ,"SUBX"  ,"SUBX"  ,"SUBX"  ,"SUBX"  ,"SUBX"  ,"SUBX"  ,"SUBX"  ,
//B8-BF
	"SUBX"  ,"SUBX"  ,"SUBX"  ,"SUBX"  ,"SUBX"  ,"SUBX"  ,"SUBX"  ,"SUBX"  ,
//C0-C7
	"OR.B"  ,"OR.B"  ,"OR.B"  ,"OR.B"  ,"OR.B"  ,"OR.B"  ,"OR.B"  ,"OR.B"  ,
//C8-CF
	"OR.B"  ,"OR.B"  ,"OR.B"  ,"OR.B"  ,"OR.B"  ,"OR.B"  ,"OR.B"  ,"OR.B"  ,
//D0-D7
	"XOR.B" ,"XOR.B" ,"XOR.B" ,"XOR.B" ,"XOR.B" ,"XOR.B" ,"XOR.B" ,"XOR.B" ,
//D8-DF
	"XOR.B" ,"XOR.B" ,"XOR.B" ,"XOR.B" ,"XOR.B" ,"XOR.B" ,"XOR.B" ,"XOR.B" ,
//E0-E7
	"AND.B" ,"AND.B" ,"AND.B" ,"AND.B" ,"AND.B" ,"AND.B" ,"AND.B" ,"AND.B" ,
//E8-EF
	"AND.B" ,"AND.B" ,"AND.B" ,"AND.B" ,"AND.B" ,"AND.B" ,"AND.B" ,"AND.B" ,
//F0-F7
	"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,
//F8-FF
	"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B"
};

static char *onamH8hi[] = {
//00-07
	"NOP"   ,"SLEEP" ,"STC.B" ,"LDC.B" ,"ORC"   ,"XORC"  ,"ANDC"  ,"LDC"   ,
//08-0F
	"ADD.B" ,"ADD.W" ,"ADD.L" ,"INC"   ,"MOV.B" ,"MOV.W" ,"ADDX"  ,"MOV.L" ,
//10-17
	"SHAL"  ,"SHAR"  ,"ROTL"  ,"ROTR"  ,"OR"    ,"XOR"   ,"AND"   ,"NEG"   ,
//18-1F
	"SUB.B" ,"SUB.W" ,"SUB.L" ,"DEC"   ,"CMP.B" ,"CMP.W" ,"SUBX"  ,"CMP.L" ,
//20-27
	"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,
//28-2F
	"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,
//30-37
	"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,
//38-3F
	"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,
//40-47
	"BRA"   ,"BRN"   ,"BHI"   ,"BLS"   ,"BCC"   ,"BCS"   ,"BNE"   ,"BEQ"   ,
//48-4F
	"BVC"   ,"BVS"   ,"BPL"   ,"BMI"   ,"BGE"   ,"BLT"   ,"BGT"   ,"BLE"   ,
//50-57
	"MULXU.B","DIVXU.B","MULXU.W","DIVXU.W","RTS" ,"BSR" ,"RTE" ,"TRAPA"   ,
//58-5F
	""      ,"JMP"   ,"JMP"   ,"JMP"   ,"BSR"   ,"JSR"   ,"JSR"   ,"JSR"   ,
//60-67
	"BSET"  ,"BNOT"  ,"BCLR"  ,"BTST"  ,"OR.W"  ,"XOR.W" ,"AND.W" ,"BIST"  ,
//68-6F
	"MOV.B" ,"MOV.W" ,"MOV.B" ,"MOV.W" ,"MOV.B" ,"MOV.W" ,"MOV.B" ,"MOV.W" ,
//70-77
	"BSET"  ,"BIST"  ,"BCLR"  ,"BTST"  ,"BIOR"  ,"BIXOR" ,"BIAND" ,"BILD"  ,
//78-7F
	""      ,"MOV.W" ,""      ,""      ,""      ,""      ,""      ,""      ,
//80-87
	"ADD.B" ,"ADD.B" ,"ADD.B" ,"ADD.B" ,"ADD.B" ,"ADD.B" ,"ADD.B" ,"ADD.B" ,
//88-8F
	"ADD.B" ,"ADD.B" ,"ADD.B" ,"ADD.B" ,"ADD.B" ,"ADD.B" ,"ADD.B" ,"ADD.B" ,
//90-97
	"ADDX"  ,"ADDX"  ,"ADDX"  ,"ADDX"  ,"ADDX"  ,"ADDX"  ,"ADDX"  ,"ADDX"  ,
//98-9F
	"ADDX"  ,"ADDX"  ,"ADDX"  ,"ADDX"  ,"ADDX"  ,"ADDX"  ,"ADDX"  ,"ADDX"  ,
//A0-A7
	"CMP.B" ,"CMP.B" ,"CMP.B" ,"CMP.B" ,"CMP.B" ,"CMP.B" ,"CMP.B" ,"CMP.B" ,
//A8-AF
	"CMP.B" ,"CMP.B" ,"CMP.B" ,"CMP.B" ,"CMP.B" ,"CMP.B" ,"CMP.B" ,"CMP.B" ,
//B0-B7
	"SUBX"  ,"SUBX"  ,"SUBX"  ,"SUBX"  ,"SUBX"  ,"SUBX"  ,"SUBX"  ,"SUBX"  ,
//B8-BF
	"SUBX"  ,"SUBX"  ,"SUBX"  ,"SUBX"  ,"SUBX"  ,"SUBX"  ,"SUBX"  ,"SUBX"  ,
//C0-C7
	"OR.B"  ,"OR.B"  ,"OR.B"  ,"OR.B"  ,"OR.B"  ,"OR.B"  ,"OR.B"  ,"OR.B"  ,
//C8-CF
	"OR.B"  ,"OR.B"  ,"OR.B"  ,"OR.B"  ,"OR.B"  ,"OR.B"  ,"OR.B"  ,"OR.B"  ,
//D0-D7
	"XOR.B" ,"XOR.B" ,"XOR.B" ,"XOR.B" ,"XOR.B" ,"XOR.B" ,"XOR.B" ,"XOR.B" ,
//D8-DF
	"XOR.B" ,"XOR.B" ,"XOR.B" ,"XOR.B" ,"XOR.B" ,"XOR.B" ,"XOR.B" ,"XOR.B" ,
//E0-E7
	"AND.B" ,"AND.B" ,"AND.B" ,"AND.B" ,"AND.B" ,"AND.B" ,"AND.B" ,"AND.B" ,
//E8-EF
	"AND.B" ,"AND.B" ,"AND.B" ,"AND.B" ,"AND.B" ,"AND.B" ,"AND.B" ,"AND.B" ,
//F0-F7
	"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,
//F8-FF
	"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B" ,"MOV.B"
};

static char *onamH8_7A[] = {
	"MOV.L", "ADD.L", "CMP.L", "SUB.L", "OR.L", "XOR.L", "AND.L", ""
};

static char *onamH8_79[] = {
	"MOV.W", "ADD.W", "CMP.W", "SUB.W", "OR.W", "XOR.W", "AND.W", ""
};

static char *onamH8_01[] = {
	"MOV.L", "MOV.L", "LDC.W", "STC.W", "POP.L", "PUSH.L"
};

static char *onamH8_01CD[] = {
	"MULXS.B", "MULXS.W", "DIVXS.B", "DIVXS.W", "OR.L", "XOR.L", "AND.L"
};

short flag32=0;

static void dH8init(void)
{
	opcsp = 19;
	argsp = 8;
	cmtsp = 24;
	init = TRUE;
}

static void putH8reg32(short x)
{
	switch (x & 0x07)
	{
		case 0: putreg("ER0"); break;
		case 1: putreg("ER1"); break;
		case 2: putreg("ER2"); break;
		case 3: putreg("ER3"); break;
		case 4: putreg("ER4"); break;
		case 5: putreg("ER5"); break;
		case 6: putreg("ER6"); break;
		case 7: putreg("ER7"); break;
	}
}

static void putH8reg16(short x)
{
	switch (x & 0x0F)
	{
		case  0: putreg("R0"); break;
		case  1: putreg("R1"); break;
		case  2: putreg("R2"); break;
		case  3: putreg("R3"); break;
		case  4: putreg("R4"); break;
		case  5: putreg("R5"); break;
		case  6: putreg("R6"); break;
		case  7: putreg("R7"); break;
		case  8: putreg("E0"); break;
		case  9: putreg("E1"); break;
		case 10: putreg("E2"); break;
		case 11: putreg("E3"); break;
		case 12: putreg("E4"); break;
		case 13: putreg("E5"); break;
		case 14: putreg("E6"); break;
		case 15: putreg("E7"); break;
	}
}

static void putH8reg(short x)
{
	switch (x & 0x0F)
	{
		case  0: putreg("R0H"); break;
		case  1: putreg("R1H"); break;
		case  2: putreg("R2H"); break;
		case  3: putreg("R3H"); break;
		case  4: putreg("R4H"); break;
		case  5: putreg("R5H"); break;
		case  6: putreg("R6H"); break;
		case  7: putreg("R7H"); break;
		case  8: putreg("R0L"); break;
		case  9: putreg("R1L"); break;
		case 10: putreg("R2L"); break;
		case 11: putreg("R3L"); break;
		case 12: putreg("R4L"); break;
		case 13: putreg("R5L"); break;
		case 14: putreg("R6L"); break;
		case 15: putreg("R7L"); break;
	}
}

static void putH8regind(short n)
{
	if (flag32)
		putH8reg32(n);
	else
		putH8reg16(n);
}

static void inval2(short a, short b, short flag)
{
	if (flag)
		data2(a, b);
	putopc(".DB");
	puthexbyte(a);
	putcomma();
	puthexbyte(b);
	enddata2(a, b);
}

static void inval4(short a, short b, short c, short d, short flag)
{
	if (flag)
		data4(a, b, c, d);
	putopc(".DB");
	puthexbyte(a);
	putcomma();
	puthexbyte(b);
	putcomma();
	puthexbyte(c);
	putcomma();
	puthexbyte(d);
	enddata4(a, b, c, d);
}

static void inval6(short a, short b, short c, short d, short e,
	short f, short flag)
{
	if (flag)
		data6(a, b, c, d, e, f);
	putopc(".DB");
	puthexbyte(a);
	putcomma();
	puthexbyte(b);
	putcomma();
	puthexbyte(c);
	putcomma();
	puthexbyte(d);
	putcomma();
	puthexbyte(e);
	putcomma();
	puthexbyte(f);
	enddata6(a, b, c, d, e, f);
}

static void extra2(short a, short b)
{
	putpc();
	putsp(5);
	data2(a, b);
	putopc(" ");
	spcnt += 4;
	enddata2(a, b);
}

static void extra4(short a, short b, short c, short d)
{
	putpc();
	putsp(5);
	data4(a, b, c, d);
	putopc(" ");
	spcnt += 4;
	enddata4(a, b, c, d);
}

static void putopc01(short y, short a, short b)
{
	short idx = 0;

	if (y == 0x00 && !(b & 0x80))
		idx = 0;
	if (y == 0x00 && (b & 0x80))
		idx = 1;
	if (y == 0x40 && !(b & 0x80))
		idx = 2;
	if (y == 0x40 && (b & 0x80))
		idx = 3;
	if (y == 0x00 && a == 0x6D && ((b & 0xF0) == 0x70))
		idx = 4;
	if (y == 0x00 && a == 0x6D && ((b & 0xF0) == 0xF0))
		idx = 5;
	putopc(onamH8_01[idx]);
}

static void putreg01(short y, short b)
{
	if (y == 0x40)
		putreg("CCR");
	else
		putH8reg32(b);
}

static void d2_h80169(short x, short y, short a, short b)
{
	data4(x, y, a, b);
	putopc01(y, a, b);
	if (b & 0x80)
	{
		putreg01(y, b);
		putcomma();
		putat();
		putH8reg32(b >> 4);
	}
	else
	{
		putat();
		putH8reg32(b >> 4);
		putcomma();
		putreg01(y, b);
	}
	enddata4(x, y, a, b);
}

static void d2_h8016B(short x, short y, short a, short b)
{
	short c, d, e, f;

	c = getnxt();
	d = getnxt();
	data6(x, y, a, b, c, d);
	putopc01(y, a, b);
	if (b & 0x20)
	{
		e = getnxt();
		f = getnxt();
		if (b & 0x80)
		{
			putreg01(y, b);
			putcomma();
			putat();
			putadr4(c, d, e, f);
		}
		else
		{
			putat();
			putadr4(c, d, e, f);
			putcomma();
			putreg01(y, b);
		}
		enddata6(x, y, a, b, c, d);
		extra2(e, f);
	}
	else
	{
		if (b & 0x80)
		{
			putreg01(y, b);
			putcomma();
			putat();
			putadr2(c, d);
		}
		else
		{
			putat();
			putadr2(c, d);
			putcomma();
			putreg01(y, b);
		}
		enddata6(x, y, a, b, c, d);
	}
}

static void d2_h8016D(short x, short y, short a, short b)
{
	data4(x, y, a, b);
	putopc01(y, a, b);
	if ((b & 0x70) == 0x70)
		putH8reg32(b);
	else if (b & 0x80)
	{
		putreg01(y, b);
		outs(",@-");
		putH8reg32(b >> 4);
	}
	else
	{
		putat();
		putH8reg32(b >> 4);
		outs("+,");
		putreg01(y, b);
	}
	enddata4(x, y, a, b);
}

static void d2_h8016F(short x, short y, short a, short b)
{
	short c, d;

	c = getnxt();
	d = getnxt();
	data6(x, y, a, b, c, d);
	putopc01(y, a, b);
	if (b & 0x80)
	{
		putreg01(y, b);
		putcomma();
		putat();
		putopn();
		putadr2(c, d);
		putcomma();
		putH8reg32(b >> 4);
		putclo();
	}
	else
	{
		putat();
		putopn();
		putadr2(c, d);
		putcomma();
		putH8reg32(b >> 4);
		putclo();
		putcomma();
		putreg01(y, b);
	}
	enddata6(x, y, a, b, c, d);
}

static void d2_h80178(short x, short y, short a, short b)
{
	short c, d, e, f, g, h;

	c = getnxt();
	d = getnxt();
	e = getnxt();
	f = getnxt();
	g = getnxt();
	h = getnxt();
	data6(x, y, a, b, c, d);
	putopc01(y, a, b);
	if (d & 0x80)
	{
		putreg01(y, d);
		putcomma();
		putat();
		putopn();
		putadr4(e, f, g, h);
		putcomma();
		putH8reg32(b);
		putclo();
	}
	else
	{
		putat();
		putopn();
		putadr4(e, f, g, h);
		putcomma();
		putH8reg32(b);
		putclo();
		putcomma();
		putreg01(y, d);
	}
	enddata6(x, y, a, b, c, d);
	extra4(e, f, g, h);
}

static void d2_h801CD(short x, short y)
{
	short a, b, h;

	if (!flag32)
	{
		inval2(x, y, 1);
		return;
	}
	a = getnxt();
	b = getnxt();
	h = 0;
	if (y == 0xC0 && a == 0x50)
		h = 1;
	if (y == 0xC0 && a == 0x52)
		h = 2;
	if (y == 0xD0 && a == 0x51)
		h = 3;
	if (y == 0xD0 && a == 0x53)
		h = 4;
	if (y == 0xF0 && a == 0x64)
		h = 5;
	if (y == 0xF0 && a == 0x65)
		h = 6;
	if (y == 0xF0 && a == 0x66)
		h = 7;
	if (h == 0)
	{
		inval4(x, y, a, b, 1);
		return;
	}
	data4(x, y, a, b);
	putopc(onamH8_01CD[h-1]);
	switch (h)
	{
		case 1:
		case 3:
			putH8reg(b >> 4);
			putcomma();
			putH8reg16(b);
			break;
		case 2:
		case 4:
			putH8reg16(b >> 4);
			putcomma();
			putH8reg32(b);
			break;
		case 5:
		case 6:
		case 7:
			putH8reg32(b >> 4);
			putcomma();
			putH8reg32(b);
			break;
	}
	enddata4(x, y, a, b);
}

static void d2_h801(short x, short y)
{
	short a, b;

	if (y == 0x00 || y == 0x40)
	{
		if (!flag32)
		{
			inval2(x, y, 1);
			return;
		}
		a = getnxt();
		b = getnxt();
		if (a == 0x69)
			d2_h80169(x, y, a, b);
		else if (a == 0x6B)
			d2_h8016B(x, y, a, b);
		else if (a == 0x6D)
			d2_h8016D(x, y, a, b);
		else if (a == 0x6F)
			d2_h8016F(x, y, a, b);
		else if (a == 0x78)
			d2_h80178(x, y, a, b);
	}
	else if (y == 0x80)
	{
		data2(x, y);
		putopc(onamH8[x]);
		enddata2(x, y);
	}
	else if (y == 0xC0 || y == 0xD0 || y == 0xF0)
		d2_h801CD(x, y);
	else
		inval2(x, y, 1);
}

static void d2_H8(short x, short y)
{
	ADDRESS adr;
	char opcode[16];

	if (x == 0x01)
	{
		d2_h801(x, y);
		return;
	}
	data2(x, y);
	switch (ofmt)
	{
		// 20 - opc
		case 0:
			if (x == 0x00 && y != 0x00)
			{
				inval2(x, y, 0);
				return;
			}
			if (x == 0x54 && y != 0x70)
			{
				inval2(x, y, 0);
				return;
			}
			if (x == 0x56 && y != 0x70)
			{
				inval2(x, y, 0);
				return;
			}
			putopc(onamH8[x]);
			break;

		// 21 - opc #$nn,CCR
		case 1:
			putopc(onamH8[x]);
			putimm(y);
			putcomma();
			putreg("CCR");
			break;

		// 22 - opc #$nn,Rr
		case 2:
			putopc(onamH8[x]);
			putimm(y);
			putcomma();
			putH8reg(x);
			break;

		// 23 - opc rel
		case 3:
			putopc(onamH8[x]);
			if (y > 0x80)
				adr = (pc + 2) - (0x100 - y);
			else
				adr = (pc + 2) + y;
			if (flag32)
				putladdr(adr);
			else
				putaddr(adr);
			break;

		// 24 - opc Rr
		case 4:
			if (y & 0x80)
			{
				if (x == 0x0A || x == 0x0F || x == 0x1A || x == 0x1F)
				{
					if (!flag32)
					{
						inval2(x, y, 0);
						return;
					}
					putopc(onamH8hi[x]);
					goto case5;
				}
				strcpy(opcode, onamH8hi[x]);
			}
			else
				strcpy(opcode, onamH8[x]);
			if (x == 0x10 || x == 0x11 || x == 0x12 || x == 0x13 || x == 0x17)
			{
				if (x == 0x17 && (y & 0x40))
				{
					if (y & 0x80)
						strcpy(opcode, "EXTS");
					else
						strcpy(opcode, "EXTU");
				}
				if ((y & 0x30) == 0x30)
				{
					strcat(opcode, ".L");
					putopc(opcode);
					putH8reg32(y);
				}
				else if (y & 0x10)
				{
					strcat(opcode, ".W");
					putopc(opcode);
					putH8reg16(y);
				}
				else
				{
					strcat(opcode, ".B");
					putopc(opcode);
					putH8reg(y);
				}
			}
			else
			{
				putopc(opcode);
				if (x == 0x0F || x == 0x1F)
					putH8reg16(y);
				else
					putH8reg(y);
			}
			break;

		// 25 - opc Rr,Rr
		case 5:
			if (y & 0x80)
				putopc(onamH8hi[x]);
			else
				putopc(onamH8[x]);
case5:
			switch (x)
			{
				case 0x08:
				case 0x0C:
				case 0x14:
				case 0x15:
				case 0x16:
				case 0x18:
				case 0x1C:
				case 0x50:
				case 0x51:
					putH8reg(y >> 4);
					break;
				case 0x09:
				case 0x0D:
				case 0x0E:
				case 0x19:
				case 0x1D:
				case 0x1E:
				case 0x52:
				case 0x53:
				case 0x64:
				case 0x65:
				case 0x66:
					putH8reg16(y >> 4);
					break;
				case 0x0A:
				case 0x0F:
				case 0x1A:
				case 0x1F:
					putH8reg32(y >> 4);
					break;
			}
			putcomma();
			switch (x)
			{
				case 0x08:
				case 0x0C:
				case 0x14:
				case 0x15:
				case 0x16:
				case 0x18:
				case 0x1C:
					putH8reg(y & 0x0F);
					break;
				case 0x09:
				case 0x0D:
				case 0x0E:
				case 0x19:
				case 0x1D:
				case 0x1E:
				case 0x50:
				case 0x51:
				case 0x64:
				case 0x65:
				case 0x66:
					putH8reg16(y & 0x0F);
					break;
				case 0x0A:
				case 0x0F:
				case 0x1A:
				case 0x1F:
				case 0x52:
				case 0x53:
					putH8reg32(y & 0x0F);
					break;
			}
			break;

		// 26 - opc RR,RR
		case 6:
			putopc(onamH8[x]);
			putH8reg16(y);
			putcomma();
			putH8reg16(y);
			break;

		// 27 - opc @Rr
		case 7:
			putopc(onamH8[x]);
			putat();
			putH8regind(y);
			break;

		// 28 - opc @aa
		case 8:
			putopc(onamH8[x]);
			putat();
			putadr1(y);
			break;

		// 29 - opc #$nn,Rr
		case 9:
			if (y & 0x80)
				putopc(onamH8hi[x]);
			else
				putopc(onamH8[x]);
			putnum((y >> 4) & 0x07);
			putcomma();
			putH8reg(y);
			break;

		// 2A - opc @RR+,Rr -or- opc Rr,@-RR
		case 10:
			putopc(onamH8[x]);
			if (y & 0x80)
			{
				putH8reg(y);
				outs(",@-");
				putH8regind(y >> 4);
			}
			else
			{
				putat();
				putH8regind(y >> 4);
				outs("+,");
				putH8reg(y);
			}
			break;

		// 2B - opc @RR+,RR, etc.
		case 11:
			if ((x == 0x6D) && ((y & 0xF0) == 0x70))
			{
				putopc("POP.W");
				putH8reg16(y);
			}
			else if ((x == 0x6D) && ((y & 0xF0) == 0xF0))
			{
				putopc("PUSH.W");
				putH8reg16(y);
			}
			else if (y & 0x80)
			{
				putopc(onamH8[x]);
				putH8reg16(y);
				outs(",@-");
				putH8regind(y >> 4);
			}
			else
			{
				putopc(onamH8[x]);
				putat();
				putH8regind(y >> 4);
				outs("+,");
				putH8reg16(y);
			}
			break;

		// 2C - opc #x -or- opc #x,RR
		case 12:
			if (x == 0x57)
			{
				putopc(onamH8[x]);
				putpound();
				putnum(y >> 4);
			}
			else
			{
				if (y & 0x40)
				{
					strcpy(opcode, onamH8hi[x]);
					if (y & 0x20)
						strcat(opcode, ".L");
					else
						strcat(opcode, ".W");
				}
				else
					strcpy(opcode, onamH8[x]);
				putopc(opcode);
				if ((y & 0x90) == 0x90)
					outs("#4");
				else if (y & 0x80)
					outs("#2");
				else
					outs("#1");
				putcomma();
				if (y & 0x40)
				{
					if (y & 0x20)
						putH8reg32(y);
					else
						putH8reg16(y);
				}
				else
					putH8regind(y);
			}
			break;

		// 2D - opc Rr,@aa -or- opc @aa,Rr
		case 13:
			putopc(onamH8[x]);
			if (x & 0x10)
			{
				putH8reg(x);
				putcomma();
				putat();
				putadr1(y);
			}
			else
			{
				putat();
				putadr1(y);
				putcomma();
				putH8reg(x);
			}
			break;

		// 2E - misc bit ops
		case 14:
			if (y & 0x80)
				putopc(onamH8hi[x]);
			else
				putopc(onamH8[x]);
			if (x < 0x64)
			{							// opc Rn,Rr
				putH8reg(y >> 4);
				putcomma();
				putH8reg(y);
			}
			else if (x < 0x68)
			{							// opc #$nn,Rr
				putnum((y >> 4) & 0x07);
				putcomma();
				putH8reg(y);
			}
			else if (y & 0x80)
			{							// opc Rr,@RR
				if (x & 0x01)
					putH8reg16(y);
				else
					putH8reg(y);
				putcomma();
				putat();
				putH8regind(y >> 4);
			}
			else
			{							// opc @RR,Rr
				putat();
				putH8regind(y >> 4);
				putcomma();
				if (x & 0x01)
					putH8reg16(y);
				else
					putH8reg(y);
			}
			break;

		// 2F - opc Rr,CCR -or- opc CCR,Rr
		case 15:
			putopc(onamH8[x]);
			if (x & 0x01)
			{
				putH8reg(y);
				putcomma();
				putreg("CCR");
			}
			else
			{
				putreg("CCR");
				putcomma();
				putH8reg(y);
			}
			break;
	}
	enddata2(x, y);
	if ((x == 0x54) || (x == 0x56))	// RTS & RTE
		putcr();
}

static void d4_H8(short x, short y, short a, short b)
{
	ADDRESS adr;

	if ((x == 0x6B || x == 0x6A) && (y & 0x20))
	{
		short c, d;
		extern void d6_H8(short x, short y, short a, short b, short c, short d);

		c = getnxt();
		d = getnxt();
		if (!flag32)
			inval6(x, y, a, b, c, d, 1);
		else
		{
			ofmt = 5;
			d6_H8(x, y, a, b, c, d);
		}
		return;
	}
	data4(x, y, a, b);
	switch (ofmt)
	{
		// 40 - opc
		case 0:
			if (x==0x7B && y==0x5C && a==0x59 && b==0x8F)
				putopc("EEPMOV.B");
			else if (x==0x7B && y==0xD4 && a==0x59 && b==0x8F)
				putopc("EEPMOV.W");
			else
			{
				inval4(x, y, a, b, 0);
				return;
			}
			break;

		// 41 - opc aaaa
		case 1:
			putopc(onamH8[x]);
			putadr3(y, a, b);
			break;

		// 42 - opc Rr,@aaaa -or- opc @aaaa,Rr
		case 2:
			if (x != 0x6B && x != 0x6A)
			{
				inval4(x, y, a, b, 0);
				return;
			}
			if ((x == 0x6A) && ((y & 0xF0) == 0x40))
				putopc("MOVFPE");
			else if ((x == 0x6A) && ((y & 0xF0) == 0xC0))
				putopc("MOVTPE");
			else
				putopc(onamH8[x]);
			if (y & 0x80)
			{
				if (x == 0x6B)
					putH8reg16(y);
				else
					putH8reg(y);
				putcomma();
				putat();
				putadr2(a, b);
			}
			else
			{
				putat();
				putadr2(a, b);
				putcomma();
				if (x == 0x6B)
					putH8reg16(y);
				else
					putH8reg(y);
			}
			break;

		// 43 - opc Rr,@(aaaa,RR) -or- opc @(aaaa,RR),Rr
		case 3:
			if (x != 0x6E && x != 0x6F)
			{
				inval4(x, y, a, b, 0);
				return;
			}
			putopc(onamH8[x]);
			if (y & 0x80)
			{
				if (x == 0x6F)
					putH8reg16(y);
				else
					putH8reg(y);
				putcomma();
				putat();
				putopn();
				putadr2(a, b);
				putcomma();
				putH8regind(y >> 4);
				putclo();
			}
			else
			{
				putat();
				putopn();
				putadr2(a, b);
				putcomma();
				putH8regind(y >> 4);
				putclo();
				putcomma();
				if (x == 0x6F)
					putH8reg16(y);
				else
					putH8reg(y);
			}
			break;

		// 44 - opc #$nnnn,RR
		case 4:
			putopc(onamH8[x]);
			putimm4(a, b);
			putcomma();
			putH8reg16(y);
			break;

		// 45 - misc bitops
		case 5:
			if (x != 0x7C && x != 0x7D && x != 0x7E && x != 0x7F)
			{
				inval4(x, y, a, b, 0);
				return;
			}
			if (b & 0x80)
				putopc(onamH8hi[a]);
			else
				putopc(onamH8[a]);
			if (x == 0x7C || x == 0x7D)
			{
				if (a < 0x64) // opc Rn,@Rr
					putH8reg(b >> 4);
				else // opc n,@Rr
					putnum((b >> 4) & 0x07);
				putcomma();
				putat();
				putH8regind(y);
			}
			else
			{
				if (a < 0x64) // opc Rn,@aa
					putH8reg(b >> 4);
				else // opc n,@Rr
					putnum((b >> 4) & 0x07);
				putcomma();
				putat();
				putadr1(y);
			}
			break;

		// 46 - opc rel16
		case 6:
			if (!flag32)
			{
				inval4(x, y, a, b, 0);
				return;
			}
			if (x == 0x58)
				putopc(onamH8[0x40 + (y >> 4)]);
			else
				putopc(onamH8[x]);
			adr = (a * 256) + b;
			putladdr((pc + 4) + adr);
			break;

		// 47 - opc #$nnnn,Rr
		case 7:
			if (!flag32)
			{
				inval4(x, y, a, b, 0);
				return;
			}
			putopc(onamH8_79[(y >> 4) & 7]);
			putimm4(a, b);
			putcomma();
			putH8reg16(y);
	}
	enddata4(x, y, a, b);
}

static void d6_H8(short x, short y, short a, short b, short c, short d)
{
	if (!flag32)
	{
		inval6(x, y, a, b, c, d, 1);
		return;
	}
	data6(x, y, a, b, c, d);
	switch (ofmt)
	{
		// 65 - opc @$nnnnnn,Rr -or- opc Rr,@$nnnnnn
		case 5:
			putopc(onamH8[x]);
			if (y & 0x80)
			{
				if (x == 0x6B)
					putH8reg16(y);
				else
					putH8reg(y);
				putcomma();
				putat();
				putadr4(a, b, c, d);
			}
			else
			{
				putat();
				putadr4(a, b, c, d);
				putcomma();
				if (x == 0x6B)
					putH8reg16(y);
				else
					putH8reg(y);
			}
			break;

		// 67 - opc #$nnnnnnnn,Rr
		case 7:
			putopc(onamH8_7A[(y >> 4) & 7]);
			putimm8(a, b, c, d);
			putcomma();
			putH8reg32(y);
	}
	enddata6(x, y, a, b, c, d);
}

static void d8_H8(short x, short y, short a, short b, short c,
	short d, short e, short f)
{
	if (!flag32)
	{
		inval4(x, y, a, b, 1);
		putpc();
		putsp(1);
		inval4(c, d, e, f, 1);
		return;
	}
	data6(x, y, a, b, c, d);
	switch (ofmt)
	{
		// 87 - opc @($nnnnnn,Rr),Rr -or- opc Rr,@($nnnnnn,Rr)
		case 7:
			putopc(onamH8[a]);
			if (b & 0x80)
			{
				if (a == 0x6B)
					putH8reg16(b);
				else
					putH8reg(b);
				putcomma();
				putat();
				putopn();
				putadr4(c, d, e, f);
				putcomma();
				putH8reg32(y);
				putclo();
			}
			else
			{
				putat();
				putopn();
				putadr4(c, d, e, f);
				putcomma();
				putH8reg32(y);
				putclo();
				putcomma();
				if (a == 0x6B)
					putH8reg16(b);
				else
					putH8reg(b);
			}
	}
	enddata6(x, y, a, b, c, d);
	extra2(e, f);
}

void dsmH8(short n)
{
	if (submach == X_H8_300H)
		flag32 = 1;
	else
		flag32 = 0;
	if (!init)
		dH8init();
	if (pc & 1)
	{
		inval(n);
		return;
	}
	if (!otypH8[n])
	{
		short x;

		x = getnxt();
		inval2(n, x, 1);
		return;
	}
#if DEBUG
	printf("op=%X pval=%X\n",n,otypH8[n]);
#endif
	omod = otypH8[n] / 16;
	ofmt = otypH8[n] % 16;
	if (omod == 2)
	{
		short x;

		x = getnxt();
		d2_H8(n,x);
	}
	else if (omod == 4)
	{
		short x, y, z;

		x = getnxt();
		y = getnxt();
		z = getnxt();
		d4_H8(n, x, y, z);
	}
	else if (omod == 6)
	{
		short x, y, z, a, b;

		x = getnxt();
		y = getnxt();
		z = getnxt();
		a = getnxt();
		b = getnxt();
		d6_H8(n, x, y, z, a, b);
	}
	else if (omod == 7)
	{
		short x, y, z, a, b, c, d;

		x = getnxt();
		y = getnxt();
		z = getnxt();
		a = getnxt();
		b = getnxt();
		c = getnxt();
		d = getnxt();
		d8_H8(n, x, y, z, a, b, c, d);
	}
}

