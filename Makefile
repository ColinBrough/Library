#----------------------------------------------------------------------
#
#	Makefile for my library of useful C routines directory.
#
#----------------------------------------------------------------------
# $Id: Makefile,v 1.13 2021/03/25 19:21:20 cmb Exp $
#----------------------------------------------------------------------

INCDIR		= /home/cmb/include
LIBDIR		= /home/cmb/lib
CC		= gcc
CFLAGS		= -g -Wall -I. -fPIC
LDFLAGS		= -L$(LIBDIR)
LOADLIBES	= -lcmb

OBJS	= FileUtils.o		\
	  Curses.o		\
	  CursesLargeFont.o	\
	  Colours.o		\
	  Misc.o		\
	  Images.o		\
	  cmb.o

all:	cmb.a

cmb.a	: $(OBJS)
	ar -rs cmb.a $(OBJS)

$(OBJS)	: cmb.h

clean:
	rm -f $(OBJS) *~ *.o *.a

install	: all
	cp -f cmb.h $(INCDIR)
	cp -f cmb.a $(LIBDIR)/libcmb.a
