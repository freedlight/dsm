// dsmrc.c - module to handle RSC codes for DSM
// copyright (c) 1994, Freedlight Software

#include "dsm.h"

static char otyprc[] = {
	0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x00,	//00-07
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//08-0F
	0x31,0x33,0x34,0x32,0x34,0x33,0x34,0x33,	//10-17
	0x35,0x36,0x00,0x00,0x00,0x00,0x00,0x00,	//18-1F
	0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,	//20-27
	0x10,0x10,0x21,0x00,0x00,0x00,0x00,0x00,	//28-2F
	0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00,	//30-37
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//38-3F
	0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,	//40-47
	0x31,0x20,0x20,0x00,0x00,0x00,0x00,0x00,	//48-4F
	0x32,0x32,0x32,0x32,0x32,0x32,0x32,0x32,	//50-57
	0x32,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//58-5F
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//60-67
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//68-6F
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//70-77
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//78-7F
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//80-87
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//88-8F
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//90-97
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//98-9F
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//A0-A7
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//A8-AF
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//B0-B7
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//B8-BF
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//C0-C7
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//C8-CF
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//D0-D7
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//D8-DF
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//E0-E7
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//E8-EF
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//F0-F7
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//F8-FF
};

static char *onamrc[] = {
	"NOP"  ,"CLC"  ,"STC"  ,"CMC"  ,"CLI"  ,"STI"  ,""     ,""     , //00-07
	""     ,""     ,""     ,""     ,""     ,""     ,""     ,""     , //08-0F
	"MOV"  ,"MOV"  ,"MOV"  ,"MOV"  ,"MOVC" ,"MOVC" ,"MOVX" ,"MOVX" , //10-17
	"POP"  ,"PUSH" ,""     ,""     ,""     ,""     ,""     ,""     , //18-1F
	"JC"   ,"JNC"  ,"JZ"   ,"JNZ"  ,"JS"   ,"JNS"  ,"JMP"  ,"CALL" , //20-27
	"RET"  ,"IRET" ,"JMPR" ,""     ,""     ,""     ,""     ,""     , //28-2F
	"RL"   ,"RR"   ,"RLC"  ,"RRC"  ,"SHL"  ,"SHR"  ,"SAR"  ,""     , //30-37
	""     ,""     ,""     ,""     ,""     ,""     ,""     ,""     , //38-3F
	"AND"  ,"TM"   ,"OR"   ,"XOR"  ,"SUB"  ,"CP"   ,"SUBC" ,"ADD"  , //40-47
	"ADC"  ,"INC"  ,"DEC"  ,""     ,""     ,""     ,""     ,""     , //48-4F
	"AND"  ,"TM"   ,"OR"   ,"XOR"  ,"SUB"  ,"CP"   ,"SUBC" ,"ADD"  , //50-57
	"ADC"  ,""     ,""     ,""     ,""     ,""     ,""     ,""     , //58-5F
	""     ,""     ,""     ,""     ,""     ,""     ,""     ,""     , //60-67
	""     ,""     ,""     ,""     ,""     ,""     ,""     ,""     , //68-6F
	""     ,""     ,""     ,""     ,""     ,""     ,""     ,""     , //70-77
	""     ,""     ,""     ,""     ,""     ,""     ,""     ,""     , //78-7F
	""     ,""     ,""     ,""     ,""     ,""     ,""     ,""     , //80-87
	""     ,""     ,""     ,""     ,""     ,""     ,""     ,""     , //88-8F
	""     ,""     ,""     ,""     ,""     ,""     ,""     ,""     , //90-97
	""     ,""     ,""     ,""     ,""     ,""     ,""     ,""     , //98-9F
	""     ,""     ,""     ,""     ,""     ,""     ,""     ,""     , //A0-A7
	""     ,""     ,""     ,""     ,""     ,""     ,""     ,""     , //A8-AF
	""     ,""     ,""     ,""     ,""     ,""     ,""     ,""     , //B0-B7
	""     ,""     ,""     ,""     ,""     ,""     ,""     ,""     , //B8-BF
	""     ,""     ,""     ,""     ,""     ,""     ,""     ,""     , //C0-C7
	""     ,""     ,""     ,""     ,""     ,""     ,""     ,""     , //C8-CF
	""     ,""     ,""     ,""     ,""     ,""     ,""     ,""     , //D0-D7
	""     ,""     ,""     ,""     ,""     ,""     ,""     ,""     , //D8-DF
	""     ,""     ,""     ,""     ,""     ,""     ,""     ,""     , //E0-E7
	""     ,""     ,""     ,""     ,""     ,""     ,""     ,""     , //E8-EF
	""     ,""     ,""     ,""     ,""     ,""     ,""     ,""     , //F0-F7
	""     ,""     ,""     ,""     ,""     ,""     ,""     ,""       //F8-FF
};

static void drcinit(void)
{
	opcsp = 10;
	argsp = 6;
	cmtsp = 15;
	init = TRUE;
}

static void putrcreg(short x)
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

static void putrcireg(short x)
{
	if ((x & 1) == 1)
		putreg("R1");
	else
		putreg("R0");
}

static void d1_rc(short x)
{
	data1(x);
	putopc(onamrc[x]);
	enddata1(x);
	if ((x == 0x28) || (x == 0x29))	// RET, RETI
		putcr();
}

static void d2_rc(short x, short y)
{
	data2(x, y);
	putopc(onamrc[x]);
	switch (ofmt)
	{
		case 0:		// $nn
			putadr1(y);
			break;
		case 1:		// @$nn
			putat();
			putadr1(y);
			break;
	}
	enddata2(x, y);
}

static void d3_rc(short x, short y, short z)
{
	data3(x, y, z);
	putopc(onamrc[x]);
	switch (ofmt)
	{
		case 0:		// opr $nnnn
			putadr2(z,y);
			break;
		case 1:		// opr $nn,$nn
			putadr1(y);
			putcomma();
			putadr1(z);
			break;
		case 2:		// opr $nn,#$nn
			putadr1(y);
			putcomma();
			putimm(z);
			break;
		case 3:		// opr @$nn,$nn
			putat();
			putadr1(y);
			putcomma();
			putadr1(z);
			break;
		case 4:		// opr $nn,@$nn
			putadr1(y);
			putcomma();
			putat();
			putadr1(z);
			break;
		case 5:		// opr $nn,@++$nn
			putadr1(y);
			putcomma();
			putat();
			putincr();
			putadr1(z);
			break;
		case 6:		// opr @$nn--,$nn
			putat();
			putadr1(y);
			putdecr();
			putcomma();
			putadr1(z);
			break;
	}
	enddata3(x, y, z);
}

void dsmRSC(short n)
{
	short x,y;

	if (!init)
		drcinit();
	if (!otyprc[n])
	{
		inval(n);
		return;
	}
#if DEBUG
	printf("op=%X pval=%X\n",n,otyprc[n]);
#endif
	omod = otyprc[n] / 16;
	ofmt = otyprc[n] % 16;
	if (omod == 1)
		d1_rc(n);
	else if (omod == 2)
	{
		x = getnxt();
		d2_rc(n,x);
	}
	else if (omod == 3)
	{
		x = getnxt();
		y = getnxt();
		d3_rc(n,x,y);
	}
}

