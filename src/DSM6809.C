// dsm6809.c - module to handle 6809 codes for DSM
// copyright (c) 1994, Freedlight Software

#include "dsm.h"

static char otyp6809[] = {
	21,02,02,21,21,02,21,21,21,21,21,02,21,21,21,21,	// 00 - 0F
	50,60,10,10,02,02,33,33,02,10,23,02,23,10,25,25,	// 10 - 1F
	22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,	// 20 - 2F
	40,40,40,40,24,24,24,24,02,10,10,10,23,10,02,10,	// 30 - 3F
	11,01,01,11,11,01,11,11,11,11,11,01,11,11,01,11,	// 40 - 4F
	12,01,01,12,12,01,12,12,12,12,12,01,12,12,01,12,	// 50 - 5F
	40,02,02,40,40,02,40,40,40,40,40,02,40,40,40,40,	// 60 - 6F
	31,03,03,31,31,03,31,31,31,31,31,03,31,31,31,31,	// 70 - 7F
	23,23,23,32,23,23,23,02,23,23,23,23,32,22,32,02,	// 80 - 8F
	21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,	// 90 - 9F
	40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,	// A0 - AF
	31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,	// B0 - BF
	23,23,23,32,23,23,23,02,23,23,23,23,32,02,32,02,	// C0 - CF
	21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,	// D0 - DF
	40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,	// E0 - EF
	31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31		// F0 - FF
};

static char *onam6809[] = {
// 00 - 07
	"NEG"  ,"     ",""     ,"COM"  ,"LSR"  ,""     ,"ROR"  ,"ASR",
// 08 - 0F
	"ASL"  ,"ROL"  ,"DEC"  ,""     ,"INC"  ,"TST"  ,"JMP"  ,"CLR",
// 10 - 17
	""     ,""     ,"NOP"  ,"SYNC" ,""     ,""     ,"LBRA" ,"LBSR",
// 18 - 1F
	""     ,"DAA"  ,"ORCC" ,""     ,"ANDCC","SEX"  ,"EXG"  ,"TFR",
// 20 - 27
	"BRA"  ,"BRN"  ,"BHI"  ,"BLS"  ,"BCC"  ,"BCS"  ,"BNE"  ,"BEQ",
// 28 - 2F
	"BVC"  ,"BVS"  ,"BPL"  ,"BMI"  ,"BGE"  ,"BLT"  ,"BGT"  ,"BLE",
// 30 - 37
	"LEAX" ,"LEAY" ,"LEAS" ,"LEAU" ,"PSHS" ,"PULS" ,"PSHU" ,"PULU",
// 38 - 3F
	""     ,"RTS"  ,"ABX"  ,"RTI"  ,"CWAI" ,"MUL"  ,""     ,"SWI",
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
	"SUBA" ,"CMPA" ,"SBCA" ,"SUBD" ,"ANDA" ,"BITA" ,"LDA"  ,"",
// 88 - 8F
	"EORA" ,"ADCA" ,"ORA"  ,"ADDA" ,"CMPX" ,"BSR"  ,"LDX"  ,"",
// 90 - 97
	"SUBA" ,"CMPA" ,"SBCA" ,"SUBD" ,"ANDA" ,"BITA" ,"LDA"  ,"STA",
// 98 - 9F
	"EORA" ,"ADCA" ,"ORA"  ,"ADDA" ,"CMPX" ,"JSR"  ,"LDX"  ,"STX",
// A0 - A7
	"SUBA" ,"CMPA" ,"SBCA" ,"SUBD" ,"ANDA" ,"BITA" ,"LDA"  ,"STA",
// A8 - AF
	"EORA" ,"ADCA" ,"ORA"  ,"ADDA" ,"CMPX" ,"JSR"  ,"LDX"  ,"STX",
// B0 - B7
	"SUBA" ,"CMPA" ,"SBCA" ,"SUBD" ,"ANDA" ,"BITA" ,"LDA"  ,"STA",
// B8 - BF
	"EORA" ,"ADCA" ,"ORA"  ,"ADDA" ,"CMPX" ,"JSR"  ,"LDX"  ,"STX",
// C0 - C7
	"SUBB" ,"CMPB" ,"SBCB" ,"ADDD" ,"ANDB" ,"BITB" ,"LDB"  ,"",
// C8 - CF
	"EORB" ,"ADCB" ,"ORB"  ,"ADDB" ,"LDD"  ,""     ,"LDU"  ,"",
// D0 - D7
	"SUBB" ,"CMPB" ,"SBCB" ,"ADDD" ,"ANDB" ,"BITB" ,"LDB"  ,"STB",
// D8 - DF
	"EORB" ,"ADCB" ,"ORB"  ,"ADDB" ,"LDD"  ,"STD"  ,"LDU"  ,"STU",
// E0 - E7
	"SUBB" ,"CMPB" ,"SBCB" ,"ADDD" ,"ANDB" ,"BITB" ,"LDB"  ,"STB",
// E8 - EF
	"EORB" ,"ADCB" ,"ORB"  ,"ADDB" ,"LDD"  ,"STD"  ,"LDU"  ,"STU",
// F0 - F7
	"SUBB" ,"CMPB" ,"SBCB" ,"ADDD" ,"ANDB" ,"BITB" ,"LDB"  ,"STB",
// F8 - FF
	"EORB" ,"ADCB" ,"ORB"  ,"ADDB" ,"LDD"  ,"STD"  ,"LDU"  ,"STU"
};

