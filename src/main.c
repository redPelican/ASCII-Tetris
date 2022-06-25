#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <time.h>

#include <ncurses.h>

#include "logic.h"
#include "window.h"

#define MAX_CHARS 16

char tetrimino[7][MAX_CHARS];

int nScreenWidth = 120;
int nScreenHeight = 36;

int nFieldWidth = 12;
int nFieldHeight = 21;

unsigned char *pField = NULL;


bool doesFit(int nTetrimino, int nRotation, int nPosX, int nPosY);

int main()
{
	// get the number of rows and columns and assigning them to nScreenHeight and nScreenWidth
	//getmaxyx(stdscr, nScreenHeight, nScreenWidth);

	// SETUP SCREEN ARRAY AND NCURSES
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
	pField = malloc(sizeof(unsigned char)*nFieldWidth*nFieldHeight);
	
	// assign 
	for(int x = 0; x < nFieldWidth; x++)
		for(int y = 0; y < nFieldHeight; y++)
			pField[y*nFieldWidth + x] = (x == 0 || x == nFieldWidth - 1 || y == nFieldHeight - 1) ? 9 : 0;

	
	int ch;
	
	bool bGameOver = false;

	int nCurrentPiece = 0;
	int nCurrentRotation = 0;
	int nCurrentX = nFieldWidth / 2;
	int nCurrentY = 0;

	struct timespec ts;

	int m_sleepTime = 50;

	ts.tv_sec = m_sleepTime / 1000;
    ts.tv_nsec = (m_sleepTime % 1000) * 1000000;


	while(!bGameOver) {
		// GAME TIMING ====== (Delta-Time)

		nanosleep(&ts, &ts);
		
		// INPUT
		ch = getch();
		
		// Movement

		// Right
		nCurrentX += (ch == KEY_RIGHT && doesFit(nCurrentPiece, nCurrentRotation, nCurrentX + 1, nCurrentY)) ? 1 : 0;
		// Left
		nCurrentX -= (ch == KEY_LEFT && doesFit(nCurrentPiece, nCurrentRotation, nCurrentX - 1, nCurrentY)) ? 1 : 0;	
		// Down	
		nCurrentY += (ch == KEY_DOWN && doesFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1)) ? 1 : 0;

		// Rotate				 ENTER
		nCurrentRotation += (ch == 10 && doesFit(nCurrentPiece, nCurrentRotation + 1, nCurrentX, nCurrentY)) ? 1 : 0;

		if(ch == 32)
			bGameOver = true; 

		// GAME LOGIC

		// OUTPUT
		
		// Draw Field
		for(int x = 0; x < nFieldWidth; x++)
			for(int y = 0; y < nFieldHeight; y++) {
				screen[(y + 2)*nScreenWidth + (x + 2)] = " ABCDEFG=#"[pField[y*nFieldWidth + x]];
			}

		// Draw Tetrimino
		for(int px = 0; px < 4; px++)
			for(int py = 0; py < 4; py++)
				if(tetrimino[nCurrentPiece][rotate(px, py, nCurrentRotation)] != '.') {
					screen[(nCurrentY + py + 2) * nScreenWidth + (nCurrentX + px + 2)] = nCurrentPiece + 65;
				}

		// Draw to Screen
		clear();
		addnstr(screen, nScreenHeight*nScreenWidth);

		refresh();
	}

	endwin();

	printf("x: %d, y: %d\n", nCurrentX, nCurrentY);
	printf("%s\n", screen);

	free(pField);
	free(screen);

	return 0;
}

// checks if a piece fits
bool doesFit(int nTetrimino, int nRotation, int nPosX, int nPosY)
{
	for(int px = 0; px < 4; ++px)
		for(int py = 0; py < 4; ++py) {
			// get index into piece
			int pi = rotate(px, py, nRotation);

			// get index into field
			int fi = (nPosY + py) * nFieldWidth + (nPosX + px);

			if(nPosX + px >= 0 && nPosX + px < nFieldWidth)
				if(nPosY + py >= 0 && nPosY + py < nFieldHeight)
					if(tetrimino[nTetrimino][pi] == 'X' && pField[fi] != 0) {
						return false;
					}
		}


	return true;
}
