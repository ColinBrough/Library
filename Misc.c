/*----------------------------------------------------------------------
 *
 *	Misc.c		Miscellaneous utility routines
 *
 *----------------------------------------------------------------------
 * $Id: Misc.c,v 1.25 2019/01/21 11:58:48 cmb Exp $
 *
 * $Log: Misc.c,v $
 * Revision 1.25  2019/01/21 11:58:48  cmb
 * Changed so routine just sets the internal value, doesn't return the
 * number.
 *
 * Revision 1.24  2019/01/21 11:56:20  cmb
 * Added code to produce a HostNumber
 *
 * Revision 1.23  2018/08/14 12:53:06  cmb
 * Added a routine to generate a random number between a top and a bottom
 * figure
 *
 * Revision 1.22  2018/06/06 12:20:49  cmb
 * Updated
 *
 * Revision 1.21  2018/02/20 15:39:43  cmb
 * Shifted base year to 1900, hopefully fixing a bug with DaysBetween and
 * MonthsBetween routines
 *
 * Revision 1.20  2018/02/20 15:34:32  cmb
 * Updated
 *
 * Revision 1.19  2015/05/21 12:10:26  cmb
 * Added routine to return the ordinal indicator as a string (1st, 2nd,
 * 3rd etc...)
 *
 * Revision 1.18  2015/05/21 11:54:39  cmb
 * Added routines to return the day of the week name of a given date
 *
 * Revision 1.17  2015/05/08 11:25:17  cmb
 * Added MonthsBetween function
 *
 * Revision 1.16  2014/12/22 15:09:36  cmb
 * Added code to compare the start of two strings (up to the length of
 * the shorter string).
 *
 * Revision 1.15  2013/09/19 11:46:57  cmb
 * Fixed typo bug
 *
 * Revision 1.14  2013/09/19 11:46:20  cmb
 * Updated
 *
 * Revision 1.13  2013/09/15 22:41:53  cmb
 * Updated
 *
 * Revision 1.12  2013/01/30 15:48:20  cmb
 * Added FloatAsDate - routine to convert a year.proportion of a year to
 * an approximate dd/mm/yyyy format...
 *
 * Revision 1.11  2012/08/23 20:20:03  cmb
 * Added extra date handling utility routines
 *
 * Revision 1.10  2008/10/21 21:10:31  cmb
 * Added routines to:
 *
 *  - calculate the number of days in a year
 *  - calculate the number of days since the first of January
 *  - calculate the number of days between two dates
 *
 * Revision 1.9  2007/09/12 21:34:43  cmb
 * Fixed a floating point/casting error
 *
 * Revision 1.8  2007/09/12 21:28:05  cmb
 * Updated
 *
 * Revision 1.7  2003/11/18 15:51:52  cmb
 * Fixed!
 *
 * Revision 1.6  2003/11/18 15:47:48  cmb
 * Updated
 *
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
 * gethostnumber	Routine to come up with a hostnumber from a 
 *			defined list of hosts my code knows about, so I
 *			sensibly index arrays by hostname...
 *----------------------------------------------------------------------*/

void gethostnumber()
{
    if (HostNumber != -1)
    {
	return;	/* Already set - do nothing */
    }
    if (strcmp(HostName, "NULL") == 0)
    {
	if (gethostname(HostName, 200) != 0)
	{
	    error("Failed to obtain hostname\n");
	}
    }
    if (strcmp(HostName, "rock") == 0)
    {
	HostNumber = HOST_ROCK;
    }
    else if (strcmp(HostName, "mica") == 0)
    {
	HostNumber = HOST_MICA;
    }
    else if (strcmp(HostName, "opal") == 0)
    {
	HostNumber = HOST_OPAL;
    }
    else if (strcmp(HostName, "agate") == 0)
    {
	HostNumber = HOST_AGATE;
    }
}

/*----------------------------------------------------------------------
 * ishost	Routine to tell whether this is the named host....
 *----------------------------------------------------------------------*/

int ishost(char *hname)
{
    gethostnumber();
    if (strcmp(HostName, hname) == 0)
    {
	return(true);
    }
    return(false);
}

