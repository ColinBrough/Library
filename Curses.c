/*----------------------------------------------------------------------
 *
 *	Curses.c	Various utility routines common when I am building
 *			a curses application.
 *
 *----------------------------------------------------------------------
 * $Id: Curses.c,v 1.1 1998/07/25 14:35:51 cmb Exp $
 *
 * $Log: Curses.c,v $
 * Revision 1.1  1998/07/25 14:35:51  cmb
 * Initial revision
 *
 *----------------------------------------------------------------------*/

#include <cmb.h>

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
		case '':
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
