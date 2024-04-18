#**********************************************
#*                                            *
#*     Project: pl1c	                      *
#*     Module:  Makefile                      *
#*                                            *
#*     (c) 2021 by Klaus Wieland              *
#*                                            *
#**********************************************

objects = parser.o scanner.o symTab.o synTree.o optimize.o generate.o
CC	= gcc
CFLAGS	=
LEX	= flex
YACC	= bison


all: pl1c

pl1c: $(objects)
	$(CC) -o $@ $^

parser.c:	parser.y
	$(YACC) -d $< -o $@

scanner.c:	scanner.l 
	$(LEX) -t $< > $@



symTab.o:	symTab.h
synTree.o:	synTree.h symTab.h
optimize.o:	optimize.h synTree.h symTab.h
generate.o:	generate.h synTree.h symTab.h
parser.o:	parser.h symTab.h synTree.h 
parser.h:	parser.y

clean:
	rm pl1c parser.c scanner.c parser.h $(objects)