static char *oarg6809[] = {
// 00 - 07
	"0,X"  ,"1,X"  ,"2,X"  ,"3,X"  ,"4,X"  ,"5,X"  ,"6,X"  ,"7,X",
// 08 - 0F
	"8,X"  ,"9,X"  ,"10,X" ,"11,X" ,"12,X" ,"13,X" ,"14,X" ,"15,X",
// 10 - 17
	"-16,X","-15,X","-14,X","-13,X","-12,X","-11,X","-10,X","-9,X",
// 18 - 1F
	"-8,X" ,"-7,X" ,"-6,X" ,"-5,X" ,"-4,X" ,"-3,X" ,"-2,X" ,"-1,X",
// 20 - 27
	"0,Y"  ,"1,Y"  ,"2,Y"  ,"3,Y"  ,"4,Y"  ,"5,Y"  ,"6,Y"  ,"7,Y",
// 28 - 2F
	"8,Y"  ,"9,Y"  ,"10,Y" ,"11,Y" ,"12,Y" ,"13,Y" ,"14,Y" ,"15,Y",
// 30 - 37
	"-16,Y","-15,Y","-14,Y","-13,Y","-12,Y","-11,Y","-10,Y","-9,Y",
// 38 - 3F
	"-8,Y" ,"-7,Y" ,"-6,Y" ,"-5,Y" ,"-4,Y" ,"-3,Y" ,"-2,Y" ,"-1,Y",
// 40 - 47
	"0,U"  ,"1,U"  ,"2,U"  ,"3,U"  ,"4,U"  ,"5,U"  ,"6,U"  ,"7,U",
// 48 - 4F
	"8,U"  ,"9,U"  ,"10,U" ,"11,U" ,"12,U" ,"13,U" ,"14,U" ,"15,U",
// 50 - 57
	"-16,U","-15,U","-14,U","-13,U","-12,U","-11,U","-10,U","-9,U",
// 58 - 5F
	"-8,U" ,"-7,U" ,"-6,U" ,"-5,U" ,"-4,U" ,"-3,U" ,"-2,U" ,"-1,U",
// 60 - 67
	"0,S"  ,"1,S"  ,"2,S"  ,"3,S"  ,"4,S"  ,"5,S"  ,"6,S"  ,"7,S",
// 68 - 6F
	"8,S"  ,"9,S"  ,"10,S" ,"11,S" ,"12,S" ,"13,S" ,"14,S" ,"15,S",
// 70 - 77
	"-16,S","-15,S","-14,S","-13,S","-12,S","-11,S","-10,S","-9,S",
// 78 - 7F
	"-8,S" ,"-7,S" ,"-6,S" ,"-5,S" ,"-4,S" ,"-3,S" ,"-2,S" ,"-1,S",
// 80 - 87
	",X+"  ,",X++" ,",-X"  ,",--X" ,",X"   ,"B,X"  ,"A,X"  ,"",
// 88 - 8F
	",X"   ,",X"   ,""     ,"D,X"  ,",PCR" ,",PCR" ,""     ,"",
// 90 - 97
	""     ,"(,X++)",""    ,"(,--X)","(,X)","(B,X)","(A,X)","",
// 98 - 9F
	",X"   ,",X"   ,""     ,"(D,X)",",PCR" ,",PCR" ,""     ,"",
// A0 - A7
	",Y+"  ,",Y++" ,",-Y"  ,",--Y" ,",Y"   ,"B,Y"  ,"A,Y"  ,"",
// A8 - AF
	",Y"   ,",Y"   ,""     ,"D,Y"  ,",PCR" ,",PCR" ,""     ,"",
// B0 - B7
	""     ,"(,Y++)",""    ,"(,--Y)","(,Y)","(B,Y)","(A,Y)","",
// B8 - BF
	",Y"   ,",Y"   ,""     ,"(D,Y)",",PCR" ,",PCR" ,""     ,"",
// C0 - C7
	",U+"  ,",U++" ,",-U"  ,",--U" ,",U"   ,"B,U"  ,"A,U"  ,"",
// C8 - CF
	",U"   ,",U"   ,""     ,"D,U"  ,",PCR" ,",PCR" ,""     ,"",
// D0 - D7
	""     ,"(,U++)",""    ,"(,--U)","(,U)","(B,U)","(A,U)","",
// D8 - DF
	",U"   ,",U"   ,""     ,"(D,U)",",PCR" ,",PCR" ,""     ,"",
// E0 - E7
	",S+"  ,",S++" ,",-S"  ,",--S" ,",S"   ,"B,S"  ,"A,S"  ,"",
// E8 - EF
	",S"   ,",S"   ,""     ,"D,S"  ,",PCR" ,",PCR" ,""     ,"",
// F0 - F7
	""     ,"(,S++)",""    ,"(,--S)","(,S)","(B,S)","(A,S)","",
// F8 - FF
	",S"   ,",S"   ,""     ,"(D,S)",",PCR" ,",PCR" ,""     ,"",
};

