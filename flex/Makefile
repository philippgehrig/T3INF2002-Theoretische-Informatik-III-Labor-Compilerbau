LEX=flex
CC=gcc

all: s_scanner

scanner.o: scanner.c
	$(CC) -c scanner.c -o scanner.o

scanner.c: scanner.l
	$(LEX) -o scanner.c scanner.l

s_scanner: scanner.o
	$(CC) scanner.o -o s_scanner

clean:
	rm -f scanner.o scanner.c s_scanner