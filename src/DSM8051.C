// dsm8051.c - module to handle 8051 codes for DSM
// copyright (c) 1994, Freedlight Software

#include "dsm.h"

static char otyp8051[] = {
	0x10,0x20,0x30,0x11,0x11,0x21,0x14,0x14,	//00-07
	0x13,0x13,0x13,0x13,0x13,0x13,0x13,0x13,	//08-0F
	0x32,0x20,0x30,0x11,0x11,0x21,0x14,0x14,	//10-17
	0x13,0x13,0x13,0x13,0x13,0x13,0x13,0x13,	//18-1F
	0x32,0x20,0x10,0x11,0x22,0x25,0x16,0x16,	//20-27
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,	//28-2F
	0x32,0x20,0x10,0x11,0x22,0x25,0x16,0x16,	//30-37
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,	//38-3F
	0x2D,0x20,0x28,0x31,0x22,0x25,0x16,0x16,	//40-47
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,	//48-4F
	0x2D,0x20,0x28,0x31,0x22,0x25,0x16,0x16,	//50-57
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,	//58-5F
	0x2D,0x20,0x28,0x31,0x22,0x25,0x16,0x16,	//60-67
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,	//68-6F
	0x2D,0x20,0x2E,0x1A,0x22,0x31,0x24,0x24,	//70-77
	0x23,0x23,0x23,0x23,0x23,0x23,0x23,0x23,	//78-7F
	0x2D,0x20,0x2E,0x1A,0x19,0x34,0x2A,0x2A,	//80-87
	0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,	//88-8F
	0x35,0x20,0x2F,0x1A,0x22,0x25,0x16,0x16,	//90-97
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,	//98-9F
	0x2E,0x20,0x2E,0x1A,0x19,0x00,0x27,0x27,	//A0-A7
	0x26,0x26,0x26,0x26,0x26,0x26,0x26,0x26,	//A8-AF
	0x2E,0x20,0x2B,0x12,0x36,0x37,0x39,0x39,	//B0-B7
	0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,	//B8-BF
	0x21,0x20,0x2B,0x12,0x11,0x25,0x16,0x16,	//C0-C7
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,	//C8-CF
	0x21,0x20,0x2B,0x12,0x11,0x33,0x16,0x16,	//D0-D7
	0x2C,0x2C,0x2C,0x2C,0x2C,0x2C,0x2C,0x2C,	//D8-DF
	0x1A,0x20,0x16,0x16,0x11,0x25,0x16,0x16,	//E0-E7
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,	//E8-EF
	0x1A,0x20,0x18,0x18,0x11,0x28,0x18,0x18,	//F0-F7
	0x17,0x17,0x17,0x17,0x17,0x17,0x17,0x17 	//F8-FF
};