static void d6809init(void)
{
	opcsp = 13;
	argsp = 6;
	cmtsp = 12;
	init = TRUE;
}

static void d1_6809(short x)
{
	data1(x);
	putopc(onam6809[x]);
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

static short rput_6809(char *s, short n)
{
	if (n)
	{
		putcomma();
		n++;
	}
	putreg(s);
	n += strlen(s);
	return n;
}

static void rproc_6809(short n)
{
	short o = 0;

	if (n & 0x80)
		o = rput_6809("PC",o);
	if (n & 0x40)
		o = rput_6809("S",o);
	if (n & 0x20)
		o = rput_6809("Y",o);
	if (n & 0x10)
		o = rput_6809("X",o);
	if (n & 0x08)
		o = rput_6809("DP",o);
	if (n & 0x04)
		o = rput_6809("B",o);
	if (n & 0x02)
		o = rput_6809("A",o);
	if (n & 0x01)
		o = rput_6809("CC",o);
}

static void d2_6809(short x, short y)
{
	short adr;

	data2(x, y);
	putopc(onam6809[x]);
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
		case 4:		// reg list
			rproc_6809(y);
			break;
		case 5:		// 2 registers
			switch ((y >> 4) & 0x0F)
			{
				case 0x00: putreg("D");  break; 
				case 0x01: putreg("X");  break; 
				case 0x02: putreg("Y");  break; 
				case 0x03: putreg("U");  break; 
				case 0x04: putreg("S");  break; 
				case 0x05: putreg("PC"); break; 
				case 0x08: putreg("A");  break; 
				case 0x09: putreg("B");  break; 
				case 0x0A: putreg("CC"); break; 
				case 0x0B: putreg("DP"); break; 
			}
			putcomma();
			switch (y & 0x0F)
			{
				case 0x00: putreg("D");  break; 
				case 0x01: putreg("X");  break; 
				case 0x02: putreg("Y");  break; 
				case 0x03: putreg("U");  break; 
				case 0x04: putreg("S");  break; 
				case 0x05: putreg("PC"); break; 
				case 0x08: putreg("A");  break; 
				case 0x09: putreg("B");  break; 
				case 0x0A: putreg("CC"); break; 
				case 0x0B: putreg("DP"); break; 
			}
			break;
	}
	enddata2(x, y);
}

static void d3_6809(short x, short y, short z)
{
	data3(x, y, z);
	putopc(onam6809[x]);
	switch (ofmt)
	{
		case 1:		// opr $nnnn
			putadr2(y,z);
			break;
		case 2:		// opr #$nnnn
			putimm4(y,z);
			break;
		case 3:		// pc relative
			putaddr((pc + 3) + (0x100 * y) + z);
			break;
	}
	enddata3(x, y, z);
}

