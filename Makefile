CC=gcc
CFLAGS=-O3 -std=c99
LIBS=-lm
OBJS=main.o startingsolution.o swap2opt.o genetic.o util.o

all: main

main: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)
clean:
	rm -f *.o
