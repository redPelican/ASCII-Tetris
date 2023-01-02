CC = clang
CFLAGS = -std=c99 -Wall -g
CFLAGS += -Iinclude

SRC = $(wildcard src/*.c)

$(SRC:.c=.o): $(SRC)
	$(CC) -c $(CFLAGS) $< -o $@

