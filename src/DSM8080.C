// dsm8080.c - module to handle 8080 codes for DSM
// copyright (c) 1994, Freedlight Software

#include "dsm.h"

static char otyp8080[] = {
	10,32,10,10,10,10,22,10,00,10,10,10,10,10,22,10,	// 00 - 0F
	00,32,10,10,10,10,22,10,00,10,10,10,10,10,22,10,	// 10 - 1F
	18,32,31,10,10,10,22,10,00,10,31,10,10,10,22,10,	// 20 - 2F
	18,32,31,10,10,10,22,10,00,10,31,10,10,10,22,10,	// 30 - 3F
	10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,	// 40 - 4F
	10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,	// 50 - 5F
	10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,	// 60 - 6F
	10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,	// 70 - 7F
	10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,	// 80 - 8F
	10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,	// 90 - 9F
	10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,	// A0 - AF
	10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,	// B0 - BF
	10,10,31,31,31,10,22,10,10,10,31,00,31,31,22,10,	// C0 - CF
	10,10,31,21,31,10,22,10,10,00,31,21,31,00,22,10,	// D0 - DF
	10,10,31,10,31,10,22,10,10,10,31,10,31,00,22,10,	// E0 - EF
	10,10,31,10,31,10,22,10,10,10,31,10,31,00,22,10		// F0 - FF
};

static char *onam8080[] = {
// 00 - 07
	"NOP" ,"LXI" ,"STAX","INX" ,"INR" ,"DCR" ,"MVI" ,"RLC",
// 08 - 0F
	" "   ,"DAD" ,"LDAX","DCX" ,"INR" ,"DCR" ,"MVI" ,"RRC",
// 10 - 17
	" "   ,"LXI" ,"STAX","INX" ,"INR" ,"DCR" ,"MVI" ,"RAL",
// 18 - 1F
	" "   ,"DAD" ,"LDAX","DCX" ,"INR" ,"DCR" ,"MVI" ,"RAR",
// 20 - 27
	"RIM" ,"LXI" ,"SHLD","INX" ,"INR" ,"DCR" ,"MVI" ,"DAA",
// 28 - 2F
	" "   ,"DAD" ,"LHLD","DCX" ,"INR" ,"DCR" ,"MVI" ,"CMA",
// 30 - 37
	"SIM" ,"LXI" ,"STA" ,"INX" ,"INR" ,"DCR" ,"MVI" ,"STC",
// 38 - 3F
	" "   ,"DAD" ,"LDA" ,"DCX" ,"INR" ,"DCR" ,"MVI" ,"CMC",
// 40 - 47
	"MOV" ,"MOV" ,"MOV" ,"MOV" ,"MOV" ,"MOV" ,"MOV" ,"MOV",
// 48 - 4F
	"MOV" ,"MOV" ,"MOV" ,"MOV" ,"MOV" ,"MOV" ,"MOV" ,"MOV",
// 50 - 57
	"MOV" ,"MOV" ,"MOV" ,"MOV" ,"MOV" ,"MOV" ,"MOV" ,"MOV",
// 58 - 5F
	"MOV" ,"MOV" ,"MOV" ,"MOV" ,"MOV" ,"MOV" ,"MOV" ,"MOV",
// 60 - 67
	"MOV" ,"MOV" ,"MOV" ,"MOV" ,"MOV" ,"MOV" ,"MOV" ,"MOV",
// 68 - 6F
	"MOV" ,"MOV" ,"MOV" ,"MOV" ,"MOV" ,"MOV" ,"MOV" ,"MOV",
// 70 - 77
	"MOV" ,"MOV" ,"MOV" ,"MOV" ,"MOV" ,"MOV" ,"HLT" ,"MOV",
// 78 - 7F
	"MOV" ,"MOV" ,"MOV" ,"MOV" ,"MOV" ,"MOV" ,"MOV" ,"MOV",
// 80 - 87
	"ADD" ,"ADD" ,"ADD" ,"ADD" ,"ADD" ,"ADD" ,"ADD" ,"ADD",
// 88 - 8F
	"ADC" ,"ADC" ,"ADC" ,"ADC" ,"ADC" ,"ADC" ,"ADC" ,"ADC",
// 90 - 97
	"SUB" ,"SUB" ,"SUB" ,"SUB" ,"SUB" ,"SUB" ,"SUB" ,"SUB",
// 98 - 9F
	"SBB" ,"SBB" ,"SBB" ,"SBB" ,"SBB" ,"SBB" ,"SBB" ,"SBB",
// A0 - A7
	"ANA" ,"ANA" ,"ANA" ,"ANA" ,"ANA" ,"ANA" ,"ANA" ,"ANA",
// A8 - AF
	"XRA" ,"XRA" ,"XRA" ,"XRA" ,"XRA" ,"XRA" ,"XRA" ,"XRA",
// B0 - B7
	"ORA" ,"ORA" ,"ORA" ,"ORA" ,"ORA" ,"ORA" ,"ORA" ,"ORA",
// B8 - BF
	"CMP" ,"CMP" ,"CMP" ,"CMP" ,"CMP" ,"CMP" ,"CMP" ,"CMP",
// C0 - C7
	"RNZ" ,"POP" ,"JNZ" ,"JMP" ,"CNZ" ,"PUSH","ADI" ,"RST",
// C8 - CF
	"RZ"  ,"RET" ,"JZ"  ," "   ,"CZ"  ,"CALL","ACI" ,"RST",
// D0 - D7
	"RNC" ,"POP" ,"JNC" ,"OUT" ,"CNC" ,"PUSH","SUI" ,"RST",
// D8 - DF
	"RC"  ," "   ,"JC"  ,"IN"  ,"CC"  ," "   ,"SBI" ,"RST",
// E0 - E7
	"RPO" ,"POP" ,"JPO" ,"XTHL","CPO" ,"PUSH","ANI" ,"RST",
// E8 - EF
	"RPE" ,"PCHL","JPE" ,"XCHG","CPE" ," "   ,"XRI" ,"RST",
// F0 - F7
	"RP"  ,"POP" ,"JP"  ,"DI"  ,"CP"  ,"PUSH","ORI" ,"RST",
// F8 - FF
	"RM"  ,"SPHL","JM"  ,"EI"  ,"CM"  ," "   ,"CPI" ,"RST",
};