static char *onam8051[] = {
	"NOP"  ,"AJMP" ,"LJMP" ,"RR"   ,"INC"  ,"INC"  ,"INC"  ,"INC"  , //00-07
	"INC"  ,"INC"  ,"INC"  ,"INC"  ,"INC"  ,"INC"  ,"INC"  ,"INC"  , //08-0F
	"JBC"  ,"ACALL","LCALL","RRC"  ,"DEC"  ,"DEC"  ,"DEC"  ,"DEC"  , //10-17
	"DEC"  ,"DEC"  ,"DEC"  ,"DEC"  ,"DEC"  ,"DEC"  ,"DEC"  ,"DEC"  , //18-1F
	"JB"   ,"AJMP" ,"RET"  ,"RL"   ,"ADD"  ,"ADD"  ,"ADD"  ,"ADD"  , //20-27
	"ADD"  ,"ADD"  ,"ADD"  ,"ADD"  ,"ADD"  ,"ADD"  ,"ADD"  ,"ADD"  , //28-2F
	"JNB"  ,"ACALL","RETI" ,"RLC"  ,"ADDC" ,"ADDC" ,"ADDC" ,"ADDC" , //30-37
	"ADDC" ,"ADDC" ,"ADDC" ,"ADDC" ,"ADDC" ,"ADDC" ,"ADDC" ,"ADDC" , //38-3F
	"JC"   ,"AJMP" ,"ORL"  ,"ORL"  ,"ORL"  ,"ORL"  ,"ORL"  ,"ORL"  , //40-47
	"ORL"  ,"ORL"  ,"ORL"  ,"ORL"  ,"ORL"  ,"ORL"  ,"ORL"  ,"ORL"  , //48-4F
	"JNC"  ,"ACALL","ANL"  ,"ANL"  ,"ANL"  ,"ANL"  ,"ANL"  ,"ANL"  , //50-57
	"ANL"  ,"ANL"  ,"ANL"  ,"ANL"  ,"ANL"  ,"ANL"  ,"ANL"  ,"ANL"  , //58-5F
	"JZ"   ,"AJMP" ,"XRL"  ,"XRL"  ,"XRL"  ,"XRL"  ,"XRL"  ,"XRL"  , //60-67
	"XRL"  ,"XRL"  ,"XRL"  ,"XRL"  ,"XRL"  ,"XRL"  ,"XRL"  ,"XRL"  , //68-6F
	"JNZ"  ,"ACALL","ORL"  ,"JMP"  ,"MOV"  ,"MOV"  ,"MOV"  ,"MOV"  , //70-77
	"MOV"  ,"MOV"  ,"MOV"  ,"MOV"  ,"MOV"  ,"MOV"  ,"MOV"  ,"MOV"  , //78-7F
	"SJMP" ,"AJMP" ,"ANL"  ,"MOVC" ,"DIV"  ,"MOV"  ,"MOV"  ,"MOV"  , //80-87
	"MOV"  ,"MOV"  ,"MOV"  ,"MOV"  ,"MOV"  ,"MOV"  ,"MOV"  ,"MOV"  , //88-8F
	"MOV"  ,"ACALL","MOV"  ,"MOVC" ,"SUBB" ,"SUBB" ,"SUBB" ,"SUBB" , //90-97
	"SUBB" ,"SUBB" ,"SUBB" ,"SUBB" ,"SUBB" ,"SUBB" ,"SUBB" ,"SUBB" , //98-9F
	"ORL"  ,"AJMP" ,"MOV"  ,"INC"  ,"MUL"  ,""     ,"MOV"  ,"MOV"  , //A0-A7
	"MOV"  ,"MOV"  ,"MOV"  ,"MOV"  ,"MOV"  ,"MOV"  ,"MOV"  ,"MOV"  , //A8-AF
	"ANL"  ,"ACALL","CPL"  ,"CPL"  ,"CJNE" ,"CJNE" ,"CJNE" ,"CJNE" , //B0-B7
	"CJNE" ,"CJNE" ,"CJNE" ,"CJNE" ,"CJNE" ,"CJNE" ,"CJNE" ,"CJNE" , //B8-BF
	"PUSH" ,"AJMP" ,"CLR"  ,"CLR"  ,"SWAP" ,"XCH"  ,"XCH"  ,"XCH"  , //C0-C7
	"XCH"  ,"XCH"  ,"XCH"  ,"XCH"  ,"XCH"  ,"XCH"  ,"XCH"  ,"XCH"  , //C8-CF
	"POP"  ,"ACALL","SETB" ,"SETB" ,"DA"   ,"DJNZ" ,"XCHD" ,"XCHD" , //D0-D7
	"DJNZ" ,"DJNZ" ,"DJNZ" ,"DJNZ" ,"DJNZ" ,"DJNZ" ,"DJNZ" ,"DJNZ" , //D8-DF
	"MOVX" ,"AJMP" ,"MOVX" ,"MOVX" ,"CLR"  ,"MOV"  ,"MOV"  ,"MOV"  , //E0-E7
	"MOV"  ,"MOV"  ,"MOV"  ,"MOV"  ,"MOV"  ,"MOV"  ,"MOV"  ,"MOV"  , //E8-EF
	"MOVX" ,"ACALL","MOVX" ,"MOVX" ,"CPL"  ,"MOV"  ,"MOV"  ,"MOV"  , //F0-F7
	"MOV"  ,"MOV"  ,"MOV"  ,"MOV"  ,"MOV"  ,"MOV"  ,"MOV"  ,"MOV"    //F8-FF
};

static void d8051init(void)
{
	opcsp = 10;
	argsp = 6;
	cmtsp = 15;
	init = TRUE;
}

static void put8051reg(short x)
{
	switch (x & 0x07)
	{
		case 0: putreg("R0"); break;
		case 1: putreg("R1"); break;
		case 2: putreg("R2"); break;
		case 3: putreg("R3"); break;
		case 4: putreg("R4"); break;
		case 5: putreg("R5"); break;
		case 6: putreg("R6"); break;
		case 7: putreg("R7"); break;
	}
}

static void put8051ireg(short x)
{
	putat();
	if ((x & 1) == 1)
		putreg("R1");
	else
		putreg("R0");
}

static void putbitadr(short n)
{
	short bit, adr;

	if (n < 0x80)
	{
		bit = n & 7;
		adr = (n >> 3) + 0x20;
	}
	else
	{
		bit = n & 7;
		adr = n & 0xF8;
	}
	putdoll();
	putbyte(adr);
	outc('.');
	outc(bit + '0');
}

static void put8adr(short n, short offs)
{
	unsigned adr;

	if (n > 0x80)
		adr = (pc + offs) - (0x100 - n);
	else
		adr = (pc + offs) + n;
	putaddr(adr);
}

static void put12adr(short op, short n)
{
	short hib = (op & 0xE0) << 3;
	unsigned adr = (pc & 0xF800) + n + hib;

	putaddr(adr);
}

