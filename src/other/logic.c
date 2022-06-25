#include "logic.h"

#include <time.h>
#include <errno.h>

// Output the index of a piece in the tetrimino array
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

// sleep function
/*
int msleep(long msec)
{
    struct timespec ts;
    int res;

    if (msec < 0)
    {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return res;
}
*/