static char *oarg8080[] = {
// 00 - 07
	""    ,"B,"  ,"B"   ,"B"   ,"B"   ,"B"   ,"B,"  ,"",
// 08 - 0F
	""    ,"B"   ,"B"   ,"B"   ,"C"   ,"C"   ,"C,"  ,"",
// 10 - 17
	""    ,"D,"  ,"D"   ,"D"   ,"D"   ,"D"   ,"D,"  ,"",
// 18 - 1F
	""    ,"D"   ,"D"   ,"D"   ,"E"   ,"E"   ,"E,"  ,"",
// 20 - 27
	""    ,"H,"  ,""    ,"H"   ,"H"   ,"H"   ,"H,"  ,"",
// 28 - 2F
	""    ,"H"   ,""    ,"H"   ,"L"   ,"L"   ,"L,"  ,"",
// 30 - 37
	""    ,"SP," ,""    ,"SP"  ,"M"   ,"M"   ,"M,"  ,"",
// 38 - 3F
	""    ,"SP"  ,""    ,"SP"  ,"A"   ,"A"   ,"A,"  ,"",
// 40 - 47
	"B,B" ,"B,C" ,"B,D" ,"B,E" ,"B,H" ,"B,L" ,"B,M" ,"B,A",
// 48 - 4F
	"C,B" ,"C,C" ,"C,D" ,"C,E" ,"C,H" ,"C,L" ,"C,M" ,"C,A",
// 50 - 57
	"D,B" ,"D,C" ,"D,D" ,"D,E" ,"D,H" ,"D,L" ,"D,M" ,"D,A",
// 58 - 5F
	"E,B" ,"E,C" ,"E,D" ,"E,E" ,"E,H" ,"E,L" ,"E,M" ,"E,A",
// 60 - 67
	"H,B" ,"H,C" ,"H,D" ,"H,E" ,"H,H" ,"H,L" ,"H,M" ,"H,A",
// 68 - 6F
	"L,B" ,"L,C" ,"L,D" ,"L,E" ,"L,H" ,"L,L" ,"L,M" ,"L,A",
// 70 - 77
	"M,B" ,"M,C" ,"M,D" ,"M,E" ,"M,H" ,"M,L" ,""    ,"M,A",
// 78 - 7F
	"A,B" ,"A,C" ,"A,D" ,"A,E" ,"A,H" ,"A,L" ,"A,M" ,"A,A",
// 80 - 87
	"B"   ,"C"   ,"D"   ,"E"   ,"H"   ,"L"   ,"M"   ,"A",
// 88 - 8F
	"B"   ,"C"   ,"D"   ,"E"   ,"H"   ,"L"   ,"M"   ,"A",
// 90 - 97
	"B"   ,"C"   ,"D"   ,"E"   ,"H"   ,"L"   ,"M"   ,"A",
// 98 - 9F
	"B"   ,"C"   ,"D"   ,"E"   ,"H"   ,"L"   ,"M"   ,"A",
// A0 - A7
	"B"   ,"C"   ,"D"   ,"E"   ,"H"   ,"L"   ,"M"   ,"A",
// A8 - AF
	"B"   ,"C"   ,"D"   ,"E"   ,"H"   ,"L"   ,"M"   ,"A",
// B0 - B7
	"B"   ,"C"   ,"D"   ,"E"   ,"H"   ,"L"   ,"M"   ,"A",
// B8 - BF
	"B"   ,"C"   ,"D"   ,"E"   ,"H"   ,"L"   ,"M"   ,"A",
// C0 - C7
	""    ,"B"   ,""    ,""    ,""    ,"B"   ,""    ,"0",
// C8 - CF
	""    ,""    ,""    ,""    ,""    ,""    ,""    ,"1",
// D0 - D7
	""    ,"D"   ,""    ,""    ,""    ,"D"   ,""    ,"2",
// D8 - DF
	""    ,""    ,""    ,""    ,""    ,""    ,""    ,"3",
// E0 - E7
	""    ,"H"   ,""    ,""    ,""    ,"H"   ,""    ,"4",
// E8 - EF
	""    ,""    ,""    ,""    ,""    ,""    ,""    ,"5",
// F0 - F7
	""    ,"PSW" ,""    ,""    ,""    ,"PSW" ,""    ,"6",
// F8 - FF
	""    ,""    ,""    ,""    ,""    ,""    ,""    ,"7"
};

