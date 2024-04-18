#include "optimize.h"
/**
 * @brief Function to remove double negations
 * 
 * @param node 
 * @return struct node* 
 */
struct node* removeDoubleNeg(struct node* node)
{
    struct node * back;
    struct node* left;
    struct node* right;
    switch (node->type){
        case type_negation:
            if(node->synTree.unary_junctor.formula->type == type_negation){
                printf("OPT: found double negation\n");
                back = removeDoubleNeg(node->synTree.unary_junctor.formula ->synTree.unary_junctor.formula);
                free(node->synTree.unary_junctor.formula);
                free(node);
            }
            else{
                back = removeDoubleNeg(node->synTree.unary_junctor.formula);
                back = node;
            }
            break;
        case type_all:
        case type_exist:
            back = removeDoubleNeg(node->synTree.quantor_struct.formula);
            node ->synTree.quantor_struct.formula = back;
        case type_and:
        case type_or:
        case type_implication:
        case type_equivalence:
            left = removeDoubleNeg(node->synTree.binary_struct.formula_left);
            right = removeDoubleNeg(node->synTree.binary_struct.formula_right);
            node->synTree.binary_struct.formula_left = left;
            node->synTree.binary_struct.formula_right = right;
        default:
            back = node;
            break;
    }
    return back;
}