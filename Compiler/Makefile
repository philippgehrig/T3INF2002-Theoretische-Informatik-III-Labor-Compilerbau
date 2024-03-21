# MAKEFILE FOR FLEX TESTING

# CREATED BY: DINAR KARCHEVSKII 
LEX=flex
CC=gcc
YACC=bison

all: semantic_check

scanner.c: scanner.l parser.tab.h parser.tab.c
	$(LEX) -t scanner.l > scanner.c

parser.tab.c parser.tab.h: parser.y
	$(YACC) -d parser.y

scanner.o: scanner.c parser.tab.h
	$(CC) -c -o scanner.o scanner.c

parser.tab.o: parser.tab.c
	$(CC) -c -o parser.tab.o parser.tab.c

semantic_check: scanner.o parser.tab.o
	$(CC) scanner.o parser.tab.o -o semantic_check

clean:
	rm -f scanner.o parser.tab.o parser.tab.c parser.tab.h scanner.c semantic_check