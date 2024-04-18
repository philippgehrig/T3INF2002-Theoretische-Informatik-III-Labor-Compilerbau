#ifndef OPTIMIZE_H
#define OPTIMIZE_H
#include <stdio.h>
#include <stdlib.h>
#include "synTree.h"

struct node* removeDoubleNeg(struct node* node);
struct node* optimzeFormula(struct node* node);
struct node* verschiebeNegation(struct node* node);
struct node* makeFormulaEasier(struct node* node);

#endif