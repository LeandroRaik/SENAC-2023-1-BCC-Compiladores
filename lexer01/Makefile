CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99
EXEC = main
SRC = main.c
INPUT = input.txt

build: $(EXEC)

$(EXEC): $(SRC)
	$(CC) $(CFLAGS) -o $(EXEC) $(SRC)

run: $(EXEC)
	./$(EXEC) $(INPUT)

clean:
	rm -f $(EXEC)
