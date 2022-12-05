/*----------------------------------------------------------------------
 *
 *	cmb.c	Place to put global variables and other core, non header
 *		stuff for the library routines.
 *
 *----------------------------------------------------------------------
 * $Id: cmb.c,v 1.3 1998/07/25 17:43:45 cmb Exp $
 *
 * $Log: cmb.c,v $
 * Revision 1.3  1998/07/25 17:43:45  cmb
 * Updated.
 *
 * Revision 1.2  1998/07/25 17:38:50  cmb
 * Updated.
 *
 * Revision 1.1  1998/07/25 17:36:14  cmb
 * Initial revision
 *
 *----------------------------------------------------------------------*/

#include <cmb.h>

int inside_curses = FALSE;	/* Flag indicating whether in curses	*/
FILE *tfile = NULL;		/* Trace file				*/
