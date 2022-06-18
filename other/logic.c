#include <stdbool.h>

#include "logic.h"

int rotate(int px, int py, int r) 
{
	switch(r % 4) {
		case 0: return py * 4 + px; // 0 degrees
		case 1: return 12 + py - (px*4); // 90 degrees
		case 2: return 15 - (py*4) - px; // 180 degrees
		case 3: return 3 + py + (px*4); // 270 degrees
	}
	return 0;
}

// checks if a piece fits
bool doesFit(int nTetrimino, int nRotation, int nPosX, int nPosY, int nFieldWidth, int nFieldHeight, const char* tetrimino[], unsigned char* pField)
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