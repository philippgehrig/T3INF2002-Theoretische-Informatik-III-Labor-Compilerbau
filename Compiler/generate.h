#ifndef GENERATE
#define GENERATE

#include "synTree.h"
#include "symTab.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void generate(struct node* node);
void addBracket(struct node* node, bool right, struct node* parent);

#endif GENERATE