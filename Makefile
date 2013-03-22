CC = gcc

OBJS = regex.o

CFLAGS = 

all: $(OBJS) main.c
	$(CC) main.c $(CFLAGS) $(OBJS) -o main

debug: CFLAGS += -g
debug: all 

regex.o: regex.c regex.h
	$(CC) $(CFLAGS) -c regex.c -o regex.o

clean:
	rm -f *.o
	rm main
