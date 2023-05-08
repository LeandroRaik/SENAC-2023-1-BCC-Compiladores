CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99

build: lexer.c
	$(CC) $(CFLAGS) -o lexer lexer.c

.PHONY: clean
clean:
	rm -f lexer