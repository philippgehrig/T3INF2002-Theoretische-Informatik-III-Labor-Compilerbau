#**********************************************
#*                                            *
#*     Project: pl1c	                      *
#*     Module:  Makefile                      *
#*                                            *
#*     (c) 2021 by Klaus Wieland              *
#*                                            *
#**********************************************

objects = scanner.o
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


clean:
	rm pl1c parser.c scanner.c parser.h $(objects)
