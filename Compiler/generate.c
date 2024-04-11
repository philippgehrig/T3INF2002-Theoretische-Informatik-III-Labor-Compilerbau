#include "generate.h"

void generate(struct node* node)
{
    if(node == NULL)
        return;
    switch(node->type)
    {
        case type_all:
            printf("ALL[");
            generate(node->synTree.quantor_struct.var);
            printf("] ");
            generate(node->synTree.quantor_struct.formula);
            break;
        case type_exist:
            printf("EXSIST[");
            generate(node->synTree.quantor_struct.var);
            printf("] ");
            generate(node->synTree.quantor_struct.formula);
            break;
        case type_and:
            generate(node->synTree.binary_struct.formula_left);
            printf("& ");
            generate(node->synTree.binary_struct.formula_right);
            break;
        case type_or:
            generate(node->synTree.binary_struct.formula_left);
            printf("| ");
            generate(node->synTree.binary_struct.formula_right);
            break;
        case type_implication:
            generate(node->synTree.binary_struct.formula_left);
            printf("-> ");
            generate(node->synTree.binary_struct.formula_right);
            break;
        case type_equivalence:
            generate(node->synTree.binary_struct.formula_left);
            printf("<-> ");
            generate(node->synTree.binary_struct.formula_right);
            break;
        case type_negation:
            printf("~ ");
            generate(node->synTree.unary_junctor.formula);
            break;
        case type_predicate:
            printf("PREDICATE ");
            printf(node->synTree.predicate_struct.tableEntry->identifier);
            printf("(");
            generate(node->synTree.predicate_struct.argument);
            printf(")");
            break;
        case type_function:
            printf("FUNCTION ");
            printf(node->synTree.function_struct.tableEntry->identifier);
            if(node->synTree.function_struct.tableEntry->arity == 0)
                generate(node->synTree.function_struct.argument);
            else
            printf("(");
            generate(node->synTree.function_struct.argument);
            printf(") ");
            break;
        default:
            printf("default");
        
    }
    return;
}

/*
@param node: the node to be printed
@param right: the position of the node in the formula => needed for Assoziativität
@param parent: the parent of the node
*/


void addBracket(struct node* node, bool right, struct node* parent)
{
    if(node == NULL)
        return;
    switch (node->type)
    {
        case type_negation:
            if(parent->type == type_function || parent->type == type_predicate || parent->type == type_all || parent->type == type_exist) {
                printf("(");
                generate(node);
                printf(")");
            }
            else generate(node);
        case type_and:
        case type_or:
        case type_implication:
            if(node->type == type_implication || right){
                printf("(");
                generate(node);
                printf(")");
            }
            else{
                generate(node);
            }
        case type_equivalence:
        
        default:
            break;
    }
}