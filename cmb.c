/*----------------------------------------------------------------------
 *
 *	cmb.c	Place to put global variables and other core, non header
 *		stuff for the library routines.
 *
 *----------------------------------------------------------------------
 * $Id: cmb.c,v 1.8 2013/03/15 09:28:49 cmb Exp $
 *
 * $Log: cmb.c,v $
 * Revision 1.8  2013/03/15 09:28:49  cmb
 * Updated
 *
 * Revision 1.7  2012/08/24 09:33:58  cmb
 * Updated
 *
 * Revision 1.6  2012/08/24 09:32:31  cmb
 * Updated
 *
 * Revision 1.5  2005/06/01 19:19:53  cmb
 * Updated woth names of the months stuff
 *
 * Revision 1.4  1999/05/12 16:01:06  cmb
 * Updated to have more of the curses initialisation code "canned" here.
 *
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

WINDOW *Screen;			/* Curses window to use.		*/
int inside_curses = FALSE;	/* Flag indicating whether in curses	*/
FILE *tfile = NULL;		/* Trace file				*/

char *MonthNamesLong[13] = { NULL, "January", "February", "March", "April", 
			     "May", "June", "July", "August", "September", 
			     "October", "November", "December" };

char *MonthNamesShort[13] = { NULL, "Jan", "Feb", "Mar", "Apr", "May",
			      "Jun", "Jul", "Aug", "Sep", "Oct",
			      "Nov", "Dec" };

char *WeekNamesLong[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", 
			   "Thursday", "Friday", "Saturday" };

char *WeekNamesShort[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

int ColoursInitialised = FALSE;	/* Flag indicating whether colour strings (below)
				 * have been initialised yet
				 */
char ColoursClearScr[8], ColoursBlack[6], ColoursRed[8], ColoursBlue[8], 
    ColoursBoldBlue[8], ColoursBoldRed[8], ColoursGreen[8], ColoursBoldGreen[8], 
    ColoursYellow[8], ColoursCyan[8];
