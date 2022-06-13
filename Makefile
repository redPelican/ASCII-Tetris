CC = clang
CFLAGS = -std=c99 -Wall -Isrc/other
LDFLAGS = -lncurses 

SRC = $(wildcard src/*.c) $(wildcard src/**/*.c)

BIN = bin

bin: $(SRC)
	$(CC) $(CFLAGS) $^ -o $(BIN) $(LDFLAGS)
