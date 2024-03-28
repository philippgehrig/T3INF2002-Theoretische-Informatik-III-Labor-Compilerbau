#**********************************************
#*                                            *
#*     Project: pl1c	                      *
#*     Module:  Makefile                      *
#*                                            *
#*     (c) 2021 by Klaus Wieland              *
#*                                            *
#**********************************************

objects = parser.o scanner.o symTab.o 
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


 
scanner.o:	  parser.h
symboltable.o:	  symTab.h
parser.o:	  parser.h symTab.h  
parser.h:	parser.y

clean:
	rm pl1c parser.c scanner.c parser.h $(objects)
