%option noyywrap

%{
  /* c decl*/
%}


DIGIT [0-9]
ID [a-zA-Z][a-zA-Z0-9_-]*
%%


"ALL" {
    fprintf(stderr,"LEX: KEYWORD: %s\n", yytext);
    return ALL;
}

"EXIST" {
    fprintf(stderr,"LEX: KEYWORD: %s\n", yytext);
    return EXIST;
}

"TRUE" {
    fprintf(stderr,"LEX: KEY: %s\n", yytext);
    return TRUE;
}
"FALSE" {
    fprintf(stderr,"LEX: KEY: %s\n", yytext);
    return FALSE;
}

"int" {
    fprintf(stderr,"LEX: KEYWORD: %s\n", yytext);
    return INT;
}

{DIGIT}+ {
    fprintf(stderr, "LEX: NUMBER: %s\n", yytext);
    yylval.val = atoi(yytext);
    return NUMBER;
}

"DECLARE" {
    fprintf(stderr, "LEX: KEY: %s\n", yytext);
    return DECLARE;
}
"PREDICATE" {
    fprintf(stderr,"LEX: KEY: %s\n", yytext);
    return PREDICATE;
}

"FUNCTION" {
    fprintf(stderr,"LEX: KEY: %s\n", yytext);
    return FUNCTION;
}

"VARIABLE" {
    fprintf(stderr,"LEX: KEY: %s\n", yytext);
    return VARIABLE;
}

":" {
    fprintf(stderr,"LEX: KEY: Colon\n");
    return COLON;
}

"," {
    fprintf(stderr,"LEX: KEY: Comma\n");
    return COMMA;
}

";" {
    fprintf(stderr,"LEX: KEY: Semicolon\n");
    return SEMICOLON;
}

"(" {
    fprintf(stderr,"LEX: KEY: Bracket open\n");
    return B_OPEN;
}

")" {
    fprintf(stderr,"LEX: KEY: Bracket close\n");
    return B_CLOSE;
}

"[" {
    fprintf(stderr,"LEX: KEY: Square bracket open\n");
    return SB_OPEN;
}

"]" {
    fprintf(stderr,"LEX: KEY: Square bracket close\n");
    return SB_CLOSE;
}

"<->" {
    fprintf(stderr,"LEX: KEY: %s\n", yytext);
    return EQUIVALENCE;
}

"->" {
    fprintf(stderr,"LEX: KEY: %s\n", yytext);
    return IMPLICATION;
}

"|" {
    fprintf(stderr,"LEX: KEY: OR\n");
    return OR;
} 

"&" {
    fprintf(stderr,"LEX: KEY: AND\n");
    return AND;
} 

"~" {
    fprintf(stderr,"LEX: KEY: NOT\n");
    return NOT;
}

"/*"[^*]*"*"+([^*/][^*]*"*"+)*"/" {
    fprintf(stderr,"LEX: COMMENT: %s\n", yytext);
}

[ \t\n]+ /* Whitespaces */

{ID} {
    fprintf(stderr, "LEX: STRING: %s\n", yytext);
    yylval.strval = yytext;
    // yyval.str = strdup(yytext); => dynamische Speicherallocation komplizierter
    return STRING;
}

. {
    fprintf(stderr, "LEX: ERROR: %s\n", yytext);
    return ERROR;
}
%%

int main( int argc, char **argv ){
    ++argv, --argc;  /* skip over program name */
    if ( argc > 0 )
            yyin = fopen( argv[0], "r" );
    else
            yyin = stdin;
    yyparse();
}