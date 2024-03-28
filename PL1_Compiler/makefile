objects = parser.o scanner.o symTab.o error.o synTree.o optimize.o
CC = gcc
LEX = flex
YACC = bison

all: pl1c
pl1c: $(objects)
		$(CC) -o $@ $^
parser.c: parser.y
		$(YACC) -d $< -o parser.c
scanner.c: scanner.l
		$(LEX) -t $< > $@

scanner.o : parser.c symTab.h error.h
parser.o : parser.h symTab.h error.h
symTab.o : symTab.h error.h
synTree.o : synTree.h symTab.h error.h