static void d8080init(void)
{
	opcsp = 10;
	argsp = 5;
	cmtsp = 12;
	init = TRUE;
}

static void d1_8080(short x)
{
	data1(x);
	putopc(onam8080[x]);
	putarg(oarg8080[x]);
	enddata1(x);
	if (x == 0xC9) // RTS
		putcr();
}

static void d2_8080(short x, short y)
{
	data2(x, y);
	putopc(onam8080[x]);
	switch (ofmt)
	{
		case 1:		// opr $nn
			putarg(oarg8080[x]);
			putadr1(y);
			break;
		case 2:		// opr #$nn
			putarg(oarg8080[x]);
			putimm(y);
			break;
	}
	enddata2(x, y);
}

static void d3_8080(short x, short y, short z)
{
	data3(x, y, z);
	putopc(onam8080[x]);
	switch (ofmt)
	{
		case 1:		// opr $nnnn
			putarg(oarg8080[x]);
			putadr2(z,y);
			break;
		case 2:		// opr #$nnnn
			putarg(oarg8080[x]);
			putimm4(z,y);
			break;
	}
	enddata3(x, y, z);
}

void dsm8080(short n)
{
	short x,y;

	if (!init)
		d8080init();
	if (!otyp8080[n])
	{
		inval(n);
		return;
	}
#if DEBUG
	printf("op=%d pval=%d\n",n,otyp8080[n]);
#endif
	init = TRUE;
	omod = otyp8080[n] / 10;
	ofmt = otyp8080[n] % 10;
	if (ofmt > 7 && submach == X_8080)
	{
		inval(n);
		return;
	}
	if (omod == 1)
		d1_8080(n);
	else if (omod == 2)
	{
		x = getnxt();
		d2_8080(n,x);
	}
	else if (omod == 3)
	{
		x = getnxt();
		y = getnxt();
		d3_8080(n,x,y);
	}
	else
		inval(n);
}