/*----------------------------------------------------------------------
 * topaz	Routine to tell whether this is topaz....
 *----------------------------------------------------------------------*/

int topaz(void)
{
    return(ishost("topaz"));
}

/*----------------------------------------------------------------------
 * mica		Routine to tell whether this is mica....
 *----------------------------------------------------------------------*/

int mica(void)
{
    return(ishost("mica"));
}

/*----------------------------------------------------------------------
 * rock		Routine to tell whether this is rock....
 *----------------------------------------------------------------------*/

int rock(void)
{
    return(ishost("rock"));
}

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
 * strfirstcmp	Compare the start of two strings, up to length of shortest
 *----------------------------------------------------------------------*/

int strfirstcmp(char *s1, char *s2)
{
    int l;
    l = Minimum(strlen(s1), strlen(s2));
    return(strncmp(s1, s2, l));
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

/*----------------------------------------------------------------------
 * DaysInYear	Routine to return the number of days in a year, given
 *		the year.
 *----------------------------------------------------------------------*/

int DaysInYear(int year)
{
    if (DaysInMonth(year, 2) == 28)
    {
	return(365);
    }
    else
    {
	return(366);
    }
}

/*----------------------------------------------------------------------
 * DateAsFloat	Routine a date as a year.proportion of year...
 *----------------------------------------------------------------------*/

float DateAsFloat(int year, int month, int day)
{
    float y = (float) year;
    int i, days = 0, yeardays = 337;
    if (month > 1)
    {
	for (i = 1; i < month; i++)
	{
	    days += DaysInMonth(year, i);
	}
    }
    days += day;
    yeardays += DaysInMonth(year, 2);
    y =  y + ((float) days / (float) yeardays);
    return(y);
}

/*----------------------------------------------------------------------
 * FloatAsDate	Routine to convert a year.proportion of a year to an 
 *		approximate dd/mm/yyyy format...
 *----------------------------------------------------------------------*/

void FloatAsDate(float proportion, int *year, int *month, int *day)
{
    int DayInYear;
    
    *year = (int) floor(proportion);
    DayInYear = (int) floor(DaysInYear(*year) * ( proportion - floor(proportion) ) );
    *month = 1;
    while (DayInYear > DaysInMonth(*year, *month))
    {
	DayInYear -= DaysInMonth(*year, *month);
	(*month)++;
    }
    *day = DayInYear;
}

/*----------------------------------------------------------------------
 * DaysSinceFirstJan	Routine to compute the number of days since the 
 *			first of January in the same year
 *----------------------------------------------------------------------*/

int DaysSinceFirstJan(int year, int month, int day)
{
    int i = 1, total = 0;

    while (i < month)
    {
	total += DaysInMonth(year, i);
	i++;
    }
    total += day;
    total--;
    return(total);
}

/*----------------------------------------------------------------------
 * MonthsBetween	Routine to compute the number of days between
 *			two months
 *----------------------------------------------------------------------*/

int MonthsBetween(int y1, int m1, int y2, int m2)
{
    int Months1, Months2;
    Months1 = 12 * (y1 - 1900) + m1;
    Months2 = 12 * (y2 - 1900) + m2;
    return(Months1 - Months2);
}

/*----------------------------------------------------------------------
 * DaysBetween	Routine to compute the number of days between two dates
 *----------------------------------------------------------------------*/

int DaysBetween(int y1, int m1, int d1, int y2, int m2, int d2)
{
    int i, days1, days2;
    if (Minimum(y1, y2) < 1900) /* Used to be set to 1970 - not sure if reducing it makes problems */
    {
	error("Date out of range: %d/%d/%d or %d/%d/%d\n", d1,m1,y1,d2,m2,y2);
    }
    days1 = DaysSinceFirstJan(y1,m1,d1);
    i = y1 - 1;
    while (i >= 1900)
    {
	days1 += DaysInYear(i);
	i--;
    }

    days2 = DaysSinceFirstJan(y2,m2,d2);
    i = y2 - 1;
    while (i >= 1900)
    {
	days2 += DaysInYear(i);
	i--;
    }
    
    return(days1 - days2);
}

/*----------------------------------------------------------------------
 * DaysSinceSunday	Routine to return the number of days (0..6) 
 *			since Sunday, given the  input date.
 *----------------------------------------------------------------------*/

int DaysSinceSunday(int year, int month, int day)
{
    struct tm T;

    T.tm_sec = 0;
    T.tm_min = 0;
    T.tm_hour = 9;
    T.tm_mday = day;
    T.tm_mon  = month - 1;
    T.tm_year = year - 1900;
    T.tm_isdst = 0;
    
    mktime( &T );
    
    return(T.tm_wday);
}

/*----------------------------------------------------------------------
 * DaysSinceMonday	Routine to return the number of days (0..6) 
 *			since Monday, given the  input date.
 *----------------------------------------------------------------------*/

int DaysSinceMonday(int year, int month, int day)
{
    int d;
    d = DaysSinceSunday(year, month, day);
    d--;
    if (d < 0)
    {
	d = 6;
    }
    return(d);
}

/*----------------------------------------------------------------------
 * AddDaysTo	Calculate the date resulting from adding XX days to a
 *		given date...
 *----------------------------------------------------------------------*/

void AddDaysTo(int *Year, int *Month, int *Day, int Days)
{
    int i;
    if (abs(Days) == Days)	/* Its positive */
    {
	for (i = 0; i < Days; i++)
	{
	    (*Day)++;
	    if (*Day > DaysInMonth(*Year, *Month))
	    {
		*Day = 1;
		(*Month)++;
		if (*Month > 12)
		{
		    *Month = 1;
		    (*Year)++;
		}
	    }
	}
    }
    else			/* Its negative */
    {
	for (i = 0; i < abs(Days); i++)
	{
	    (*Day)--;
	    if (*Day < 1)
	    {
		(*Month)--;
		if (*Month < 1)
		{
		    *Month = 12;
		    (*Year)--;
		}
		*Day = DaysInMonth(*Year, *Month);
	    }
	}
    }
}

/*----------------------------------------------------------------------
 * IsDate	Rough validity checker for a date
 *----------------------------------------------------------------------*/

int IsDate(int year, int month, int day)
{
    if ((year < 1900) || (year > 2099))
    {
	return(FALSE);
    }
    if ((month < 1) || (month > 12))
    {
	return(FALSE);
    }
    if ((day < 1) || (day > DaysInMonth(year,month)))
    {
	return(FALSE);
    }
    return(TRUE);
}

/*----------------------------------------------------------------------
 * DayNameLong		Return pointer to the string name for the day of
 *			the week for a date
 *----------------------------------------------------------------------*/

char *DayNameLong(int year, int month, int day)
{
    return(WeekNamesLong[DaysSinceSunday(year, month, day)]);
}

/*----------------------------------------------------------------------
 * DayNameShort		Return pointer to the short, 3-letter string name
 *			for the day of the week for a date
 *----------------------------------------------------------------------*/

char *DayNameShort(int year, int month, int day)
{
    return(WeekNamesShort[DaysSinceSunday(year, month, day)]);
}

/*----------------------------------------------------------------------
 * ToUTC	Convert an hour to the equivalent UTC hour, taking 
 *		cognisance of BST...
 *----------------------------------------------------------------------*/

int ToUTC(int Year, int Month, int Day, int Hour)
{
    int IsSummer = false;
    int mstart, mend, dstart, dend;
    
    int SummerTime[40][4] = { { 27, 3, 30, 10 }, /* 2016 */
			      { 26, 3, 29, 10 }, /* 2017 */
			      { 25, 3, 28, 10 }, /* 2018 */
			      { 31, 3, 27, 10 }, /* 2019 */
			      { 29, 3, 25, 10 }, /* 2020 */
			      { 28, 3, 31, 10 }, /* 2021 */
			      { 27, 3, 30, 10 }, /* 2022 */
			      { 26, 3, 29, 10 }, /* 2023 */
			      { 31, 3, 27, 10 }, /* 2024 */
			      { 30, 3, 26, 10 }, /* 2025 */
			      { 29, 3, 25, 10 }, /* 2026 */
			      { 28, 3, 31, 10 }, /* 2027 */
			      { 26, 3, 29, 10 }, /* 2028 */
			      { 25, 3, 28, 10 }, /* 2029 */
			      { 31, 3, 27, 10 }, /* 2030 */
			      {  0, 3,  0, 10 }, /* 2031; not yet specified */
			      {  0, 3,  0, 10 }, /* 2032; not yet specified */
			      {  0, 3,  0, 10 }, /* 2033; not yet specified */
			      {  0, 3,  0, 10 }, /* 2034; not yet specified */
			      {  0, 3,  0, 10 }, /* 2035; not yet specified */
			      {  0, 3,  0, 10 }, /* 2036; not yet specified */
			      {  0, 3,  0, 10 }, /* 2037; not yet specified */
			      {  0, 3,  0, 10 }, /* 2038; not yet specified */
			      {  0, 3,  0, 10 }, /* 2039; not yet specified */
			      {  0, 3,  0, 10 }, /* 2040; not yet specified */
			      {  0, 3,  0, 10 }, /* 2041; not yet specified */
			      {  0, 3,  0, 10 }, /* 2042; not yet specified */
			      {  0, 3,  0, 10 }, /* 2043; not yet specified */
			      {  0, 3,  0, 10 }, /* 2044; not yet specified */
			      {  0, 3,  0, 10 }, /* 2045; not yet specified */
			      {  0, 3,  0, 10 }, /* 2046; not yet specified */
			      {  0, 3,  0, 10 }, /* 2047; not yet specified */
			      {  0, 3,  0, 10 }, /* 2048; not yet specified */
			      {  0, 3,  0, 10 }, /* 2049; not yet specified */
			      {  0, 3,  0, 10 }, /* 2050; not yet specified */
			      {  0, 3,  0, 10 }, /* 2051; not yet specified */
			      {  0, 3,  0, 10 }, /* 2052; not yet specified */
			      {  0, 3,  0, 10 }, /* 2053; not yet specified */
			      {  0, 3,  0, 10 }, /* 2054; not yet specified */
			      {  0, 3,  0, 10 }  /* 2055; not yet specified */
    };
    dstart = SummerTime[ Year - 2016 ][ 0 ];
    mstart = SummerTime[ Year - 2016 ][ 1 ];
    dend   = SummerTime[ Year - 2016 ][ 2 ];
    mend   = SummerTime[ Year - 2016 ][ 3 ];
    if (dstart == 0)
    {
	error("BST dates haven't been specified in the code yet for %d...\n", Year);
    }
    
    if ((DaysBetween(Year, Month, Day, Year, mstart, dstart) >= 0) &&
	(DaysBetween(Year, Month, Day, Year, mend,   dend)   <  0))
    {
	IsSummer = true;
    }
    
    if (IsSummer)
    {
	Hour--;
    }
    return(Hour);
}

/*----------------------------------------------------------------------
 * FirstSecondThird	Return suffix to numeric when written out for "1st", "2nd", "3rd"
 *----------------------------------------------------------------------*/

char *FirstSecondThird(int i)
{
    if ( ((i % 10) == 1) && (i != 11) )
    {
	return("st");
    }
    if ( ((i % 10) == 2) && (i != 12) )
    {
	return("nd");
    }
    if ( ((i % 10) == 3) && (i != 13) )
    {
	return("rd");
    }
    return("th");
}

/*----------------------------------------------------------------------
 * Minimum	Routine to return the smaller of two integers
 *----------------------------------------------------------------------*/

int Minimum(int a, int b)
{
    return((a < b) ? a : b);
}

/*----------------------------------------------------------------------
 * RandomInt	Routine to generate a random integer within a given range
 *----------------------------------------------------------------------*/

int RandomInt(int range_bottom, int range_top)
{
    int range_length, r, result;
    time_t t;

    t = time(NULL);
    srand(t);
    r = rand();

    if ((range_top < range_bottom) ||
	(range_top < 1) ||
	(range_bottom < 0))
    {
	error("Can't generate a random integer in that range (%d ... %d)\n", range_bottom,range_top);
    }
    range_length = range_top - range_bottom;
    result = (int) rint((((float) r / (float) RAND_MAX) * (float) range_length)
                        + (float) range_bottom);
    if (result == range_top) result = range_bottom;
    return(result);
}

/*----------------------------------------------------------------------*/
