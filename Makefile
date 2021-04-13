# -*- MakeFile -*-

CC=gcc
CFLAGS=-Wall

all: main

main: main.o args.o
	$(CC) $(CFLAGS) main.o args.o -o main

main.o: main.c args.h
	$(CC) $(CFLAGS) -c main.c

args.o: args.c args.h
	$(CC) $(CFLAGS) -c args.c

build: all

clean:
	rm -f *.o main
