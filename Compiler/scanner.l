%{
#include "parser.h"
int yyparse();
%}

%option noyywrap

ID [a-zA-Z][a-zA-Z0-9_]*

%%

"DECLARE" {
  fprintf(stderr, "LEX: Keyword: DECLARE\n");
  return DECLARE;
}
"PREDICATE" {
  fprintf(stderr, "LEX: Keyword: PREDICATE\n");
  return PREDICATE;
}
"FUNCTION" {
  fprintf(stderr, "LEX: Keyword: FUNCTION\n");
  return FUNCTION;
}
"VARIABLE" {
  fprintf(stderr, "LEX: Keyword: VARIABLE\n");
  return VARIABLE;
}
":" {
  fprintf(stderr, "LEX: Keyword :\n");
  return DD;
}
"int" {
  fprintf(stderr, "LEX: Keyword int\n");
  return INT;
}
"<->" {
  fprintf(stderr,"LEX: Keyword EQUIVALENT\n");
  return EQUIVALENT;
}
"->" {
  fprintf(stderr,"LEX: Keyword implication\n");
  return IMPLICATION;
}
"|" {
  fprintf(stderr,"LEX: Keyword OR\n");
  return OR;
}
"&" {
  fprintf(stderr,"LEX: Keyword AND\n");
  return AND;
}
"ALL" {
  fprintf(stderr,"LEX: Keyword ALL\n");
  return ALL;
}
"EXIST" {
  fprintf(stderr, "LEX: Operator EXISTS\n");
  return EXIST;
}
"TRUE" {
  fprintf(stderr, "LEX: Keyword TRUE\n");
  return TRUE;
}
"FALSE" {
  fprintf(stderr, "LEX: Keyword FALSE\n");
  return FALSE;
}
"~" {
  fprintf(stderr, "LEX: Keyword negation %s\n", yytext );
  return NOT;
}
"[" {
  fprintf(stderr, "LEX: Keyword eckige Klammer auf %s\n", yytext );
  return B_O;
  }
"]" {
  fprintf(stderr, "LEX: Keyword eckige Klammer zu %s\n", yytext );
  return B_C;
}
"(" {
  fprintf(stderr, "LEX: Keyword runde Klammer auf %s\n", yytext );
  return R_B_O;
}
")" {
  fprintf(stderr, "LEX: Keyword runde Klammer zu %s\n", yytext );
  return R_B_C;
}
"/*".*"*/" {
  fprintf(stderr, "LEX: Comment %s\n", yytext );
}
";" {
  fprintf(stderr, "LEX: Keyword ;\n");
  return SEMICOLON;
}
"," {
  fprintf(stderr, "LEX: Keyword , \n");
  return COMMA;
}
{ID} {
  fprintf(stderr, "LEX: Identifier: %s\n", yytext );
  strcpy(yylval.val,yytext);
  return ID;
}  
[0-9]+ {
  fprintf(stderr,"LEX: Digit: %s\n", yytext );
  yylval.number = atoi( yytext );
  return DIGIT;
}
[ \t\n\r] {

}
. {
  fprintf(stderr,"LEX: Error: %s\n", yytext );
}

%%

int main(int argc, char** argv)
{
  ++argv, --argc;  /* skip over program name */
  if ( argc > 0 )
    yyin = fopen( argv[0], "r" );
  else
    yyin = stdin;
  //yylex();
  yyparse();
}