CC = gcc

OBJS = regex.o

CFLAGS =

LIBS = -lncurses

all: $(OBJS) main.c
	$(CC) $(CFLAGS) main.c $(OBJS) -o main

debug: CFLAGS += -g
debug: all 

test: test.c regex.o
	$(CC) $(CFLAGS) test.c $(OBJS) -o test

regex.o: regex.c regex.h
	$(CC) $(CFLAGS) -c regex.c -o regex.o

trex: regex.o trex.c
	$(CC) $(CFLAGS) trex.c -o trex $(LIBS) $(OBJS)

trex/debug: debug trex

clean:
	rm -f *.o
	rm main
	rm trex
