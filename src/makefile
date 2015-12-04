#
#  makefile for DSM
#

.c.obj:
	@bcc -c -C -G -O -d -v -ml $*.c

AOBJ= dsm.obj dsmio.obj hash.obj \
	 dsm6502.obj dsm6801.obj dsm6805.obj dsm6809.obj dsm6811.obj \
	 dsm8051.obj dsm8080.obj dsmh8.obj dsmrsc.obj dsmz80.obj

LINKOPT= /c /n /v

all:	dsm.exe

install:
	tdstrip dsm.exe
	copy dsm.exe \bin\misc /v /y

dsm:	dsm.exe

cpubld:	cpubld.exe

dsm.exe: $(AOBJ)
	@tlink $(LINKOPT) c0l @link.lst,dsm,dsm,cl
	@del *.bak

dsm.obj: dsm.c dsm.h

dsm6502.obj: dsm6502.c dsm.h

dsm6801.obj: dsm6801.c dsm.h

dsm6805.obj: dsm6805.c dsm.h

dsm6809.obj: dsm6809.c dsm.h

dsm6811.obj: dsm6811.c dsm.h

dsm8051.obj: dsm8051.c dsm.h

dsm8080.obj: dsm8080.c dsm.h

dsmh8.obj: dsmh8.c dsm.h

dsmrsc.obj: dsmrsc.c dsm.h

dsmz80.obj: dsmz80.c dsm.h

dsmio.obj: dsmio.c dsm.h

hash.obj: hash.c hash.h

