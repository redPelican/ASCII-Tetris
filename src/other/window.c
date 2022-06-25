#include <ncurses.h>
#include "window.h"

void scr_Setup() 
{
	initscr();	
	cbreak();
	keypad(stdscr, TRUE);
	noecho();
	nodelay(stdscr, TRUE);
}
