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

struct node* moveNeg(struct node* node){
	struct node* rueck;
    struct node* newLeft;
    struct node* newRight;
    struct node* newNegationNode;
	switch (node->type){
	    case type_negation:
            switch(node->synTree.unary_junctor.formula->type){
                case type_and:
                    fprintf(stderr, "OPT: Shift Negation in Conjunction\n");
                    newLeft = makeNegationNode(node->synTree.unary_junctor.formula->synTree.binary_struct.formula_left);
                    newRight = makeNegationNode(node->synTree.unary_junctor.formula->synTree.binary_struct.formula_right);
                    newRight = moveNeg(newRight);
                    newLeft = moveNeg(newLeft);
                    rueck = makeDisjunctionNode(newLeft, newRight);
                    free(node->synTree.unary_junctor.formula);
                    free(node);
                    break;
                case type_or:
                    fprintf(stderr, "OPT: Shift Negation in Disjunction\n");
                    newLeft = makeNegationNode(node->synTree.unary_junctor.formula->synTree.binary_struct.formula_left);
                    newRight = makeNegationNode(node->synTree.unary_junctor.formula->synTree.binary_struct.formula_right);
                    newRight = moveNeg(newRight);
                    newLeft = moveNeg(newLeft);
                    rueck = makeConjunctionNode(newLeft, newRight);
                    free(node->synTree.unary_junctor.formula);
                    free(node); 
                    break;
                case type_exist:
                    fprintf(stderr, "OPT: Shift Negation in Exist\n");
					newNegationNode = makeNegationNode(node->synTree.unary_junctor.formula->synTree.quantor_struct.formula);
                    newNegationNode = moveNeg(newNegationNode);
					rueck = makeAllNode(node->synTree.unary_junctor.formula->synTree.quantor_struct.var,newNegationNode);
                    free(node->synTree.unary_junctor.formula);
					free(node);
                    break;
                case type_all:
                    fprintf(stderr, "OPT: Shift Negation in All\n");
                    newNegationNode = makeNegationNode(node->synTree.unary_junctor.formula->synTree.quantor_struct.formula);
					newNegationNode = moveNeg(newNegationNode);
                    rueck = makeExistNode(node->synTree.unary_junctor.formula->synTree.quantor_struct.var,newNegationNode);
                    free(node->synTree.unary_junctor.formula);
                    free(node);
                    break;
                default:
                    rueck = node;
					break;
            }
			break;
        case type_all:
		case type_exist:
			rueck = moveNeg(node->synTree.quantor_struct.formula);
            node->synTree.quantor_struct.formula = rueck;
            rueck = node;
			break;
		case type_and:
		case type_or:
		case type_implication:
		case type_equivalence:
            newLeft = moveNeg(node->synTree.binary_struct.formula_left);
			newRight = moveNeg(node->synTree.binary_struct.formula_right);
			node->synTree.binary_struct.formula_left = newLeft;
            node->synTree.binary_struct.formula_right = newRight;
            rueck = node;
			break;
		default:
			rueck = node;
	}
	return rueck;
}

struct node* makeFormulaEasier(struct node* node){
    struct node* rueck;
    struct node* left;
    struct node* right;
	switch (node->type){
		case type_and:
		case type_or:
			node->synTree.binary_struct.formula_left = makeFormulaEasier(node->synTree.binary_struct.formula_left);
            node->synTree.binary_struct.formula_right = makeFormulaEasier(node->synTree.binary_struct.formula_right);
            rueck = node;
			break;
	    case type_negation:
            node->synTree.unary_junctor.formula = makeFormulaEasier(node->synTree.unary_junctor.formula);
            rueck = node;
            break;
        case type_all:
		case type_exist:
			rueck = makeFormulaEasier(node->synTree.quantor_struct.formula);
            node->synTree.quantor_struct.formula = rueck;
            rueck = node;
			break;
		case type_equivalence:
            fprintf(stderr,"OPT: Make Equivalence easier\n");
            node->synTree.binary_struct.formula_left = makeFormulaEasier(node->synTree.binary_struct.formula_left);
            node->synTree.binary_struct.formula_right = makeFormulaEasier(node->synTree.binary_struct.formula_right);
            left = makeConjunctionNode(node->synTree.binary_struct.formula_left, node->synTree.binary_struct.formula_right);
            struct node* rightNegLeft = makeNegationNode(copyOfTeilTree(node->synTree.binary_struct.formula_left));
            struct node* rightNegRight = makeNegationNode(copyOfTeilTree(node->synTree.binary_struct.formula_right));
            right = makeConjunctionNode(rightNegLeft, rightNegRight);
            rueck = makeDisjunctionNode(left, right);
            free(node);
            break;
		case type_implication:
            fprintf(stderr,"OPT: Make Implication easier\n");
            node->synTree.binary_struct.formula_left = makeFormulaEasier(node->synTree.binary_struct.formula_left);
            node->synTree.binary_struct.formula_right = makeFormulaEasier(node->synTree.binary_struct.formula_right);
            left = makeNegationNode(node->synTree.binary_struct.formula_left);
            right = node->synTree.binary_struct.formula_right;
            rueck = makeDisjunctionNode(left, right);
            free(node);
			break;
		default:
			rueck = node;
	}
	return rueck;
}

