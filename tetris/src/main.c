#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include <ncurses.h>

#include "logic.h"
#include "vector.h"

#define MAX_CHARS 16

char tetrimino[7][MAX_CHARS];

int nScreenWidth = 120;
int nScreenHeight = 36;

const int nFieldWidth = 12;
const int nFieldHeight = 21;

unsigned char *pField = NULL;


bool doesFit(int nTetrimino, int nRotation, int nPosX, int nPosY);
void scr_Setup();
void scr_Draw(char *output, int scrHeight, int scrWidth);

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

	int nCurrentPiece = 2;
	int nCurrentRotation = 0;
	int nCurrentX = nFieldWidth / 2;
	int nCurrentY = 0;

	bool bRotateHold = false;

    int nSpeed = 20;
    int nSpeedCounter = 0;

    bool bForceDown = false;

    //bool bKey[4];

    int nLines;
    int nScore;

    VECTOR_INIT(vLines);


	while(!bGameOver) {
		// GAME TIMING ====== (Delta-Time)
		msleep(50); // One game tick
		nSpeedCounter++;

		bForceDown = (nSpeed == nSpeedCounter);
		
		// INPUT
		ch = getch();

		/*
		for (int k = 0; k < 4; k++)
			bKey[k] = ch == 

		*/
		
		// Movement

		// Right
		nCurrentX += (ch == KEY_RIGHT && doesFit(nCurrentPiece, nCurrentRotation, nCurrentX + 1, nCurrentY)) ? 1 : 0;
		// Left
		nCurrentX -= (ch == KEY_LEFT && doesFit(nCurrentPiece, nCurrentRotation, nCurrentX - 1, nCurrentY)) ? 1 : 0;	
		// Down	
		nCurrentY += (ch == KEY_DOWN && doesFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1)) ? 1 : 0;

		// Rotate
		if (ch == KEY_UP) {
			nCurrentRotation += (!bRotateHold && doesFit(nCurrentPiece, nCurrentRotation + 1, nCurrentX, nCurrentY)) ? 1 : 0;
			bRotateHold = true;
		}
		else
			bRotateHold = false;
		

		if(ch == 32)
			bGameOver = true; 

		// GAME LOGIC

		// Force piece down
		if (bForceDown) {
			if (doesFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1))
				nCurrentY++;
			else {
				// Lock piece
				for(int px = 0; px < 4; px++)
					for(int py = 0; py < 4; py++)
						if(tetrimino[nCurrentPiece][rotate(px, py, nCurrentRotation)] == 'X') 
							pField[(nCurrentY + py) * nFieldWidth + (nCurrentX + px)] = nCurrentPiece + 1;

				// Check for lines
				for (int py = 0; py < 4; py++)
					if (nCurrentY + py < nFieldHeight - 1) {
						bool bLine = true;

						for (int px = 1; px < nFieldWidth - 1; px++) 
							bLine &= (pField[(nCurrentY + py) * nFieldWidth + px]) != 0;

						// set lines to =
						if (bLine) {
							for (int px = 1; px < nFieldWidth - 1; px++)
								pField[(nCurrentY + py) * nFieldWidth + px] = 8;
							vLines.pfVectorAdd(&vLines, nCurrentY + py); 

						}
					}

				// Choose and place next piece
				nCurrentX = nFieldWidth / 2; // reset x and y
				nCurrentY = 0;
				nCurrentRotation = 0; 
				nCurrentPiece = rand() % 7; // TODO: output true random numbers

				// Game over
				bGameOver = !doesFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1);
			}
			nSpeedCounter = 0;
		}

		// OUTPUT
		
		/* TODO: Add NES scoring system
				 more points for more line clears.
		*/

		// Draw Field
		for(int x = 0; x < nFieldWidth; x++)
			for(int y = 0; y < nFieldHeight; y++) {
				screen[(y + 2)*nScreenWidth + (x + 2)] = " ABCDEFG=#"[pField[y*nFieldWidth + x]];
			}

		// Draw Tetrimino
		for(int px = 0; px < 4; px++)
			for(int py = 0; py < 4; py++)
				if(tetrimino[nCurrentPiece][rotate(px, py, nCurrentRotation)] == 'X') {
					screen[(nCurrentY + py + 2) * nScreenWidth + (nCurrentX + px + 2)] = nCurrentPiece + 65;
				}

		// Animate Completed Line
		if (!vLines.pfVectorIsEmpty(&vLines)) {
			// Draw to screen
			scr_Draw(screen, nScreenHeight, nScreenWidth);

			msleep(4); // sleep for 400ms to delay

			for (int v = 0; v < vLines.pfVectorTotal(&vLines); v++) 
				for (int px = 1; px < nFieldWidth - 1; px++) {
					for (int py = v; py > 0; py--) {
						pField[py * nFieldWidth + px] = pField[(py - 1) * nFieldWidth + px];
						pField[px] = 0;
					}
				} 
			vLines.pfVectorFree(&vLines);
				
		}


		// Score


		// Draw to Screen
		scr_Draw(screen, nScreenHeight, nScreenWidth);
	}

	endwin();

	// deallocate memory
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

void scr_Setup() 
{
	initscr();	
	cbreak();
	keypad(stdscr, TRUE);
	noecho();
	nodelay(stdscr, TRUE);
}

void scr_Draw(char *output, int scrHeight, int scrWidth)
{
	clear();
	addnstr(output, scrHeight*scrWidth);
	refresh();
}
