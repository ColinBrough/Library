/*----------------------------------------------------------------------
 *
 *	cmb.h	Header file for the utility and convenience stuff
 *		handy to have available when I am programming my own
 *		C code.
 *
 *----------------------------------------------------------------------
 * $Id: cmb.h,v 1.9 1998/08/19 21:12:20 cmb Exp $
 *
 * $Log: cmb.h,v $
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

#include <stdio.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
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

/*----------------------------------------------------------------------
 * Some common ncurses defines, to save space in the application specific
 * header files.
 *----------------------------------------------------------------------*/

#define WHITE_ON_BLACK  0
#define BLACK_ON_WHITE  1
#define RED_ON_WHITE    2
#define BLUE_ON_WHITE   3
#define GREEN_ON_WHITE  4
#define YELLOW_ON_WHITE 5
#define MAGENTA_ON_WHITE 6
#define CYAN_ON_WHITE   7

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

/*----------------------------------------------------------------------
 * OK, so globals are bad form in a library, but handy...
 *----------------------------------------------------------------------*/

extern int inside_curses;       /* Flag indicating whether in curses    */
extern FILE *tfile;		/* Trace file				*/

/*----------------------------------------------------------------------
 * Now the headers for each of the available routines.
 *----------------------------------------------------------------------*/

/*----------------------------------------
 * FileUtils.c
 *----------------------------------------*/

void
map_file(FileDes *f);
void
unmap_file(FileDes *f);
void
copy_file(FILE *outs, const char *infname, ...);
FileDes *
MapFile(const char *filename, ...);
void
UnmapFile(FileDes *f);

/*----------------------------------------
 * Curses.c
 *----------------------------------------*/

int
get_string(char *result, int y, int x, int maxlen, int up_down);

/*----------------------------------------
 * Colours.c
 *----------------------------------------*/

void
black(void);
void
red(void);
void
blue(void);
void
bold_blue(void);
void
bold_red(void);
void
green(void);
void
bold_green(void);
void
yellow(void);
