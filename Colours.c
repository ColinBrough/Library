/*----------------------------------------------------------------------
 *
 *	Colours.c	A series of routines to set colours, for use in
 *			text output to stdout - ie, not inside curses.
 *
 *----------------------------------------------------------------------
 * $Id: Colours.c,v 1.4 2000/05/05 13:34:27 cmb Exp $
 *
 * $Log: Colours.c,v $
 * Revision 1.4  2000/05/05 13:34:27  cmb
 * Updated to add a clearscreen function.
 *
 * Revision 1.3  1999/08/17 12:25:16  cmb
 * Updated - added cyan, and reformatted.
 *
 * Revision 1.2  1998/08/19 21:13:33  cmb
 * Added include!
 *
 * Revision 1.1  1998/08/19 21:09:55  cmb
 * Initial revision
 *
 *----------------------------------------------------------------------*/

#include <cmb.h>

void clearscreen(void)
{
    /*------------------------------------------------------------------
     * This stuff resets clears the screen without going into curses.
     *------------------------------------------------------------------*/
    printf("%c%c%c%c%c%c%c", 27, '[', 'H', 27, '[', '2', 'J');
}

/*----------------------------------------------------------------------*/

void black(void)
{
    /*------------------------------------------------------------------
     * This stuff resets foreground and background to black and white
     * respectively - for use in xterms and on the console really....
     *------------------------------------------------------------------*/
    printf("%c%c%c%c%c", 27, '[', '0', '0', 'm');
}

/*----------------------------------------------------------------------*/

void red(void)
{
    printf("%c%c%c%c%c%c%c", 27, '[', '0', ';', '3', '1', 'm');
}

/*----------------------------------------------------------------------*/

void blue(void)
{
    printf("%c%c%c%c%c%c%c", 27, '[', '0', ';', '3', '4', 'm');
}

/*----------------------------------------------------------------------*/

void bold_blue(void)
{
    printf("%c%c%c%c%c%c%c", 27, '[', '3', '4', ';', '1', 'm');
}

/*----------------------------------------------------------------------*/

void bold_red(void)
{
    printf("%c%c%c%c%c%c%c", 27, '[', '3', '1', ';', '1', 'm');
}

/*----------------------------------------------------------------------*/

void green(void)
{
    printf("%c%c%c%c%c%c%c", 27, '[', '0', ';', '3', '2', 'm');
}

/*----------------------------------------------------------------------*/

void bold_green(void)
{
    printf("%c%c%c%c%c%c%c", 27, '[', '3', '2', ';', '1', 'm');
}

/*----------------------------------------------------------------------*/

void yellow(void)
{
    printf("%c%c%c%c%c%c%c", 27, '[', '0', ';', '3', '3', 'm');
}

/*----------------------------------------------------------------------*/

void cyan(void)
{
    printf("%c%c%c%c%c%c%c", 27, '[', '0', ';', '3', '6', 'm');
}