static void d1_8051(short x)
{
	data1(x);
	putopc(onam8051[x]);
	switch (ofmt)
	{
		case 0:		// opr
			break;
		case 1:		// opr A
			putreg("A");
			break;
		case 2:		// opr C
			putreg("C");
			break;
		case 3:		// opr Rn
			put8051reg(x);
			break;
		case 4:		// opr @Rn
			put8051ireg(x);
			break;
		case 5:		// opr A,Rn
			putreg("A");
			putcomma();
			put8051reg(x);
			break;
		case 6:		// opr A,@Rn
			putreg("A");
			putcomma();
			put8051ireg(x);
			break;
		case 7:		// opr Rn,A
			put8051reg(x);
			putcomma();
			putreg("A");
			break;
		case 8:		// opr @Rn,A
			put8051ireg(x);
			putcomma();
			putreg("A");
			break;
		case 9:		// opr AB
			putreg("AB");
			break;
		case 10:		// special
			switch (x)
			{
				case 0x73: putarg("@A+DPTR"); break;
				case 0x83: putarg("A,@A+PC"); break;
				case 0x93: putarg("A,@A+DPTR"); break;
				case 0xA3: putarg("DPTR"); break;
				case 0xE0: putarg("A,@DPTR"); break;
				case 0xF0: putarg("@DPTR,A"); break;
			}
			break;
	}
	enddata1(x);
	if ((x == 0x22) || (x == 0x32))	// RET, RETI
		putcr();
}

static void d2_8051(short x, short y)
{
	data2(x, y);
	putopc(onam8051[x]);
	switch (ofmt)
	{
		case 0:		// 12-bit code
			put12adr(x,y);
			break;
		case 1:		// $nn
			putadr1(y);
			break;
		case 2:		// A,#$nn
			putreg("A");
			putcomma();
			putimm(y);
			break;
		case 3:		// Rn,#$nn
			put8051reg(x);
			putcomma();
			putimm(y);
			break;
		case 4:		// @Rn,#$nn
			put8051ireg(x);
			putcomma();
			putimm(y);
			break;
		case 5:		// A,$nn
			putreg("A");
			putcomma();
			putadr1(y);
			break;
		case 6:		// Rn,$nn
			put8051reg(x);
			putcomma();
			putadr1(y);
			break;
		case 7:		// @Rn,$nn
			put8051ireg(x);
			putcomma();
			putadr1(y);
			break;
		case 8:		// $nn,A
			putadr1(y);
			putcomma();
			putreg("A");
			break;
		case 9:		// $nn,Rn
			putadr1(y);
			putcomma();
			put8051reg(x);
			break;
		case 10:		// $nn,@Rn
			putadr1(y);
			putcomma();
			put8051ireg(x);
			break;
		case 11:		// $nn.b
			putbitadr(y);
			break;
		case 12:		// Rn,$nn rel
			put8051reg(x);
			putcomma();
			put8adr(y,2);
			break;
		case 13:		// 8-bit code
			put8adr(y,2);
			break;
		case 14:		// C,$nn.b
			putreg("C");
			putcomma();
			if (x == 0xA0 || x == 0xB0)
				putarg("/");
			putbitadr(y);
			break;
		case 15:		// $nn.b,C
			putbitadr(y);
			putcomma();
			putreg("C");
			break;
	}
	enddata2(x, y);
}

static void d3_8051(short x, short y, short z)
{
	data3(x, y, z);
	putopc(onam8051[x]);
	switch (ofmt)
	{
		case 0:		// opr $nnnn
			putadr2(y,z);
			break;
		case 1:		// opr $nn,#$nn
			putadr1(y);
			putcomma();
			putimm(z);
			break;
		case 2:		// opr $nn.b,$nrel
			putbitadr(y);
			putcomma();
			put8adr(z,3);
			break;
		case 3:		// opr $nn,$nrel
			putadr1(y);
			putcomma();
			put8adr(z,3);
			break;
		case 4:		// opr $nn,$nn
			putadr1(z);
			putcomma();
			putadr1(y);
			break;
		case 5:		// opr DPTR,#$nnnn
			putreg("DPTR");
			putcomma();
			putimm4(y,z);
			break;
		case 6:		// opr A,#$nn,$nrel
			putreg("A");
			putcomma();
			putimm(y);
			putcomma();
			put8adr(z,3);
			break;
		case 7:		// opr A,$nn,$nrel
			putreg("A");
			putcomma();
			putadr1(y);
			putcomma();
			put8adr(z,3);
			break;
		case 8:		// opr Rn,#$nn,$nrel
			put8051reg(x);
			putcomma();
			putimm(y);
			putcomma();
			put8adr(z,3);
			break;
		case 9:		// opr @Rn,#$nn,$nrel
			put8051ireg(x);
			putcomma();
			putimm(y);
			putcomma();
			put8adr(z,3);
			break;
	}
	enddata3(x, y, z);
}

void dsm8051(short n)
{
	short x,y;

	if (!init)
		d8051init();
	if (!otyp8051[n])
	{
		inval(n);
		return;
	}
#if DEBUG
	printf("op=%X pval=%X\n",n,otyp8051[n]);
#endif
	omod = otyp8051[n] / 16;
	ofmt = otyp8051[n] % 16;
	if (omod == 1)
		d1_8051(n);
	else if (omod == 2)
	{
		x = getnxt();
		d2_8051(n,x);
	}
	else if (omod == 3)
	{
		x = getnxt();
		y = getnxt();
		d3_8051(n,x,y);
	}
}