static void dp_6809(short x, short y, short z)
{
	short u,v,o;

	putbyte(y);
	putsp(1);
	putbyte(z);
	putsp(1);
	ofmt = 0;
	if (z > 0x7F)
	{
		u = z & 0x1F;
		switch (u)
		{
			case 0x08:
			case 0x0C:
				ofmt = 1;
				break;
			case 0x09:
			case 0x0D:
				ofmt = 2;
				break;
			case 0x18:
			case 0x1C:
				ofmt = 3;
				break;
			case 0x19:
			case 0x1D:
			case 0x1F:
				ofmt = 4;
				break;
		}
	}
	if (ofmt == 1 || ofmt == 3)
	{
		u = getnxt();
		putbyte(u);
		putsp(2);
	}
	else if (ofmt == 2 || ofmt == 4)
	{
		u = getnxt();
		v = getnxt();
		putbyte(u);
		putsp(1);
		putbyte(v);
		putsp(1);
	}
	else
		putsp(4);
	if (x == 0)
	{
		if (ofmt == 2 || ofmt == 4)
			putsp(1);
		else
			putsp(3);
		putopc(onam6809[y]);
	}
	else if (omod > 4)
		putopc(onam6809[1]); // dummy
	else
		putopc(onam6809[x]);
	switch (ofmt)
	{
		case 0:
			putarg(oarg6809[z]);
			if (x)
				enddata3(x, y, z);
			else
				enddata2(y, z);
			break;
		case 1:
			putadr1(u);
			putarg(oarg6809[z]);
			if (x)
				enddata4(x, y, z, u);
			else
				enddata3(y, z, u);
			break;
		case 2:
			putadr2(u,v);
			putarg(oarg6809[z]);
			if (x)
				enddata5(x, y, z, u, v);
			else
				enddata4(y, z, u, v);
			break;
		case 3:
			putopn();
			putadr1(u);
			putarg(oarg6809[z]);
			putclo();
			if (x)
				enddata4(x, y, z, u);
			else
				enddata3(y, z, u);
			break;
		case 4:
			putopn();
			putadr2(u,v);
			putarg(oarg6809[z]);
			putclo();
			if (x)
				enddata5(x, y, z, u, v);
			else
				enddata4(y, z, u, v);
			break;
	}
}

static void d10_6809(short x, short y)
{
	short w,z;

	putbyte(x);
	putsp(1);
	switch (y)
	{
		case 0x3F:
			putbyte(y);
			putsp(1);
			putsp(5);
			break;
		case 0x93:
		case 0x9C:
		case 0x9E:
		case 0x9F:
		case 0xDE:
		case 0xDF:
			z = getnxt();
			putbyte(y);
			putsp(1);
			putbyte(z);
			putsp(3);
			break;
		case 0xA3:
			z = getnxt();
			strcpy(onam6809[1],"CMPD");
			dp_6809(x,y,z);
			return;
		case 0xAC:
			z = getnxt();
			strcpy(onam6809[1],"CMPY");
			dp_6809(x,y,z);
			return;
		case 0xAE:
			z = getnxt();
			strcpy(onam6809[1],"LDY");
			dp_6809(x,y,z);
			return;
		case 0xAF:
			z = getnxt();
			strcpy(onam6809[1],"STY");
			dp_6809(x,y,z);
			return;
		case 0xEE:
			z = getnxt();
			strcpy(onam6809[1],"LDS");
			dp_6809(x,y,z);
			return;
		case 0xEF:
			z = getnxt();
			strcpy(onam6809[1],"STS");
			dp_6809(x,y,z);
			return;
		case 0x21:
		case 0x22:
		case 0x23:
		case 0x24:
		case 0x25:
		case 0x26:
		case 0x27:
		case 0x28:
		case 0x29:
		case 0x2A:
		case 0x2B:
		case 0x2C:
		case 0x2D:
		case 0x2E:
		case 0x2F:
		case 0x83:
		case 0x8C:
		case 0x8E:
		case 0xB3:
		case 0xBC:
		case 0xBE:
		case 0xBF:
		case 0xCE:
		case 0xFE:
		case 0xFF:
			z = getnxt();
			w = getnxt();
			putbyte(y);
			putsp(1);
			putbyte(z);
			putsp(1);
			putbyte(w);
			break;
	}
	putsp(2);
	switch (y)
	{
		case 0x21:
			putopc("LBRN");
			break;
		case 0x22:
			putopc("LBHI");
			break;
		case 0x23:
			putopc("LBLS");
			break;
		case 0x24:
			putopc("LBCC");
			break;
		case 0x25:
			putopc("LBCS");
			break;
		case 0x26:
			putopc("LBNE");
			break;
		case 0x27:
			putopc("LBEQ");
			break;
		case 0x28:
			putopc("LBVC");
			break;
		case 0x29:
			putopc("LBVS");
			break;
		case 0x2A:
			putopc("LBPL");
			break;
		case 0x2B:
			putopc("LBMI");
			break;
		case 0x2C:
			putopc("LBGE");
			break;
		case 0x2D:
			putopc("LBLT");
			break;
		case 0x2E:
			putopc("LBGT");
			break;
		case 0x2F:
			putopc("LBLE");
			break;
		case 0x3F:
			putopc("SWI2");
			break;
		case 0x83:
		case 0x93:
		case 0xB3:
			putopc("CMPD");
			break;
		case 0x8C:
		case 0x9C:
		case 0xBC:
			putopc("CMPY");
			break;
		case 0x8E:
		case 0x9E:
		case 0xBE:
			putopc("LDY");
			break;
		case 0x9F:
		case 0xBF:
			putopc("STY");
			break;
		case 0xCE:
		case 0xDE:
		case 0xFE:
			putopc("LDS");
			break;
		case 0xDF:
		case 0xFF:
			putopc("STS");
			break;
	}
	switch (y)
	{
		case 0x3F:
			break;
		case 0x93:
		case 0x9C:
		case 0x9E:
		case 0x9F:
		case 0xDE:
		case 0xDF:
			putadr1(z);
			break;
		case 0x83:
		case 0x8C:
		case 0x8E:
		case 0xCE:
			putimm4(z,w);
			break;
		case 0xB3:
		case 0xBC:
		case 0xBE:
		case 0xBF:
		case 0xFE:
		case 0xFF:
			putadr2(z,w);
			break;
		default: // 0x21 - 0x2F
			putaddr((pc + 4) + (0x100 * z) + w);
			break;
	}
	switch (y)
	{
		case 0x3F:
			enddata2(x, y);
			break;
		case 0x93:
		case 0x9C:
		case 0x9E:
		case 0x9F:
		case 0xDE:
		case 0xDF:
			enddata3(x, y, z);
			break;
		default:
			enddata4(x, y, z, w);
			break;
	}
}

