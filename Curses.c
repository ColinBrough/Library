/*----------------------------------------------------------------------
 *
 *	Curses.c	Various utility routines common when I am building
 *			a curses application.
 *
 *----------------------------------------------------------------------
 * $Id: Curses.c,v 1.5 2008/08/19 19:37:28 cmb Exp $
 *
 * $Log: Curses.c,v $
 * Revision 1.5  2008/08/19 19:37:28  cmb
 * Made it able to use wider than 80 column terminals.
 *
 * Revision 1.4  2002/12/18 16:24:19  cmb
 * Updated.
 *
 * Revision 1.3  2002/12/04 22:40:17  cmb
 * Removed character constant that's changed on the new machine.
 *
 * Revision 1.2  1999/05/12 16:01:17  cmb
 * Updated to have more of the curses initialisation code "canned" here.
 *
 * Revision 1.1  1998/07/25 14:35:51  cmb
 * Initial revision
 *
 *----------------------------------------------------------------------*/

#include <cmb.h>

/*----------------------------------------------------------------------
 * StartCurses	Routine to do what I normally do when I am starting a
 *		curses application. If I want to do other initialisation,
 *		then I'll have to craft my own...
 *----------------------------------------------------------------------*/

void StartCurses(void)
{
    	/*--------------------------------------------------------------
	 * Now initialise the curses stuff... Yucky loads of error 
	 * handling!
	 *--------------------------------------------------------------*/

    if ((Screen = initscr()) == NULL)
    {
        error("Failed to initialise ncurses\n");
    }
    inside_curses = TRUE;
    if (raw() == ERR)
    {
        error("Failed to enter RAW mode\n");
    }
    if (noecho() == ERR)
    {
        error("Failed to enter NOECHO mode\n");
    }
    if (nonl() == ERR)
    {
        error("Failed to enter NONL mode\n");
    }
    if (cbreak() == ERR)
    {
        error("Failed to enter CBREAK mode\n");
    }
    
    if (keypad(Screen, TRUE) == ERR)
    {
        error("Failed to enter KEYPAD mode\n");
    }
    if (start_color() == ERR)
    {
        error("Failed to start up colour processing\n");
    }
    start_color();
    
    if ((LINES < 24) || (COLS < 80))
    {
        error("Illegal number of lines (%d) or columns (%d)\n", 
              LINES, COLS);
    }

    /*------------------------------------------------------------------
     * Now code to initialise the colour pairs to be used.
     *------------------------------------------------------------------*/

    if (init_pair(WHITE_ON_BLACK, COLOR_WHITE, COLOR_BLACK) == ERR)
    {
        error("Failed to initialise colour pair : WHITE_ON_BLACK\n");
    }
    if (init_pair(BLACK_ON_WHITE, COLOR_BLACK, COLOR_WHITE) == ERR)
    {
        error("Failed to initialise colour pair : BLACK_ON_WHITE\n");
    }
    if (init_pair(RED_ON_WHITE, COLOR_RED, COLOR_WHITE) == ERR)
    {
        error("Failed to initialise colour pair : RED_ON_WHITE\n");
    }
    if (init_pair(BLUE_ON_WHITE, COLOR_BLUE, COLOR_WHITE) == ERR)
    {
        error("Failed to initialise colour pair : BLUE_ON_WHITE\n");
    }
    if (init_pair(GREEN_ON_WHITE, COLOR_GREEN, COLOR_WHITE) == ERR)
    {
        error("Failed to initialise colour pair : GREEN_ON_WHITE\n");
    }
    if (init_pair(YELLOW_ON_WHITE, COLOR_YELLOW, COLOR_WHITE) == ERR)
    {
        error("Failed to initialise colour pair : YELLOW_ON_WHITE\n");
    }
    if (init_pair(MAGENTA_ON_WHITE, COLOR_MAGENTA, COLOR_WHITE) == ERR)
    {
        error("Failed to initialise colour pair : MAGENTA_ON_WHITE\n");
    }
    if (init_pair(CYAN_ON_WHITE, COLOR_CYAN, COLOR_WHITE) == ERR)
    {
        error("Failed to initialise colour pair : CYAN_ON_WHITE\n");
    }

    if (init_pair(RED_ON_BLACK, COLOR_RED, COLOR_BLACK) == ERR)
    {
        error("Failed to initialise colour pair : RED_ON_BLACK\n");
    }
    if (init_pair(BLUE_ON_BLACK, COLOR_BLUE, COLOR_BLACK) == ERR)
    {
        error("Failed to initialise colour pair : BLUE_ON_BLACK\n");
    }
    if (init_pair(GREEN_ON_BLACK, COLOR_GREEN, COLOR_BLACK) == ERR)
    {
        error("Failed to initialise colour pair : GREEN_ON_BLACK\n");
    }
    if (init_pair(YELLOW_ON_BLACK, COLOR_YELLOW, COLOR_BLACK) == ERR)
    {
        error("Failed to initialise colour pair : YELLOW_ON_BLACK\n");
    }
    if (init_pair(MAGENTA_ON_BLACK, COLOR_MAGENTA, COLOR_BLACK) == ERR)
    {
        error("Failed to initialise colour pair : MAGENTA_ON_BLACK\n");
    }
    if (init_pair(CYAN_ON_BLACK, COLOR_CYAN, COLOR_BLACK) == ERR)
    {
        error("Failed to initialise colour pair : CYAN_ON_BLACK\n");
    }
    attrset(A_NORMAL | COLOR_PAIR(BLACK_ON_WHITE));
}

/*----------------------------------------------------------------------
 * Routine to jump out of curses and reset things.
 *----------------------------------------------------------------------*/

