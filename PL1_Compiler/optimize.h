#ifndef OPTIMIZE_H
#define OPTIMIZE_H
#include <stdio.h>



struct node* entfDoppNegation(struct node* node);
struct node*  optimzeFormula(struct node* node);
struct node* verschiebeNegation(struct node* node);
struct node* makeFormulaEasier(struct node* node);

#endif