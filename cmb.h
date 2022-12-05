/*----------------------------------------------------------------------
 *
 *	cmb.h	Header file for the utility and convenience stuff
 *		handy to have available when I am programming my own
 *		C code.
 *
 *----------------------------------------------------------------------
 * $Id: cmb.h,v 1.50 2019/01/21 11:48:01 cmb Exp $
 *
 * $Log: cmb.h,v $
 * Revision 1.50  2019/01/21 11:48:01  cmb
 * Added the host number variable
 *
 * Revision 1.49  2019/01/21 11:44:10  cmb
 * Added hostnumber constants
 *
 * Revision 1.48  2019/01/09 16:40:22  cmb
 * Added file detection/confirmation routine header
 *
 * Revision 1.47  2018/08/14 12:48:21  cmb
 * Updated
 *
 * Revision 1.46  2018/06/06 11:58:31  cmb
 * Updated
 *
 * Revision 1.45  2016/08/09 12:51:16  cmb
 * Summary: Updated
 *
 * Revision 1.44  2016/06/16 16:57:57  cmb
 * Summary: Added header for routine to read integer from a file
 *
 * Revision 1.43  2015/05/21 12:10:41  cmb
 * Updated
 *
 * Revision 1.42  2015/05/21 11:54:22  cmb
 * Added routines to return the day of the week name of a given date
 *
 * Revision 1.41  2015/05/08 11:13:14  cmb
 * Updated
 *
 * Revision 1.40  2014/12/22 14:53:27  cmb
 * Updated
 *
 * Revision 1.39  2014/06/04 14:27:02  cmb
 * Updated
 *
 * Revision 1.38  2013/09/19 11:47:58  cmb
 * Added function definitions for hostname handling functions (ishost,
 * topaz, mica, rock).
 *
 * Revision 1.37  2013/09/19 11:39:13  cmb
 * Updated
 *
 * Revision 1.36  2013/09/15 22:41:22  cmb
 * Updated
 *
 * Revision 1.35  2013/03/18 12:03:29  cmb
 * Updated
 *
 * Revision 1.34  2013/03/15 09:55:20  cmb
 * Updated
 *
 * Revision 1.33  2013/03/15 09:30:40  cmb
 * Updated
 *
 * Revision 1.32  2013/01/30 14:06:24  cmb
 * Updated
 *
 * Revision 1.31  2013/01/30 14:05:15  cmb
 * UPdated
 *
 * Revision 1.30  2012/08/24 09:34:08  cmb
 * Updated
 *
 * Revision 1.29  2012/08/23 20:19:58  cmb
 * Added extra date handling utility routines
 *
 * Revision 1.28  2009/08/12 20:28:53  cmb
 * Updated
 *
 * Revision 1.27  2008/10/21 20:50:33  cmb
 * Updated
 *
 * Revision 1.26  2008/08/19 19:37:08  cmb
 * Reverted once I've found the right package!!
 *
 * Revision 1.25  2008/08/19 19:23:35  cmb
 * Updated
 *
 * Revision 1.24  2007/09/12 21:27:34  cmb
 * Updated
 *
 * Revision 1.23  2005/06/01 19:20:04  cmb
 * Updated with names of the month stuff
 *
 * Revision 1.22  2003/11/18 15:47:45  cmb
 * Updated
 *
 * Revision 1.21  2003/06/03 12:20:26  cmb
 * Updated.
 *
 * Revision 1.20  2003/04/22 23:07:11  cmb
 * Updated
 *
 * Revision 1.19  2003/02/17 12:29:27  cmb
 * Updated.
 *
 * Revision 1.18  2002/12/18 16:29:46  cmb
 * Updated.
 *
 * Revision 1.17  2002/12/18 16:24:16  cmb
 * Updated.
 *
 * Revision 1.16  2000/05/09 20:24:11  cmb
 * Added header and routine from Misc.c
 *
 * Revision 1.15  2000/05/05 13:36:31  cmb
 * Updated.
 *
 * Revision 1.14  1999/08/17 12:25:36  cmb
 * Updated.
 *
 * Revision 1.13  1999/05/12 16:01:12  cmb
 * Updated to have more of the curses initialisation code "canned" here.
 *
 * Revision 1.12  1999/02/27 15:47:41  cmb
 * Updated.
 *
 * Revision 1.11  1999/01/22 16:59:43  cmb
 * Updated.
 *
 * Revision 1.10  1998/08/21 20:51:04  cmb
 * Updated so now doesn't use varargs, but assumes that the path will
 * come in NULL when no path has to be prepended to a filename to be
 * mapped or copied.
 *
 * Revision 1.9  1998/08/19 21:12:20  cmb
 * Include the time header, and function prototypes for the colour
 * routines.
 *
 * Revision 1.8  1998/08/05 15:19:11  cmb
 * Changed the prototype of copy_file to enable it to take an optional
 * third (path) argument.
 *
 * Revision 1.7  1998/08/04 22:15:24  cmb
 * Updated so that a couple of functions properly describe things that
 * they only use as input as 'const'.
 *
 * Revision 1.6  1998/08/04 19:13:31  cmb
 * Redid definition of MapFile to match changes in FileUtils.c allowing
 * an optional path to be passed in to construct the path, via the stdarg
 * mechanism.
 *
 * Revision 1.5  1998/08/04 18:21:58  cmb
 * Added headers for two slightly higher level wrapper functions round
 * the file mapping and unmapping code, making it slightly easier to use
 * in conventional ways.
 *
 * Revision 1.4  1998/07/25 17:43:13  cmb
 * Removed redundant true/false definitions.
 *
 * Revision 1.3  1998/07/25 17:40:35  cmb
 * A few #defines for use by curses programs, macros to aid tracing, and
 * a couple of global variables - one the FILE * for the tracing macros,
 * and the other an integer variable indicating whether we are currently
 * inside curses.
 *
 * Revision 1.2  1998/07/25 14:36:27  cmb
 * Added another function header.
 *
 * Revision 1.1  1998/07/25 14:30:57  cmb
 * Initial revision
 *
 *----------------------------------------------------------------------*/