void StopCurses(void)
{
    clear();
    refresh();
    endwin();
    inside_curses = FALSE;
    
    fputc(27,  stdout);		/* This stuff resets foreground and	*/
    fputc('[', stdout);		/* background to black and white	*/
    fputc('0', stdout);		/* respectively - for use in xterms	*/
    fputc('0', stdout);		/* and on the console really....	*/
    fputc('m', stdout);
}


/*----------------------------------------------------------------------
 * get_string	Get a string of text, doing my own editing!
 *		The string should be echoed at (x,y), and have maximum length
 *		maxlen. The 'up_down' flag indicates whether the up/down
 *		arrow keys are allowed as exit conditions. 
 *----------------------------------------------------------------------*/

int
get_string(char *result, int y, int x, int maxlen, int up_down)
{
	char *blank;
	int len, pos, ch, i, newpos;
	
	blank = (char *) malloc(maxlen);
	for (i = 0; i < (maxlen-1); i++) 
	{
		blank[i] = '_';
	}
	blank[maxlen-1] = '\0';
	len = strlen(result);
	newpos = 0;
	pos = 0;
	
	while (TRUE)
	{
		mvaddstr(y, x, blank);
		mvaddstr(y, x, result);
		move(y, x+pos);
		refresh();
		ch = getch();
	escape:
		switch (ch)
		{
		case '':
			ch = getch();
			switch (ch)
			{
			case 'd':
				/*--------------------------------------
				 * Delete a word forward. N.B. deliberate
				 * fall through - shares code with move
				 * forward a word...
				 *--------------------------------------*/
			case 'f':
				/* Forward a word ----------------------*/
				if (pos == len) break;
				if (result[pos] == ' ')
				{
					/* We are already over a space	*/
					i = pos;
					while (result[i] == ' ')
					{
						i++;
						if (i == len) break;
					}
					while (i < len)
					{
						if (result[i] == ' ')
						{
							newpos = i;
							break;
						}
						i++;
					}
					if (i == len) newpos = len;
				}
				else
				{
					i = pos;
					while (i < len)
					{
						if (result[i] == ' ')
						{
							newpos = i;
							break;
						}
						i++;
					}
					if (i == len) newpos = len;
				}
				if (ch == 'd')	/* Delete a word -------*/
				{
					if (pos == newpos) break;
					for (i = newpos; i < len; i++)
					{
						result[i - (newpos-pos)] =
							result[i];
					}
					for (i = 0; i < ((newpos-pos)+1); i++)
					{
						result[len-i] = '\0';
					}
					len -= (newpos - pos);
				}
				else		/* Forward a word ------*/
				{
					pos = newpos;
				}
				break;
			case 'b':
				/*--------------------------------------
				 * Move backward a word. N.B. deliberate
				 * fall through - shares code with delete
				 * a word backward...
				 *--------------------------------------*/
			case '':
				/* Delete a word backward --------------*/
				i = pos - 1;
				if (i < 0) break;
				if (i == 0)
				{
					newpos = 0;
					goto skip1;
				}
				if (result[i] == ' ')
				{
					/* We are already at start of word */
					while (result[i] == ' ')
					{
						i--;
						if (i < 0) break;
					}
					while (i > 0)
					{
						i--;
						if (result[i] == ' ')
						{
							newpos = i+1;
							break;
						}
					}
					if (i <= 0) newpos = 0;
				}
				else
				{
					while (i > 0)
					{
						i--;
						if (result[i] == ' ')
						{
							newpos = i+1;
							break;
						}
					}
					if (i == 0) newpos = 0;
				}
			skip1:
				if ((ch == 'b') || (pos == newpos))
				{
					pos = newpos;
					break;
				}
				for (i = pos; i < len; i++)
				{
					result[i - (pos-newpos)] = 
						result[i];
				}
				for (i = 0; i < ((pos-newpos)+1); i++)
				{
					result[len-i] = '\0';
				}
				len -= (pos-newpos);
				pos = newpos;
				break;
			default:
				/*--------------------------------------
				 * The escape was redundant, so goto the
				 * the switch for the outer loop.
				 *--------------------------------------*/
				goto escape;
			}
			break;
		case '':
			for (i = 0; i < maxlen; i++) result[i] = '\0';
			pos = 0;
			len = 0;
			break;
		case '':
			for (i = pos; i < maxlen; i++) result[i] = '\0';
			len = pos;
			break;
		case '':
			pos = 0;
			break;
		case '':
			pos = len;
			break;
		case '':
		case KEY_RIGHT:
			if (pos != len) pos++;
			break;
		case '':
		case KEY_LEFT:
			if (pos != 0) pos--;
			break;
		case KEY_UP:
			if (up_down)
			{
				free(blank);		/* -1 => pos==0	*/
				return((-pos)-1);	/* -2 => pos==1	*/
			}
			break;
		case KEY_DOWN:
			if (up_down)
			{
				free(blank);
				return(pos);
			}
			break;
		case '':
			if (pos == len) break;
			len--;
			for (i = pos; i < len; i++) result[i] = result[i+1];
			result[len] = '\0';
			break;
		case '':
		case KEY_BACKSPACE:
			if (pos == 0) break;
			pos--;
			len--;
			for (i = pos; i < len; i++) result[i] = result[i+1];
			result[len] = '\0';
			break;
			/*		case '':*/
		case KEY_ENTER:
			free(blank);
			return(maxlen+pos);	
		default:
			if ( (len == (maxlen-1)) || (ch < ' ') || (ch > 127))
			{
				break;
			}
			for (i = len; i > pos; i--) result[i] = result[i-1];
			result[pos] = ch;
			len++;
			pos++;
			break;
		}
	}
}
