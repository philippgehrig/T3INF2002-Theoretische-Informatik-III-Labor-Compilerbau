#ifndef GENERATE
#define GENERATE

#include "synTree.h"
#include "symTab.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void generate(struct node* node);
void generate_helper(struct node* node, struct node* parent, bool right);
void addBracket(struct node* node, bool right, struct node* parent);

#endif GENERATE