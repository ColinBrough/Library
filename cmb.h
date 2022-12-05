/*----------------------------------------------------------------------
 *
 *	cmb.h	Header file for the utility and convenience stuff
 *		handy to have available when I am programming my own
 *		C code.
 *
 *----------------------------------------------------------------------
 * $Id: cmb.h,v 1.2 1998/07/25 14:36:27 cmb Exp $
 *
 * $Log: cmb.h,v $
 * Revision 1.2  1998/07/25 14:36:27  cmb
 * Added another function header.
 *
 * Revision 1.1  1998/07/25 14:30:57  cmb
 * Initial revision
 *
 *----------------------------------------------------------------------*/

#include <stdio.h>
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
#include <ncurses.h>

#ifndef true
#define true     1
#endif
#ifndef false
#define false    0
#endif

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
copy_file(FILE *outs, char *infname);

/*----------------------------------------
 * Curses.c
 *----------------------------------------*/

int
get_string(char *result, int y, int x, int maxlen, int up_down);
