/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     EQUIVALENT = 258,
     IMPLICATION = 259,
     OR = 260,
     AND = 261,
     NOT = 262,
     B_C = 263,
     B_O = 264,
     EXIST = 265,
     ALL = 266,
     COMMA = 267,
     R_B_O = 268,
     R_B_C = 269,
     SEMICOLON = 270,
     TRUE = 271,
     FALSE = 272,
     ID = 273,
     DIGIT = 274,
     DECLARE = 275,
     PREDICATE = 276,
     FUNCTION = 277,
     VARIABLE = 278,
     DD = 279,
     INT = 280
   };
#endif
/* Tokens.  */
#define EQUIVALENT 258
#define IMPLICATION 259
#define OR 260
#define AND 261
#define NOT 262
#define B_C 263
#define B_O 264
#define EXIST 265
#define ALL 266
#define COMMA 267
#define R_B_O 268
#define R_B_C 269
#define SEMICOLON 270
#define TRUE 271
#define FALSE 272
#define ID 273
#define DIGIT 274
#define DECLARE 275
#define PREDICATE 276
#define FUNCTION 277
#define VARIABLE 278
#define DD 279
#define INT 280




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 12 "parser.y"
{
    char val [101];
	int number;
    int regno;
    struct node* node;
}
/* Line 1529 of yacc.c.  */
#line 106 "parser.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

