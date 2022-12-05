/*----------------------------------------------------------------------
 *
 *	cmb.c	Place to put global variables and other core, non header
 *		stuff for the library routines.
 *
 *----------------------------------------------------------------------
 * $Id: cmb.c,v 1.15 2021/01/18 19:12:30 cmb Exp $
 *
 * $Log: cmb.c,v $
 * Revision 1.15  2021/01/18 19:12:30  cmb
 * Moved much of the tracer functionality into functions in C, rather
 * than pre-processor macros, to give some extra functionality -
 * including setting an "infinte loop" limit (tracecount), which is set
 * by tracestart(XX) and then each time 'tracer' is called incremented -
 * if count goes over the limit, bail out... To pick up line number and
 * filename still need pre-processor macro, which copes __LINE__ and
 * __FILE__ to global variables which are then picked up by the real C
 * functions defined here.
 *
 * Revision 1.14  2021/01/18 17:13:52  cmb
 * Updated
 *
 * Revision 1.13  2019/02/11 14:57:17  cmb
 * Updated list of known hostnames
 *
 * Revision 1.12  2019/01/21 19:26:54  cmb
 * Added array of hostnames
 *
 * Revision 1.11  2019/01/21 11:46:35  cmb
 * Updated
 *
 * Revision 1.10  2013/09/19 11:39:35  cmb
 * Updated
 *
 * Revision 1.9  2013/03/18 12:04:49  cmb
 * Updated
 *
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
int tracelimit = 0;             /* Bail-out limit when tracing - 0=infinite */
int tracecount = 0;             /* Count of number of trace steps taken */
int CurrentLineNumber = 0;	/* Line number in file, used by tracing code */
char *CurrentFileName = NULL;	/* Current filename, used by tracing code */

char HostName[200] = "NULL";	/* A blank value to start with...	*/
char *HostNames[NUMHOSTS] = { "rock", "mica", "opal", "agate", "topaz", "stone", NULL, NULL };
				/* List of hostnames here needs to be kept
				 * in sync with list of defines in cmb.h */

int HostNumber = -1;		/* A blank value to start with...	*/

char *MonthNamesLong[13] = { NULL, "January", "February", "March", "April", 
			     "May", "June", "July", "August", "September", 
			     "October", "November", "December" };

char *MonthNamesShort[13] = { NULL, "Jan", "Feb", "Mar", "Apr", "May",
			      "Jun", "Jul", "Aug", "Sep", "Oct",
			      "Nov", "Dec" };

char *WeekNamesLong[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", 
			   "Thursday", "Friday", "Saturday" };

char *WeekNamesShort[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

char ColoursClearScr[8]  = { 27, '[', 'H', 27, '[', '2', 'J', '\0' };
char ColoursBlack[6]     = { 27, '[', '0', '0', 'm', '\0' };
char ColoursRed[8]       = { 27, '[', '0', ';', '3', '1', 'm', '\0' };
char ColoursBlue[8]      = { 27, '[', '0', ';', '3', '4', 'm', '\0' };
char ColoursBoldBlue[8]  = { 27, '[', '3', '4', ';', '1', 'm', '\0' };
char ColoursBoldRed[8]   = { 27, '[', '3', '1', ';', '1', 'm', '\0' };
char ColoursGreen[8]     = { 27, '[', '0', ';', '3', '2', 'm', '\0' };
char ColoursBoldGreen[8] = { 27, '[', '3', '2', ';', '1', 'm', '\0' };
char ColoursYellow[8]    = { 27, '[', '0', ';', '3', '3', 'm', '\0' };
char ColoursCyan[8]      = { 27, '[', '0', ';', '3', '6', 'm', '\0' };

/*----------------------------------------------------------------------
 * Some of the tracing functionality goes here, so its not in another
 * part source file of the Library...
 *----------------------------------------------------------------------*/

void tracestart(int l)
{
    if ((l < 0) || (l > 100000))
    {
        if (inside_curses)
        {
	    endwin();
	    fputc(27,  stdout);
	    fputc('[', stdout);
	    fputc('0', stdout);
	    fputc('0', stdout);
	    fputc('m', stdout);
        }
        printf("In tracestart routine in cmb.c, out of range tracing limit set (%d)\n", l);
	exit(0);
    }
    tracelimit = l;
    
    tfile = fopen("TRACEFILE", "w");
    fprintf(tfile, "Trace starts (limit = %d\n", tracelimit);
}

/*----------------------------------------------------------------------
 * traceend	Function to cleanly closedown tracing
 *----------------------------------------------------------------------*/

void traceend()
{
    fprintf(tfile, "Trace ends\n");
    fclose(tfile); 
}

/*----------------------------------------------------------------------
 * TracerFunction	Function to output tracing information; picks
 *			up the filename and line number from global
 * 			variables whose values are set using macro
 *			expansion, and then does the variable number of
 *			arguments stuff via vfprintf
 *----------------------------------------------------------------------*/

void TracerFunction(char *format, ...)
{
    va_list valist;
    va_start(valist, format);
    
    fprintf(tfile, "%18s %5d ", CurrentFileName, CurrentLineNumber);
    vfprintf(tfile, format, valist);
    fflush(tfile);
    if ((tracecount++) > tracelimit)
    {
	fprintf(tfile, "FORCING TRACE END AND EXIT as over tracelimit (%d)\n", tracelimit);
	traceend();
	exit(-1);
    }
}

/*----------------------------------------------------------------------*/
