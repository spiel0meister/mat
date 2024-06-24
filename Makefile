CFLAGS=-Wall -Wextra -ggdb

test: main.c mat.h
	gcc $(CFLAGS) -o $@ $^
