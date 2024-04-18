#ifndef GENERATE
#define GENERATE
#include <stdbool.h>
#include "synTree.h"


void generate(struct node* node);
void generate_helper(struct node* node, struct node* parent, bool right);
void addBracket(struct node* node, bool right, struct node* parent);

#endif