struct node* makeBoolOperations(struct node* node){
    struct node* rueck;
    switch (node->type){
		case type_and:
            node->synTree.binary_struct.formula_left = makeBoolOperations(node->synTree.binary_struct.formula_left);
            node->synTree.binary_struct.formula_right = makeBoolOperations(node->synTree.binary_struct.formula_right);
            if(node->synTree.binary_struct.formula_left->type == type_true_node){
                fprintf(stderr,"OPT: Refactor unnecessary Conjunction with left Formula\n");
                rueck = node->synTree.binary_struct.formula_right;
                freeTeilTree(node->synTree.binary_struct.formula_left);
                free(node);
            }
            else if(node->synTree.binary_struct.formula_right->type == type_true_node){
                fprintf(stderr,"OPT: Refactor unnecessary Conjunction with right Formula\n");
                rueck = node->synTree.binary_struct.formula_left;
                freeTeilTree(node->synTree.binary_struct.formula_right);
                free(node);
            }
            else if(node->synTree.binary_struct.formula_left->type == type_false_node || node->synTree.binary_struct.formula_right->type == type_false_node){
                fprintf(stderr,"OPT: Refactor unnecessary Conjunction with False\n");
                rueck = makeFalseNode();
                freeTeilTree(node->synTree.binary_struct.formula_left);
                freeTeilTree(node->synTree.binary_struct.formula_right);
                free(node);
            }
            else{
                rueck = node;
            }
            break;
		case type_or:
            node->synTree.binary_struct.formula_left = makeBoolOperations(node->synTree.binary_struct.formula_left);
            node->synTree.binary_struct.formula_right = makeBoolOperations(node->synTree.binary_struct.formula_right);

            if(node->synTree.binary_struct.formula_left->type == type_true_node || node->synTree.binary_struct.formula_right->type == type_true_node){
                fprintf(stderr,"OPT: Refactor unnecessary Disjunction with True\n");
                rueck = makeTrueNode();
                freeTeilTree(node->synTree.binary_struct.formula_left);
                freeTeilTree(node->synTree.binary_struct.formula_right);
                free(node);
            }
            else if(node->synTree.binary_struct.formula_left->type == type_false_node){
                fprintf(stderr,"OPT: Refactor unnecessary Disjunction with right Formula\n");
                rueck = node->synTree.binary_struct.formula_right;
                freeTeilTree(node->synTree.binary_struct.formula_left);
                free(node);
            }
            else if(node->synTree.binary_struct.formula_right->type == type_false_node){
                fprintf(stderr,"OPT: Refactor unnecessary Disjunction with left Formula\n");
                rueck = node->synTree.binary_struct.formula_left;
                freeTeilTree(node->synTree.binary_struct.formula_right);
                free(node);
            }
            else{
                rueck = node;
            }
            break;
	    case type_negation:
		    node->synTree.unary_junctor.formula = makeBoolOperations(node->synTree.unary_junctor.formula);
            if(node->synTree.unary_junctor.formula->type == type_true_node){
                fprintf(stderr,"OPT: Refactor Negation True with False\n");
                rueck = makeFalseNode();
                free(node->synTree.unary_junctor.formula);
                free(node);
            }else if(node->synTree.unary_junctor.formula->type == type_false_node){
                fprintf(stderr, "OPT: Refactor Negation False with True\n");
                rueck = makeTrueNode();
                free(node->synTree.unary_junctor.formula);
                free(node);
            }else{
                rueck = node;
            }
            break;
        case type_equivalence:
		case type_implication:
			node->synTree.binary_struct.formula_left = makeBoolOperations(node->synTree.binary_struct.formula_left);
            node->synTree.binary_struct.formula_right = makeBoolOperations(node->synTree.binary_struct.formula_right);
			rueck = node;
			break;
        case type_all:
		case type_exist:
			rueck = makeBoolOperations(node->synTree.quantor_struct.formula);
            node->synTree.quantor_struct.formula = rueck;
            rueck = node;
			break;
		default:
			rueck = node;
	}
	return rueck;
}

struct node* optimizeFormula(struct node* node){
    struct node* rueck;
    rueck = removeDoubleNeg(node);
    rueck = moveNeg(rueck);
    rueck = makeFormulaEasier(rueck);
    rueck = makeBoolOperations(rueck);
    return rueck;
}