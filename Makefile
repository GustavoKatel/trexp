CC = gcc

OBJS = regex.o

CFLAGS =

LIBS = -lncurses

all: $(OBJS) main.c
	$(CC) $(CFLAGS) main.c $(OBJS) -o main

debug: CFLAGS += -g
debug: all test

test: test.c regex.o
	$(CC) -g test.c $(OBJS) -o test

regex.o: regex.c regex.h
	$(CC) $(CFLAGS) -c regex.c -o regex.o

trexp: regex.o trexp.c
	$(CC) $(CFLAGS) trexp.c -o trexp $(LIBS) $(OBJS)

trexp/debug: debug trexp

clean:
	rm -f *.o
	rm main
	rm trexp
