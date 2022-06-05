CC = clang
CFLAGS = -std=c99 -Wall 
LDFLAGS = -lncurses

SRC = $(wildcard *.c)

BIN = bin

bin: $(SRC)
	$(CC) $(CFLAGS) $^ -o $(BIN) $(LDFLAGS)
