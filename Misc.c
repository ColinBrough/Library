/*----------------------------------------------------------------------
 *
 *	Misc.c		Miscellaneous utility routines
 *
 *----------------------------------------------------------------------
 * $Id: Misc.c,v 1.3 2003/04/22 23:07:42 cmb Exp $
 *
 * $Log: Misc.c,v $
 * Revision 1.3  2003/04/22 23:07:42  cmb
 * Fixed typo
 *
 * Revision 1.2  2003/04/22 23:06:33  cmb
 * Updated.
 *
 * Revision 1.1  2000/05/09 20:24:00  cmb
 * Initial revision
 *
 *----------------------------------------------------------------------*/

#include "cmb.h"

/*----------------------------------------------------------------------
 * strlastcmp	Compare the ends of two strings
 *----------------------------------------------------------------------*/

int strlastcmp(char *s1, char *s2)
{
    int l1, l2;
    l1 = strlen(s1);
    l2 = strlen(s2);
    if (l1 < l2)
    {
        s2 = s2 + (l2 - l1);
    }
    else
    {
        s1 = s1 + (l1 - l2);
    }
    return(strcmp(s1, s2));
}

/*----------------------------------------------------------------------
 * ReturnTime	Routine to return the current date and time
 *----------------------------------------------------------------------*/

void ReturnTime(int *year, int *month, int *day, int *hour, int *min, int *sec)
{
    time_t t;
    struct tm *T;

    time( &t );
    T = localtime(&t);
    
    *sec   = T->tm_sec;
    *min   = T->tm_min;
    *hour  = T->tm_hour;
    *day   = T->tm_mday;
    *month = T->tm_mon + 1;
    *year  = T->tm_year + 1900;
}
