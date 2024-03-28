%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symTab.h"
#include "synTree.h"
#include "optimize.h"
#include "error.h"
int yylex(void);
void initialize();
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
        	printTree($<node>1,0);
            FILE *f = fopen("output.pl1", "w");
            if(f == NULL){
                printf("Error opening file!\n");
                exit(1);
            }
            $<node>1 = optimzeFormula($<node>1);
            writeOutputDeclare(f);
            fprintf(f, "\n");
            writeOutputFormula($<node>1,f);
            fprintf(f, ";\n");
        }
        ;

declarations:     DECLARE PREDICATE ID DD DIGIT { 
                    printf("PAR: Declare Predicate %s with %d\n", $<val>3, $<number>5);
                    char* val1 = $<val>3;
                    int val2 = $<number>5;
					insert_right(val1,Predicate,val2,NoType); 
					 printList();
                  }
                | DECLARE FUNCTION ID DD DIGIT { 
                    printf("PAR: Declare Function %s with %d\n", $<val>3, $<number>5);
					 insert_right($<val>3,Function,$<number>5,NoType);   
                    printList();

                  }

                | DECLARE VARIABLE ID DD INT { 
                    printf("PAR: Declare Variable %s with int \n", $<val>3);
					 insert_right($<val>3,Variable,0,Int); 
                    printList();
                  }
                ;

formula:      ID R_B_O term R_B_C { 
                    printf("PAR: %s\n", $<val>1); 
                    if((checkPredicate($<val>1))==1){
						tableEntry t = search_for($<val>1);
						$<node>$ = makePredicateNode(t,$<node>3);
                    }else {
                        printf("Syntax Error (Isn't predicate)");
                        exit(1);
			        }
				}
            | TRUE { 
				printf("PAR: True\n"); 
				$<node>$=makeTrueNode();
            }
            | FALSE { 
                printf("PAR: False\n"); 
                $<node>$=makeFalseNode();
            }
            | R_B_O formula R_B_C { 
                printf("PAR: ( )\n"); 
                $<node>$ = $<node>2;
            }
		    | NOT formula { 
                printf("PAR: ~\n"); 
                $<node>$ = makeNegationNode($<node>2);
            }
            | formula AND formula { 
                printf("PAR: AND\n"); 
                $<node>$ = makeConjunctionNode($<node>1,$<node>3);
            }
            | formula OR formula { 
				printf("PAR: OR\n"); 
                $<node>$ = makeDisjunctionNode($<node>1,$<node>3);
			}
            | formula EQUIVALENT formula { 
                printf("PAR: EQUIVALENT\n"); 
                $<node>$ = makeEquivalenceNode($<node>1,$<node>3);
            }
            | formula IMPLICATION formula { 
                printf("PAR: IMPLICATION\n"); 
                $<node>$ = makeImplicationNode($<node>1,$<node>3);
            }
            | ALL B_O ID B_C formula { 
                printf("PAR: ALL[%s]\n", $<val>3); 
                if((checkVariable($<val>3))==1){
                    tableEntry e = search_for($<val>3);
                    struct node* var = makeVariableNode(e);
                    $<node>$ = makeAllNode(var , $<node>5);
                }
                else{
                    printf("Ist't Variable");
                }
            }
            | EXIST B_O ID B_C formula { 
            printf("PAR: EXIST[%s]\n", $<val>3); 
            if((checkVariable($<val>3))==1){	
 					tableEntry e = search_for($<val>3);
                    struct node* var = makeVariableNode(e);
					printf("test: %s\n",var->variable_struct.tableEntry->identifier);
                    $<node>$ = makeExistNode(var , $<node>5);                
					}
                else{
                    printf("Ist't Variable");
                }
            }
            ;

term:     {
			printf("PAR: kein Argument\n");
			$<node>$=NULL;
		}
        | ID      {
			strcpy($<val>$,$<val>1); 
			printf("PAR: %s\n", $<val>1);
			if((checkFunction($<val>1))==1){
				tableEntry e = search_for($<val>1);
				if(e->arity != 0){
                    printf("Syntax Error (isn't arity=0)");
                    exit(1);
				}
				else{
                    struct node* node = makeFunctionNode(e, NULL);
					$<node>$ = makeArgumentNode(node);
				}
            }
			else if((checkVariable($<val>1))==1){
				tableEntry e = search_for($<val>1);
                struct node* node = makeVariableNode(e);
				$<node>$ = makeArgumentNode(node);
            }
			else {
				printf("Syntax Error (isn't Variable or Function)");
                exit(1);
			}
			
        }
        | DIGIT   {
            strcpy($<val>$,$<val>1); 
            printf("PAR: %d\n", $<number>1);
            struct node* num = makeNumberNode($<number>1);
			$<node>$ = makeArgumentNode(num);
        }
        | ID R_B_O term R_B_C { 
            printf("PAR: %s( )\n", $<val>1); 
			if((checkFunction($<val>1))==1){
				tableEntry e = search_for($<val>1);
                struct node* num = makeFunctionNode(e, $<node>3);
                $<node>$ = makeArgumentNode(num);
            }
			else{
				printf("Syntax Error (isn't Function)");
                exit(1);
			}
        }
        | term COMMA term { 
			printf("PAR: ,\n"); 
			$<node>$ = appendArgumentNode($<node>1,$<node>3);
		}
        ;

%%


/* int yyerror(char *s){
    printf("%s\n", s);
    exit(1);
}
 */

// int main(void)
//  {
// 	// init();
//  	return yyparse();
//  } 
