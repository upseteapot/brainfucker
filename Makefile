CC     := gcc
FLAGS  := -Wall -Wextra -pedantic -std=c11
TARGET := brainfucker

all: clean main

main: ./src/*.c
	$(CC) $(FLAGS) -o $(TARGET) -Iinclude/ $^

clean:
	rm -f brainfucker
