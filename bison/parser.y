%{
    /* C declarations */
%}

%union {
    int intval;
    char strval[101];
}



%start stmtseq


%token DECLARE
%token PREDICATE
%token FUNCTION
%token VARIABLE
%token INT
%token STRING
%token ERROR
%token NUMBER

%left COMMA
%left SEMICOLON
%left COLON
%left B_OPEN
%left B_CLOSE
%left SB_OPEN
%left SB_CLOSE
%left EQUIVALENT
%left IMPLIES
%left OR
%left AND
%left NOT
%left ALL
%left EXISTS
%left TRUE
%left FALSE


%%

declare: DECLARE PREDICATE STRING COLON NUMBER
    | DECLARE FUNCTION STRING COLON NUMBER
    | DECLARE VARIABLE STRING COLON INT

    ;

formel: NUM                             {  }
    | formel AND formel                 {  }
    | formel OR formel                  {  }
    | formel EQUIVALENT formel          {  }
    | formel IMPLIES formel             {  }
    | ALL SB_OPEN formel SB_CLOSE       {  }
    | EXISTS SB_OPEN formel SB_CLOSE    {  }
    | NOT formel                        {  }
    ;



%%

