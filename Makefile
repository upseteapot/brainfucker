CC     := gcc
FLAGS  := -Wall -Wextra -pedantic -std=c11
TARGET := brainfucker

all: clean main

main: ./*.c
	$(CC) $(FLAGS) -o $(TARGET) -I./ $^

clean:
	rm -f brainfucker

