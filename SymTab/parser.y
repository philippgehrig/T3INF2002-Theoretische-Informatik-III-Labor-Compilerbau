%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symTab.h"


int yylex(void);
void initialize();
int yyerror(char *s);
%}
%union {
    char val [101];
	int number;
    int regno;
    struct node* node;
}
%left   EQUIVALENT
%left   IMPLICATION
%left   OR
%left   AND
%left   NOT
%left   ALL     EXIST   B_O     B_C
%left  COMMA
%token  R_B_O   R_B_C
%token  SEMICOLON
%token  TRUE FALSE
%token  ID
%token  DIGIT
%token  DECLARE PREDICATE FUNCTION VARIABLE DD INT

%%

file:    
        | declarations file {

        }
        | formula SEMICOLON file {
            FILE *f = fopen("output.pl1", "w");
            if(f == NULL){
                printf("Error opening file!\n");
                exit(1);
            }
        }
        ;

declarations:     DECLARE PREDICATE ID DD DIGIT { 
                    printf("PARSER: Declare Predicate %s with %d\n", $<val>3, $<number>5);
					insert_right($<val>3,Predicate,$<number>5,NoType); 
					// printTable();
                  }
                | DECLARE FUNCTION ID DD DIGIT { 
                    printf("PARSER: Declare Function %s with %d\n", $<val>3, $<number>5);
                    insert_right($<val>3,Function,$<number>5,NoType); 
					 // printTable();
                  }

                | DECLARE VARIABLE ID DD INT { 
                    printf("PARSER: Declare Variable %s with int \n", $<val>3);
                    insert_right($<val>3,Variable,$<number>5,NoType); 
					// printTable();
                  }
                ;

formula:      ID R_B_O term R_B_C { 
                    printf("PARSER: %s\n", $<val>1); 
				}
            | TRUE { 
				printf("PARSER: True\n"); 
            }
            | FALSE { 
                printf("PARSER: False\n"); 
            }
            | R_B_O formula R_B_C { 
                printf("PARSER: ( )\n"); 
            }
		    | NOT formula { 
                printf("PARSER: ~\n"); 
            }
            | formula AND formula { 
                printf("PARSER: AND\n"); 
            }
            | formula OR formula { 
				printf("PARSER: OR\n"); 
			}
            | formula EQUIVALENT formula { 
                printf("PARSER: EQUIVALENT\n"); 
            }
            | formula IMPLICATION formula { 
                printf("PARSER: IMPLICATION\n"); 
            }
            | ALL B_O ID B_C formula { 
                printf("PARSER: ALL[%s]\n", $<val>3); 
            }
            | EXIST B_O ID B_C formula { 
            printf("PARSER: EXIST[%s]\n", $<val>3); 
            }
            ;

term:     {
			printf("PARSER: kein Argument\n");
		}
        | ID      {
			strcpy($<val>$,$<val>1); 
			printf("PARSER: %s\n", $<val>1);
			
        }
        | DIGIT   {
            strcpy($<val>$,$<val>1); 
            printf("PARSER: %d\n", $<number>1);
        }
        | ID R_B_O term R_B_C { 
            printf("PARSER: %s( )\n", $<val>1); 
        }
        | term COMMA term { 
			printf("PARSER: ,\n"); 
		}
        ;

%%


int yyerror(char *s){
    printf("%s\n", s);
    exit(1);
}


// int main(void)
//  {
// 	// init();
//  	return yyparse();
//  } 
