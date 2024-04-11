#**********************************************
#*                                            *
#*     Project: pl1c	                      *
#*     Module:  Makefile                      *
#*                                            *
#*     (c) 2021 by Klaus Wieland              *
#*                                            *
#**********************************************

objects = parser.o symTab.o synTree.o scanner.o generate.o
CC	= gcc
CFLAGS	= -O
LEX	= flex
YACC	= bison


all: pl1c

pl1c: $(objects)
	$(CC) -o $@ $^

parser.c:	parser.y
	$(YACC) -d $< -o $@

scanner.c:	scanner.l 
	$(LEX) -t $< > $@


scanner.o:	parser.h
symTab.o:	symTab.h
synTree.o:	synTree.h symTab.h
parser.o:	parser.h symTab.h synTree.h 
parser.h:	parser.y
generate.o: generate.h symTab.h synTree.h

clean:
	rm pl1c parser.c scanner.c parser.h $(objects)
