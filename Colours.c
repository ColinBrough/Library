/*----------------------------------------------------------------------
 *
 *	Colours.c	A series of routines to set colours, for use in
 *			text output to stdout - ie, not inside curses.
 *
 *----------------------------------------------------------------------
 * $Id: Colours.c,v 1.5 2013/03/15 10:31:30 cmb Exp $
 *
 * $Log: Colours.c,v $
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

void ColoursInitialise(void)
{
    ColoursInitialised = TRUE;
    ColoursClearScr[0] = 27;
    ColoursClearScr[1] = '[';
    ColoursClearScr[2] = 'H';
    ColoursClearScr[3] = 27;
    ColoursClearScr[4] = '[';
    ColoursClearScr[5] = '2';
    ColoursClearScr[6] = 'J';
    ColoursClearScr[7] = '\0';
    ColoursBlack[0] = 27;
    ColoursBlack[1] = '[';
    ColoursBlack[2] = '0';
    ColoursBlack[3] = '0';
    ColoursBlack[4] = 'm';
    ColoursBlack[5] = '\0';
    ColoursRed[0] = 27;
    ColoursRed[1] = '[';
    ColoursRed[2] = '0';
    ColoursRed[3] = ';';
    ColoursRed[4] = '3';
    ColoursRed[5] = '1';
    ColoursRed[6] = 'm';
    ColoursRed[7] = '\0';
    ColoursBlue[0] = 27;
    ColoursBlue[1] = '[';
    ColoursBlue[2] = '0';
    ColoursBlue[3] = ';';
    ColoursBlue[4] = '3';
    ColoursBlue[5] = '4';
    ColoursBlue[6] = 'm';
    ColoursBlue[7] = '\0';
    ColoursBoldBlue[0] = 27;
    ColoursBoldBlue[1] = '[';
    ColoursBoldBlue[2] = '3';
    ColoursBoldBlue[3] = '4';
    ColoursBoldBlue[4] = ';';
    ColoursBoldBlue[5] = '1';
    ColoursBoldBlue[6] = 'm';
    ColoursBoldBlue[7] = '\0';
    ColoursBoldRed[0] = 27;
    ColoursBoldRed[1] = '[';
    ColoursBoldRed[2] = '3';
    ColoursBoldRed[3] = '1';
    ColoursBoldRed[4] = ';';
    ColoursBoldRed[5] = '1';
    ColoursBoldRed[6] = 'm';
    ColoursBoldRed[7] = '\0';
    ColoursGreen[0] = 27;
    ColoursGreen[1] = '[';
    ColoursGreen[2] = '0';
    ColoursGreen[3] = ';';
    ColoursGreen[4] = '3';
    ColoursGreen[5] = '2';
    ColoursGreen[6] = 'm';
    ColoursGreen[7] = '\0';
    ColoursBoldGreen[0] = 27;
    ColoursBoldGreen[1] = '[';
    ColoursBoldGreen[2] = '3';
    ColoursBoldGreen[3] = '2';
    ColoursBoldGreen[4] = ';';
    ColoursBoldGreen[5] = '1';
    ColoursBoldGreen[6] = 'm';
    ColoursBoldGreen[7] = '\0';
    ColoursYellow[0] = 27;
    ColoursYellow[1] = '[';
    ColoursYellow[2] = '0';
    ColoursYellow[3] = ';';
    ColoursYellow[4] = '3';
    ColoursYellow[5] = '3';
    ColoursYellow[6] = 'm';
    ColoursYellow[7] = '\0';
    ColoursCyan[0] = 27;
    ColoursCyan[1] = '[';
    ColoursCyan[2] = '0';
    ColoursCyan[3] = ';';
    ColoursCyan[4] = '3';
    ColoursCyan[5] = '6';
    ColoursCyan[6] = 'm';
    ColoursCyan[7] = '\0';
}

/*----------------------------------------------------------------------*/

void clearscreen(void)
{
    if (! ColoursInitialised) ColoursInitialise();
    /*------------------------------------------------------------------
     * This stuff resets clears the screen without going into curses.
     *------------------------------------------------------------------*/
    printf("%s", ColoursClearScr);
}

/*----------------------------------------------------------------------*/

void black(void)
{
    if (! ColoursInitialised) ColoursInitialise();
    /*------------------------------------------------------------------
     * This stuff resets foreground and background to black and white
     * respectively - for use in xterms and on the console really....
     *------------------------------------------------------------------*/
    printf("%s", ColoursBlack);
}

/*----------------------------------------------------------------------*/

void red(void)
{
    if (! ColoursInitialised) ColoursInitialise();
    printf("%s", ColoursRed);
}

/*----------------------------------------------------------------------*/

void blue(void)
{
    if (! ColoursInitialised) ColoursInitialise();
    printf("%s", ColoursBlue);
}

/*----------------------------------------------------------------------*/

void bold_blue(void)
{
    if (! ColoursInitialised) ColoursInitialise();
    printf("%s", ColoursBoldBlue);
}

/*----------------------------------------------------------------------*/

void bold_red(void)
{
    if (! ColoursInitialised) ColoursInitialise();
    printf("%s", ColoursBoldRed);
}

/*----------------------------------------------------------------------*/

void green(void)
{
    if (! ColoursInitialised) ColoursInitialise();
    printf("%s", ColoursGreen);
}

/*----------------------------------------------------------------------*/

void bold_green(void)
{
    if (! ColoursInitialised) ColoursInitialise();
    printf("%s", ColoursBoldGreen);
}

/*----------------------------------------------------------------------*/

void yellow(void)
{
    if (! ColoursInitialised) ColoursInitialise();
    printf("%s", ColoursYellow);
}

/*----------------------------------------------------------------------*/

void cyan(void)
{
    if (! ColoursInitialised) ColoursInitialise();
    printf("%s", ColoursCyan);
}
