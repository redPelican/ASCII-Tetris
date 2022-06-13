#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <ncurses.h>


#include "logic.h"
#include "window.h"

#define MAX_CHARS 16

char tetrimino[7][16];

int nFieldWidth = 10;
int nFieldHeight = 40;
unsigned char *pField = NULL;

int main()
{
	scr_Setup();

	// I Piece
	strncpy(tetrimino[0], "..X...X...X...X.", MAX_CHARS);	
	
	// O Piece
	strncpy(tetrimino[1], ".....XX..XX.....", MAX_CHARS);	
	
	// S Piece	
	strncpy(tetrimino[2], ".X...XX...X.....", MAX_CHARS);	

	// Z Piece
	strncpy(tetrimino[3], "..X..XX..X......", MAX_CHARS);
	
	// T Piece
	strncpy(tetrimino[4], "..X..XX...X.....", MAX_CHARS);
	
	// J Piece	
	strncpy(tetrimino[5], ".....XX..X...X..", MAX_CHARS);

	// L Piece
	strncpy(tetrimino[6], ".....XX...X...X.", MAX_CHARS);
	
	// allocate memory for the playing field
	pField = malloc(sizeof(unsigned char)*(nFieldWidth*nFieldHeight));
	for(int x = 0; x < nFieldWidth; x++)
		for(int y = 0; y < nFieldHeight; y++)
			pField[y*nFieldWidth + x] = (x == 0 || x == nFieldWidth - 1 || y == nFieldHeight - 1) ? 9 : 0;

	bool bGameOver = false;
	while(!bGameOver) {
		// GAME TIMING ======
		
		// INPUT
		
		// Draw Field


		// 
		scr_Output(0, 0, "Hello\n");

		int ch;
		ch = getch();

		if(ch == KEY_DOWN)
			bGameOver = true;
	}

	free(pField);

	return 0;
}


