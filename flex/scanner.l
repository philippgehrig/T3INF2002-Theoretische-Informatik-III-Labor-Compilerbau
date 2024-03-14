%option noyywrap

%{
  /* c decl*/
%}


DIGIT [0-9]
ID [a-zA-Z][a-zA-Z0-9_-]*
%%


"ALL"[ ]* {
    fprintf(stderr,"LEX: KEYWORD: %s\n", yytext);
}

"EXISTS"[ ]* {
    fprintf(stderr,"LEX: KEYWORD: %s\n", yytext);
}

"int" {
    fprintf(stderr,"LEX: KEYWORD: %s\n", yytext);
}

{DIGIT}+ {
    fprintf(stderr, "LEX: NUMBER: %s\n", yytext);
}

"DECLARE" {
    fprintf(stderr, "LEX: KEY: %s\n", yytext);
}
"PREDICATE" {
    fprintf(stderr,"LEX: KEY: %s\n", yytext);
}

"FUNCTION" {
    fprintf(stderr,"LEX: KEY: %s\n", yytext);
}

"VARIABLE" {
    fprintf(stderr,"LEX: KEY: %s\n", yytext);
}

":" {
    fprintf(stderr,"LEX: KEY: Colon\n");
}

"," {
    fprintf(stderr,"LEX: KEY: Comma\n");
}

";" {
    fprintf(stderr,"LEX: KEY: Semicolon\n");
}

"(" {
    fprintf(stderr,"LEX: KEY: Bracket open\n");
}

")" {
    fprintf(stderr,"LEX: KEY: Bracket close\n");
}

"[" {
    fprintf(stderr,"LEX: KEY: Square bracket open\n");
}

"]" {
    fprintf(stderr,"LEX: KEY: Square bracket close\n");
}

"<->" {
    fprintf(stderr,"LEX: KEY: %s\n", yytext);
}

"->" {
    fprintf(stderr,"LEX: KEY: %s\n", yytext);
}

"|" {
    fprintf(stderr,"LEX: KEY: OR\n");
} 

"&" {
    fprintf(stderr,"LEX: KEY: AND\n");
} 

"~" {
    fprintf(stderr,"LEX: KEY: NOT\n");
}

"/*"[^*]*"*"+([^*/][^*]*"*"+)*"/" {
    fprintf(stderr,"LEX: COMMENT: %s\n", yytext);
}

[ \t\n]+ /* Whitespaces */

{ID} {
    fprintf(stderr, "LEX: STRING: %s\n", yytext);
}

. {
    fprintf(stderr, "LEX: ERROR: %s\n", yytext);
}
%%

int main( int argc, char **argv ){
    ++argv, --argc;  /* skip over program name */
    if ( argc > 0 )
            yyin = fopen( argv[0], "r" );
    else
            yyin = stdin;
    yylex();
}