#define _GNU_SOURCE         /* Be quite happy to use GNU extensions	*/

#include <stdio.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <signal.h>
#include <ncurses.h>
#include <time.h>
#include <mntent.h>
#include <pwd.h>
#include <math.h>

/*----------------------------------------------------------------------
 * Some common ncurses defines, to save space in the application specific
 * header files.
 *----------------------------------------------------------------------*/

#define BLACK_ON_WHITE    1
#define RED_ON_WHITE      2
#define BLUE_ON_WHITE     3
#define GREEN_ON_WHITE    4
#define YELLOW_ON_WHITE   5
#define MAGENTA_ON_WHITE  6
#define CYAN_ON_WHITE     7
#define RED_ON_BLACK      8
#define BLUE_ON_BLACK     9
#define GREEN_ON_BLACK   10
#define YELLOW_ON_BLACK  11
#define MAGENTA_ON_BLACK 12
#define CYAN_ON_BLACK    13
#define WHITE_ON_BLACK   14

/*----------------------------------------------------------------------
 * A fancy error reporting macro - doubt this will work except with gcc!
 * It prints the line number and file along with the actual error, which
 * can be a 'printf' style parameter string with arguments... Note how it
 * drops out of curses if that is active, and resets the terminal as
 * required.
 *----------------------------------------------------------------------*/

