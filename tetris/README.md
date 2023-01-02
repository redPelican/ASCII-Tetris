# ASCII-Tetris
## using ncurses

A version of Tetris that runs in the terminal using ASCII characters. It is heavily based on [OneLoneCoder's C++ version](https://www.youtube.com/watch?v=8OK8_tHeCIA) as I followed his tutorial. However, my version is completely in C and should run on Mac and Linux.

---

### Compiling
The included Makefile should build the binary. Use `make` to build for Unix-like systems (Mac and Linux). Linux and Windows have not been tested.
Note: clang does need to be installed

### Prerequisites:
* A Unix-like OS
* the ncurses library
* clang

### Windows
You are welcome to try and compile to Windows :).

### Controls
* Left Arrow: Move piece left
* Up Arrow: Rotate piece
* Down Arrow: Force piece down
* Right Arrow: Move piece right
* Space Bar: quit game