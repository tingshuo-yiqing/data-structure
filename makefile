CC = gcc
CFLAGS = -Wall -Iinclude
OBJ = build/list.o

all: build/main build/test_list

build/main: src/main.c $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

build/test_list: tests/test_list.c $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

build/list.o: src/list.c include/list.h
	$(CC) $(CFLAGS) -c src/list.c -o $@

clean:
	rm -rf build/*
