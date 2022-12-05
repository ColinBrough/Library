#----------------------------------------------------------------------
#
#	Makefile for my library of useful C routines directory.
#
#----------------------------------------------------------------------
# $Id: Makefile,v 1.5 1998/08/05 15:17:56 cmb Exp $
#----------------------------------------------------------------------

INCDIR		= /home/cmb/include
LIBDIR		= /home/cmb/lib
CC		= gcc
CFLAGS		= -g -Wall -I.
LDFLAGS		= -L$(LIBDIR)
LOADLIBES	= -lcmb

OBJS	= FileUtils.o	\
	  Curses.o	\
	  cmb.o

all:	cmb.a

cmb.a	: $(OBJS)
	ar -rs cmb.a $(OBJS)

$(OBJS)	: cmb.h

clean:
	rm -f $(OBJS) *~ *.o *.a

install	: all
	cp cmb.h $(INCDIR)
	cp cmb.a $(LIBDIR)/libcmb.a
