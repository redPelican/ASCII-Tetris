CC = clang
CFLAGS = -std=c99 -Wall -g
CFLAGS += -Isrc/logic -Isrc/vector/include
LDFLAGS = -lncurses 

SRC = $(wildcard src/*.c) $(wildcard src/**/*.c) $(wildcard src/**/**/*.c)
OBJ = $(SRC:.c=.o)
BIN = bin

.PHONY: all

all: dirs tetris #libs

#libs:
#	cd lib/vector && make

dirs:
	mkdir -p ./$(BIN)

tetris: $(OBJ)
	$(CC) $< -o $(BIN)/$@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm -rf $(OBJ) $(BIN)


