#ifndef OPTIMIZE_H
#define OPTIMIZE_H
#include <stdio.h>
#include <stdlib.h>
#include "synTree.h"

struct node* removeDoubleNeg(struct node* node);
struct node* optimzeFormula(struct node* node);
struct node* moveNeg(struct node* node);
struct node* makeBoolOperations(struct node* node);
struct node* optimizeFormula(struct node* node);

#endif