static void d11_6809(short x, short y)
{
	short w,z;

	putbyte(x);
	putsp(1);
	switch (y)
	{
		case 0x3F:
			putbyte(y);
			putsp(1);
			putsp(5);
			break;
		case 0x93:
		case 0x9C:
			z = getnxt();
			putbyte(y);
			putsp(1);
			putbyte(z);
			putsp(3);
			break;
		case 0xA3:
			z = getnxt();
			strcpy(onam6809[1],"CMPU");
			dp_6809(x,y,z);
			return;
		case 0xAC:
			z = getnxt();
			strcpy(onam6809[1],"CMPS");
			dp_6809(x,y,z);
			return;
		case 0x83:
		case 0x8C:
		case 0xB3:
		case 0xBC:
			z = getnxt();
			w = getnxt();
			putbyte(y);
			putsp(1);
			putbyte(z);
			putsp(1);
			putbyte(w);
			break;
	}
	putsp(2);
	switch (y)
	{
		case 0x3F:
			putopc("SWI3");
			break;
		case 0x93:
		case 0x83:
		case 0xB3:
			putopc("CMPU");
			break;
		case 0x9C:
		case 0x8C:
		case 0xBC:
			putopc("CMPS");
			break;
	}
	switch (y)
	{
		case 0x3F:
			break;
		case 0x93:
		case 0x9C:
			putadr1(z);
			break;
		case 0x83:
		case 0x8C:
			putimm4(z,w);
			break;
		case 0xB3:
		case 0xBC:
			putadr2(z,w);
			break;
	}
	switch (y)
	{
		case 0x3F:
			enddata2(x, y);
			break;
		case 0x93:
		case 0x9C:
			enddata3(x, y, z);
			break;
		case 0x83:
		case 0x8C:
		case 0xB3:
		case 0xBC:
			enddata4(x, y, z, w);
			break;
	}
}

void dsm6809(short n)
{
	short x,y;

	if (!init)
		d6809init();
#if DEBUG
	printf("op=%d pval=%d\n",n,otyp6809[n]);
#endif
	omod = otyp6809[n] / 10;
	ofmt = otyp6809[n] % 10;
	switch (omod)
	{
		case 0:
			inval(n);
			for (x=1; x<ofmt; x++)
			{
				n = getnxt();
				inval(n);
			}
			break;
		case 1:
			d1_6809(n);
			break;
		case 2:
			x = getnxt();
			d2_6809(n,x);
			break;
		case 3:
			x = getnxt();
			y = getnxt();
			d3_6809(n,x,y);
			break;
		case 4:
			x = getnxt();
			dp_6809(0,n,x);
			break;
		case 5:
			x = getnxt();
			d10_6809(n,x);
			break;
		case 6:
			x = getnxt();
			d11_6809(n,x);
			break;
	}
}
