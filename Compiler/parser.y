%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symTab.h"
#include "synTree.h"
#include "generate.h"
#include "optimize.h"

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
%token SEMICOLON
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

            printSymTab();
            printf("\n");
            $<node>1 = optimizeFormula($<node>1);
            generate($<node>1);
            printf(";\n");
        };

declarations:     DECLARE PREDICATE ID DD DIGIT { 
                    fprintf(stderr,"PARSER: Declare Predicate %s with %d\n", $<val>3, $<number>5);
					insert_right($<val>3,Predicate,$<number>5,NoType); 
                    printSymTabService();
                  }
                | DECLARE FUNCTION ID DD DIGIT { 
                    fprintf(stderr,"PARSER: Declare Function %s with %d\n", $<val>3, $<number>5);
                    insert_right($<val>3,Function,$<number>5,NoType);
                    printSymTabService();
                  }

                | DECLARE VARIABLE ID DD INT { 
                    fprintf(stderr,"PARSER: Declare Variable %s with int \n", $<val>3);
                    insert_right($<val>3,Variable,$<number>5,NoType);
                    printSymTabService(); 
                  };

formula:      ID R_B_O term R_B_C { 
                    fprintf(stderr,"PARSER: %s\n", $<val>1);
                    if((checkPredicate($<val>1))==1){
						tableEntry t = search_for($<val>1);
						$<node>$ = makePredicateNode(t,$<node>3);
                    }else {
                        fprintf(stderr,"Syntax Error (Isn't predicate)");
                        exit(1);
			        } 
				}
            | TRUE { 
				fprintf(stderr,"PARSER: True\n");
                $<node>$=makeTrueNode(); 
            }
            | FALSE { 
                fprintf(stderr,"PARSER: False\n");
                $<node>$=makeFalseNode(); 
            }
            | R_B_O formula R_B_C { 
                fprintf(stderr,"PARSER: ( )\n"); 
                $<node>$ = $<node>2;
            }
		    | NOT formula { 
                fprintf(stderr,"PARSER: ~\n"); 
                $<node>$ = makeNegationNode($<node>2);
            }
            | formula AND formula { 
                fprintf(stderr,"PARSER: AND\n");
                $<node>$ = makeConjunctionNode($<node>1,$<node>3); 
            }
            | formula OR formula { 
				fprintf(stderr,"PARSER: OR\n");
                $<node>$ = makeDisjunctionNode($<node>1,$<node>3); 
			}
            | formula EQUIVALENT formula { 
                fprintf(stderr,"PARSER: EQUIVALENT\n"); 
                $<node>$ = makeEquivalenceNode($<node>1,$<node>3);
            }
            | formula IMPLICATION formula { 
                fprintf(stderr,"PARSER: IMPLICATION\n");
                $<node>$ = makeImplicationNode($<node>1,$<node>3); 
            }
            | ALL B_O ID B_C formula { 
                fprintf(stderr,"PARSER: ALL[%s]\n", $<val>3);
                if((checkVariable($<val>3))==1){
                    tableEntry e = search_for($<val>3);
                    struct node* var = makeVariableNode(e);
                    $<node>$ = makeAllNode(var , $<node>5);
                }
                else{
                    fprintf(stderr,"Ist't Variable");
                } 
            }
            | EXIST B_O ID B_C formula { 
            fprintf(stderr,"PARSER: EXIST[%s]\n", $<val>3);
            if((checkVariable($<val>3))==1){	
 					tableEntry e = search_for($<val>3);
                    struct node* var = makeVariableNode(e);
					fprintf(stderr,"test: %s\n",var->synTree.variable_struct.tableEntry->identifier);
                    $<node>$ = makeExistNode(var , $<node>5);                
					}
                else{
                    fprintf(stderr,"Ist't Variable");
                } 
            };

term:     {
			fprintf(stderr,"PARSER: kein Argument\n");
            $<node>$=NULL;
		}
        | ID      {
			strcpy($<val>$,$<val>1); 
			fprintf(stderr,"PARSER: %s\n", $<val>1);
            if((checkFunction($<val>1))==1){
				tableEntry e = search_for($<val>1);
				if(e->arity != 0){
                    fprintf(stderr,"Syntax Error (isn't arity=0)");
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
				fprintf(stderr,"Syntax Error (isn't Variable or Function)");
                exit(1);
			}
			
        }
        | DIGIT   {
            strcpy($<val>$,$<val>1); 
            fprintf(stderr,"PARSER: %d\n", $<number>1);
            struct node* num = makeNumberNode($<number>1);
			$<node>$ = makeArgumentNode(num);
        }
        | ID R_B_O term R_B_C { 
            fprintf(stderr,"PARSER: %s( )\n", $<val>1);
            if((checkFunction($<val>1))==1){
				tableEntry e = search_for($<val>1);
                struct node* num = makeFunctionNode(e, $<node>3);
                $<node>$ = makeArgumentNode(num);
            }
			else{
				fprintf(stderr,"Syntax Error (isn't Function)");
                exit(1);
			} 
        }
        | term COMMA term { 
			fprintf(stderr,"PARSER: ,\n"); 
            $<node>$ = appendArgumentNode($<node>1,$<node>3);
		};

%%


int yyerror(char *s){
    fprintf(stderr,"%s\n", s);
    exit(1);
}


// int main(void)
//  {
// 	// init();
//  	return yyparse();
//  } 
