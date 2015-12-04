// cputype.h - for XASM and DSM
// not compiler specific
// copyright (c) 1987-1993 Freedlight Software, Inc.

typedef struct {
	char name[8];			// name of cpu
	char sclass;			// class of cpu
	char subclass;			// subclass of cpu
	unsigned long maxmem;	// maximum memory size
	short maxrel;			// maximum relative branch
	short minrel;			// maximum relative branch
	char bits;				// cpu processor bits
	boolean byterev;		// byte reversal in word data
	boolean active;			// xasm implemented
	boolean dactive;		// dsm implemented
} scpu;

// cpu classes
#define Xnone	 0 // nothing
#define X1800	 1 // 1800 series
#define		X_1802		1
#define		X_1805		2
#define X32000	 2 // 32000 series
#define		X_32008		1
#define		X_32016		2
#define		X_32032		3
#define		X_32532		4
#define X34000	 3 // 34000 series
#define		X_34010		1
#define		X_34020		2
#define X3800	 4 // 3800 series
#define		X_3870		1
#define		X_F8		2
#define X56000	 5 // Motorola DSP56000 series
#define		X_56000		1
#define X62800	 6 // 62800 series
#define		X_62801		1
// reserved - 7
#define X6502	 8 // 6502 series
#define		X_6502		1
#define		X_6501		2
#define		X_6511		3
#define		X_65C00		4
#define		X_65C02		5
#define		X_65C151	6
#define X6800	 9 // 6800 series
#define		X_6800		1
#define		X_6802		2
#define		X_6808		3
#define X6801	10 // 6801 series
#define		X_6301		1
#define		X_6303		2
#define		X_6801		3
#define		X_6803		4
#define X6804	11 // 6804 series
#define		X_6804		1
#define X6805	12 // 6805 series
#define		X_6805		1
#define		X_146805	2
#define X6809	13 // 6809 series
#define		X_6809		1
#define X6811	14 // 6811 series
#define		X_68HC11	1
#define X68000	15 // 68000 series
#define		X_68000		1
#define		X_68008		2
#define		X_68010		3
#define		X_68020		4
#define		X_68030		5
#define		X_68200		6
#define X7500	16 // NEC 7500 series
#define		X_7500		1
#define		X_7501		2
#define		X_7502		3
#define		X_7520		4
#define X7700	17 // NEC 7700 series
#define		X_7720		1
#define X7800	18 // NEC 7800 series
#define		X_7800		1
#define		X_7801		2
#define		X_78C05		3
#define		X_7807		4
#define		X_7810		5
#define X8048	19 // 8048 series
#define		X_8048		1
// reserved - 20
#define X8051	21 // 8051 series
#define		X_8031		1
#define		X_8044		2
#define		X_8051		3
#define X8080	22 // 8080 series
#define		X_8080		1
#define		X_8085		2
#define		X_80C85		3
#define X8086	23 // 8086 series
#define		X_8088		1
#define		X_80C88		2
#define		X_8086		3
#define		X_80C86		4
#define		X_80186		5
#define		X_80C186	6
#define		X_80286		7
#define		X_80C286	8
#define		X_80386		9
#define X8096	24 // 8096 series
#define		X_8096		1
#define	XH8		25	// Hitachi H8 series
#define		X_H8_300	1
#define		X_H8_300H	2
#define XRSC	26 // Sensory RSC series
#define		X_RSC264	1
#define XCOP400	27 // COP400 series
#define		X_COP400	1
#define		X_COPS400	2
#define XNCR32	28 // NCR32 series
#define		X_NCR32		1
#define XNOVA	29 // DG NOVA series
#define		X_NOVA		1
#define XPDP8	30 // PDP8 series
#define		X_PDP8		1
#define XPDP11	31 // PDP11 series
#define		X_PDP11		1
#define XZ8		32 // Z8 series
#define		X_Z8		1
#define XZ80	33 // Z80 series
#define		X_64180		1
#define		X_84C00		2
#define		X_84C01		3
#define		X_NEC780	4
#define		X_NSC800	5
#define		X_Z80		6
#define XZ8000	34 // Z8000 series
#define		X_Z8001		1
#define		X_Z8002		2

