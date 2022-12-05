/*----------------------------------------------------------------------
 *
 *	Colours.c	A series of routines to set colours, for use in
 *			text output to stdout - ie, not inside curses.
 *
 *----------------------------------------------------------------------
 * $Id: Colours.c,v 1.6 2013/03/18 12:05:14 cmb Exp $
 *
 * $Log: Colours.c,v $
 * Revision 1.6  2013/03/18 12:05:14  cmb
 * Updated
 *
 * Revision 1.5  2013/03/15 10:31:30  cmb
 * Updated to use strings, so can be accessed either through a function
 * interface, or by including the relevant strings in printf statements
 * to change the colours...
 *
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

/*----------------------------------------------------------------------*/

void clearscreen(void)
{
    /*------------------------------------------------------------------
     * This stuff resets clears the screen without going into curses.
     *------------------------------------------------------------------*/
    printf("%s", ColoursClearScr);
}

/*----------------------------------------------------------------------*/

void black(void)
{
    /*------------------------------------------------------------------
     * This stuff resets foreground and background to black and white
     * respectively - for use in xterms and on the console really....
     *------------------------------------------------------------------*/
    printf("%s", ColoursBlack);
}

/*----------------------------------------------------------------------*/

void red(void)
{
    printf("%s", ColoursRed);
}

/*----------------------------------------------------------------------*/

void blue(void)
{
    printf("%s", ColoursBlue);
}

/*----------------------------------------------------------------------*/

void bold_blue(void)
{
    printf("%s", ColoursBoldBlue);
}

/*----------------------------------------------------------------------*/

void bold_red(void)
{
    printf("%s", ColoursBoldRed);
}

/*----------------------------------------------------------------------*/

void green(void)
{
    printf("%s", ColoursGreen);
}

/*----------------------------------------------------------------------*/

void bold_green(void)
{
    printf("%s", ColoursBoldGreen);
}

/*----------------------------------------------------------------------*/

void yellow(void)
{
    printf("%s", ColoursYellow);
}

/*----------------------------------------------------------------------*/

void cyan(void)
{
    printf("%s", ColoursCyan);
}