#define error( format, args...) \
{\
        if (inside_curses)\
        {\
                endwin();\
                inside_curses = FALSE;\
                fputc(27,  stdout);\
                fputc('[', stdout);\
                fputc('0', stdout);\
                fputc('0', stdout);\
                fputc('m', stdout);\
        }\
        printf("Error at line %d of file %s\n", __LINE__, __FILE__);\
        printf(format, ##args);\
        exit(-1);\
}

/*----------------------------------------------------------------------
 * Macros to aid with tracing what is going on by doing flushed prints
 * to a TRACEFILE.
 *----------------------------------------------------------------------*/

#define tracestart \
{\
        tfile = fopen("TRACEFILE", "w");\
        fprintf(tfile, "Trace starts\n");\
}

#define traceend   { fprintf(tfile, "Trace ends\n"); fclose(tfile); }

#define tracer( format, args...) \
{\
        fprintf(tfile, "%18s %5d ", __FILE__, __LINE__);\
        fprintf(tfile, format, ##args);\
        fflush(tfile);\
}

/*----------------------------------------------------------------------
 * Some constants to represent particular hosts
 *----------------------------------------------------------------------*/

#define HOST_ROCK 0
#define HOST_MICA 1
#define HOST_OPAL 2
#define HOST_AGATE 3

/*----------------------------------------------------------------------
 * Type definitions
 *----------------------------------------------------------------------*/
 
typedef struct FileDes 
{
    char *page;
    char filename[PATH_MAX];
    size_t length;
    int file_descriptor;
    FILE *file;
} FileDes;

typedef struct ImgElem
{
    int r;
    int g;
    int b;
} ImgElem;

/*----------------------------------------------------------------------
 * OK, so globals are bad form in a library, but handy...
 *----------------------------------------------------------------------*/

extern WINDOW *Screen;		/* Curses window to use.		*/
extern int inside_curses;       /* Flag indicating whether in curses    */
extern FILE *tfile;		/* Trace file				*/
extern char HostName[200];	/* Hostname				*/
extern int HostNumber;		/* A number for the current host	*/

extern char *MonthNamesLong[13];	/* Names of the months		*/
extern char *MonthNamesShort[13];	/* Short form is 1st 3 chars	*/
extern char *WeekNamesLong[7];		/* Names of the months		*/
extern char *WeekNamesShort[7];		/* Short form is 1st 3 chars	*/

extern char ColoursClearScr[8];
extern char ColoursBlack[6];
extern char ColoursRed[8];
extern char ColoursBlue[8];
extern char ColoursBoldBlue[8];
extern char ColoursBoldRed[8];
extern char ColoursGreen[8];
extern char ColoursBoldGreen[8];
extern char ColoursYellow[8];
extern char ColoursCyan[8];

/*----------------------------------------------------------------------
 * Now the headers for each of the available routines.
 *----------------------------------------------------------------------*/

/*----------------------------------------
 * FileUtils.c
 *----------------------------------------*/

void map_file(FileDes *f);
void unmap_file(FileDes *f);
void copy_file(FILE *outs, const char *infname, const char *path);
FileDes *MapFile(const char *filename, const char *path);
void UnmapFile(FileDes *f);
int IsNewerN(char *f1, char *f2);
int IsFile(char *f);
int ReadIntFromFile(char *fname);
void CreateDirectoryPath(char *pathname);

/*----------------------------------------
 * Curses.c
 *----------------------------------------*/

void StartCurses(void);
void StopCurses(void);
int  get_string(char *result, int y, int x, int maxlen, int up_down);

/*----------------------------------------
 * Colours.c
 *----------------------------------------*/

void clearscreen(void);
void black(void);
void red(void);
void blue(void);
void bold_blue(void);
void bold_red(void);
void green(void);
void bold_green(void);
void yellow(void);
void cyan(void);

/*----------------------------------------
 * Misc.c
 *----------------------------------------*/

int ishost(char *hname);
int topaz(void);
int mica(void);
int rock(void);
int strlastcmp(char *s1, char *s2);
int strfirstcmp(char *s1, char *s2);
void ReturnTime(int *year, int *month, int *day, int *hour, int *min, int *sec);
int DaysInMonth(int year, int month);
int DaysInYear(int year);
float DateAsFloat(int year, int month, int day);
void FloatAsDate(float proportion, int *year, int *month, int *day);
int DaysSinceFirstJan(int year, int month, int day);
int MonthsBetween(int y1, int m1, int y2, int m2);
int DaysBetween(int y1, int m1, int d1, int y2, int m2, int d2);
int DaysSinceSunday(int year, int month, int day);
int DaysSinceMonday(int year, int month, int day);
void AddDaysTo(int *Year, int *Month, int *Day, int Days);
int IsDate(int year, int month, int day);
char *DayNameLong(int year, int month, int day);
char *DayNameShort(int year, int month, int day);
int ToUTC(int Year, int Month, int Day, int Hour);
char *FirstSecondThird(int i);
int Minimum(int a, int b);
int RandomInt(int range_bottom, int range_top);

/*----------------------------------------
 * Images.c
 *----------------------------------------*/
