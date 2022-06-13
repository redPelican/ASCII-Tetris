#include <ncurses.h>
#include "window.h"

void scr_Setup() 
{
	initscr();	
	cbreak();
	keypad(stdscr, TRUE);
	noecho();
}

void scr_Output(int pos_X, int pos_Y, const char* cont)
{
	mvprintw(pos_X, pos_Y, cont);

	refresh();
}

