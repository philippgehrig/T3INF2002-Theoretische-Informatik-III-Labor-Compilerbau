%{
#include "parser.h"
int yyparse();
%}

%option noyywrap

ID [a-zA-Z][a-zA-Z0-9_]*

%%

"DECLARE" {
  printf( "LEX: Keyword: DECLARE\n");
  return DECLARE;
}
"PREDICATE" {
  printf( "LEX: Keyword: PREDICATE\n");
  return PREDICATE;
}
"FUNCTION" {
  printf( "LEX: Keyword: FUNCTION\n");
  return FUNCTION;
}
"VARIABLE" {
  printf( "LEX: Keyword: VARIABLE\n");
  return VARIABLE;
}
":" {
  printf( "LEX: Keyword :\n");
  return DD;
}
"int" {
  printf( "LEX: Keyword int\n");
  return INT;
}
"<->" {
  printf("LEX: Keyword EQUIVALENT\n");
  return EQUIVALENT;
}
"->" {
  printf("LEX: Keyword implication\n");
  return IMPLICATION;
}
"|" {
  printf("LEX: Keyword OR\n");
  return OR;
}
"&" {
  printf("LEX: Keyword AND\n");
  return AND;
}
"ALL" {
  printf("LEX: Keyword ALL\n");
  return ALL;
}
"EXIST" {
  printf( "LEX: Operator EXISTS\n");
  return EXIST;
}
"TRUE" {
  printf( "LEX: Keyword TRUE\n");
  return TRUE;
}
"FALSE" {
  printf( "LEX: Keyword FALSE\n");
  return FALSE;
}
"~" {
  printf( "LEX: Keyword negation %s\n", yytext );
  return NOT;
}
"[" {
  printf( "LEX: Keyword eckige Klammer auf %s\n", yytext );
  return B_O;
  }
"]" {
  printf( "LEX: Keyword eckige Klammer zu %s\n", yytext );
  return B_C;
}
"(" {
  printf( "LEX: Keyword runde Klammer auf %s\n", yytext );
  return R_B_O;
}
")" {
  printf( "LEX: Keyword runde Klammer zu %s\n", yytext );
  return R_B_C;
}
"/*".*"*/" {
  printf( "LEX: Comment %s\n", yytext );
}
";" {
  printf( "LEX: Keyword ;\n");
  return SEMICOLON;
}
"," {
  printf( "LEX: Keyword , \n");
  return COMMA;
}
{ID} {
  printf( "LEX: Identifier: %s\n", yytext );
  strcpy(yylval.val,yytext);
  return ID;
}  
[0-9]+ {
  printf("LEX: Digit: %s\n", yytext );
  yylval.number = atoi( yytext );
  return DIGIT;
}
[ \t\n\r] {

}
. {
  printf("LEX: Error: %s\n", yytext );
}

%%

int main( argc, argv )
int argc;
char **argv;
{
  ++argv, --argc;  /* skip over program name */
  if ( argc > 0 )
    yyin = fopen( argv[0], "r" );
  else
    yyin = stdin;
  //yylex();
  yyparse();
}