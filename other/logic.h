#ifndef _LOGIC_H
#define _LOGIC_H

int rotate(int px, int py, int r);

bool doesFit(int nTetrimino, int nRotation, int nPosX, int nPosY, int nFieldWidth, int nFieldHeight, const char* tetrimino[], unsigned char* pField);

#endif
