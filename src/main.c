#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <ncurses.h>


#include "logic.h"
#include "window.h"

#define MAX_CHARS 16

char tetrimino[7][16];

int nScreenWidth, nScreenHeight;

int nFieldWidth = 10;
int nFieldHeight = 40;
unsigned char *pField = NULL;

int main()
{
	// get the number of rows and columns and assigning them to nScreenHeight and nScreenWidth
	getmaxyx(stdscr, nScreenHeight, nScreenWidth);

	char *screen = malloc(sizeof(char)*nScreenWidth*nScreenHeight);
	
	for(int i = 0; i < nScreenWidth*nScreenHeight; i++)
		screen[i] = ' ';

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

	int nCurrentPiece = 0;
	int nCurrentRotation = 0;
	int nCurrentX = nFieldWidth / 2;
	int nCurrentY = 0;

	while(!bGameOver) {
		// GAME TIMING ======
		
		// INPUT
		
		// Draw Field

		// Draw Tetrimino

		for(int px = 0; px < 4; px++)
			for(int py = 0; py < 4; py++)
				if(tetrimino[nCurrentPiece][rotate(px, py, nCurrentRotation)] == 'X')
					pField[(nCurrentY + py + 2) * nScreenWidth + (nCurrentX + px + 2)] = nCurrentPiece + 65;


		addnstr(screen, nScreenHeight*nScreenWidth);
		/* 
		scr_Output(0, 0, "Hello\n");

		int ch;
		ch = getch();

		if(ch == KEY_DOWN)
			bGameOver = true;
		*/
	}

	endwin();

	free(pField);
	free(screen);

	return 0;
}


