/*----------------------------------------------------------------------
 *
 *	Misc.c		Miscellaneous utility routines
 *
 *----------------------------------------------------------------------
 * $Id: Misc.c,v 1.5 2003/06/03 12:52:20 cmb Exp $
 *
 * $Log: Misc.c,v $
 * Revision 1.5  2003/06/03 12:52:20  cmb
 * Updated to throw away fields if passed in NULL.
 *
 * Revision 1.4  2003/06/03 12:21:00  cmb
 * Added a routine to return the number of days in a given month
 *
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
    
    if (sec   != NULL) *sec   = T->tm_sec;
    if (min   != NULL) *min   = T->tm_min;
    if (hour  != NULL) *hour  = T->tm_hour;
    if (day   != NULL) *day   = T->tm_mday;
    if (month != NULL) *month = T->tm_mon + 1;
    if (year  != NULL) *year  = T->tm_year + 1900;
}

/*----------------------------------------------------------------------
 * DaysInMonth	Routine to return the number of days in a month, given
 *		month and year.
 *----------------------------------------------------------------------*/

int DaysInMonth(int year, int month)
{
    int days_in_month[]={ 0,31,28,31,30,31,30,31,31,30,31,30,31 };

    if ((month < 1) || (month > 12))
    {
	error("Month out of range: %d\n", month);
    }
    
    if ((year % 4 == 0) && !((year % 100 == 0) && (year % 400 != 0)))
    {
        days_in_month[2]++;	/* February has 29 days... */
    }
    return(days_in_month[month]);
}
