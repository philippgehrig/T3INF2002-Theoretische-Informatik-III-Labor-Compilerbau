#include "SynTree.h"
#include <stdlib.h>
/**
 * @brief Function to remove double negations
 * 
 * @param node 
 * @return struct node* 
 */
struct node* entfDoppNegation(struct node* node)
{
    struct node* rueck;
	switch (node->nodeType)
	{
		case negation:
            if(node->unary_junctor.formula->nodeType == negation){
                printf("OPT: Found double negation\n");
				rueck = entfDoppNegation(node->unary_junctor.formula->unary_junctor.formula);
                free(node->unary_junctor.formula);
                free(node);
            }else{
                rueck = entfDoppNegation(node->unary_junctor.formula);
				rueck = node;
            }
			break;
        case all:
		case exist:
			rueck = entfDoppNegation(node->quantor_struct.formula);
            node->quantor_struct.formula = rueck;
            rueck = node;
			break;
		case and:
		case or:
		case implication:
		case equivalence:
            struct node* left = entfDoppNegation(node->binary_struct.formula_left);
			struct node* right = entfDoppNegation(node->binary_struct.formula_right);
            node->binary_struct.formula_left = left;
            node->binary_struct.formula_right = right;
            rueck = node;
			break;
		default:
		    rueck = node;
	}
    return rueck;
}

struct node* verschiebeNegation(struct node* node){
	struct node* rueck;
	switch (node->nodeType){
	    case negation:
            struct node* newLeft;
            struct node* newRight;
			struct node* newNegationNode ;
            switch(node->unary_junctor.formula->nodeType){
                case and:
                    printf("OPT: Shift Negation in Conjunction\n");
                    newLeft = makeNegationNode(node->unary_junctor.formula->binary_struct.formula_left);
                    newRight = makeNegationNode(node->unary_junctor.formula->binary_struct.formula_right);
                    newRight = verschiebeNegation(newRight);
                    newLeft = verschiebeNegation(newLeft);
                    rueck = makeDisjunctionNode(newLeft, newRight);
                    free(node->unary_junctor.formula);
                    free(node);
                    break;
                case or:
                    printf("OPT: Shift Negation in Disjunction\n");
                    newLeft = makeNegationNode(node->unary_junctor.formula->binary_struct.formula_left);
                    newRight = makeNegationNode(node->unary_junctor.formula->binary_struct.formula_right);
                    newRight = verschiebeNegation(newRight);
                    newLeft = verschiebeNegation(newLeft);
                    rueck = makeConjunctionNode(newLeft, newRight);
                    free(node->unary_junctor.formula);
                    free(node); 
                    break;
                case exist:
                    printf("OPT: Shift Negation in Exist\n");
					newNegationNode = makeNegationNode(node->unary_junctor.formula->quantor_struct.formula);
                    newNegationNode = verschiebeNegation(newNegationNode);
					rueck = makeAllNode(node->unary_junctor.formula->quantor_struct.var,newNegationNode);
                    free(node->unary_junctor.formula);
					free(node);
                    break;
                case all:
                    printf("OPT: Shift Negation in All\n");
                    newNegationNode = makeNegationNode(node->unary_junctor.formula->quantor_struct.formula);
					newNegationNode = verschiebeNegation(newNegationNode);
                    rueck = makeExistNode(node->unary_junctor.formula->quantor_struct.var,newNegationNode);
                    free(node->unary_junctor.formula);
                    free(node);
                    break;
                default:
                    rueck = node;
					break;
            }
			break;
        case all:
		case exist:
			rueck = verschiebeNegation(node->quantor_struct.formula);
            node->quantor_struct.formula = rueck;
            rueck = node;
			break;
		case and:
		case or:
		case implication:
		case equivalence:
            struct node* left = verschiebeNegation(node->binary_struct.formula_left);
			struct node* right = verschiebeNegation(node->binary_struct.formula_right);
			node->binary_struct.formula_left = left;
            node->binary_struct.formula_right = right;
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
	switch (node->nodeType){
		case and:
		case or:
			node->binary_struct.formula_left = makeFormulaEasier(node->binary_struct.formula_left);
            node->binary_struct.formula_right = makeFormulaEasier(node->binary_struct.formula_right);
            rueck = node;
			break;
	    case negation:
            node->unary_junctor.formula = makeFormulaEasier(node->unary_junctor.formula);
            rueck = node;
            break;
        case all:
		case exist:
			rueck = makeFormulaEasier(node->quantor_struct.formula);
            node->quantor_struct.formula = rueck;
            rueck = node;
			break;
		case equivalence:
            printf("OPT: Make Equivalence easier\n");
            node->binary_struct.formula_left = makeFormulaEasier(node->binary_struct.formula_left);
            node->binary_struct.formula_right = makeFormulaEasier(node->binary_struct.formula_right);
            left = makeConjunctionNode(node->binary_struct.formula_left, node->binary_struct.formula_right);
            struct node* rightNegLeft = makeNegationNode(copyOfTeilTree(node->binary_struct.formula_left));
            struct node* rightNegRight = makeNegationNode(copyOfTeilTree(node->binary_struct.formula_right));
            right = makeConjunctionNode(rightNegLeft, rightNegRight);
            rueck = makeDisjunctionNode(left, right);
            free(node);
            break;
		case implication:
            printf("OPT: Make Implication easier\n");
            node->binary_struct.formula_left = makeFormulaEasier(node->binary_struct.formula_left);
            node->binary_struct.formula_right = makeFormulaEasier(node->binary_struct.formula_right);
            left = makeNegationNode(node->binary_struct.formula_left);
            right = node->binary_struct.formula_right;
            rueck = makeDisjunctionNode(left, right);
            free(node);
			break;
		default:
			rueck = node;
	}
	return rueck;
}

/**
 * @brief 
 * 
 * @param node 
 * @return struct node* 
 */
struct node* makeBoolOperations(struct node* node){
    struct node* rueck;
    switch (node->nodeType){
		case and:
            node->binary_struct.formula_left = makeBoolOperations(node->binary_struct.formula_left);
            node->binary_struct.formula_right = makeBoolOperations(node->binary_struct.formula_right);
            if(node->binary_struct.formula_left->nodeType == true_node){
                printf("OPT: Refactor unnecessary Conjunction with left Formula\n");
                rueck = node->binary_struct.formula_right;
                freeTeilTree(node->binary_struct.formula_left);
                free(node);
            }
            else if(node->binary_struct.formula_right->nodeType == true_node){
                printf("OPT: Refactor unnecessary Conjunction with right Formula\n");
                rueck = node->binary_struct.formula_left;
                freeTeilTree(node->binary_struct.formula_right);
                free(node);
            }
            else if(node->binary_struct.formula_left->nodeType == false_node || node->binary_struct.formula_right->nodeType == false_node){
                printf("OPT: Refactor unnecessary Conjunction with False\n");
                rueck = makeFalseNode();
                freeTeilTree(node->binary_struct.formula_left);
                freeTeilTree(node->binary_struct.formula_right);
                free(node);
            }
            else{
                rueck = node;
            }
            break;
		case or:
            node->binary_struct.formula_left = makeBoolOperations(node->binary_struct.formula_left);
            node->binary_struct.formula_right = makeBoolOperations(node->binary_struct.formula_right);

            if(node->binary_struct.formula_left->nodeType == true_node || node->binary_struct.formula_right->nodeType == true_node){
                printf("OPT: Refactor unnecessary Disjunction with True\n");
                rueck = makeTrueNode();
                freeTeilTree(node->binary_struct.formula_left);
                freeTeilTree(node->binary_struct.formula_right);
                free(node);
            }
            else if(node->binary_struct.formula_left->nodeType == false_node){
                printf("OPT: Refactor unnecessary Disjunction with right Formula\n");
                rueck = node->binary_struct.formula_right;
                freeTeilTree(node->binary_struct.formula_left);
                free(node);
            }
            else if(node->binary_struct.formula_right->nodeType == false_node){
                printf("OPT: Refactor unnecessary Disjunction with left Formula\n");
                rueck = node->binary_struct.formula_left;
                freeTeilTree(node->binary_struct.formula_right);
                free(node);
            }
            else{
                rueck = node;
            }
            break;
	    case negation:
		    node->unary_junctor.formula = makeBoolOperations(node->unary_junctor.formula);
            if(node->unary_junctor.formula->nodeType == true_node){
                printf("OPT: Refactor Negation True with False\n");
                rueck = makeFalseNode();
                free(node->unary_junctor.formula);
                free(node);
            }else if(node->unary_junctor.formula->nodeType == false_node){
                printf("OPT: Refactor Negation False with True\n");
                rueck = makeTrueNode();
                free(node->unary_junctor.formula);
                free(node);
            }else{
                rueck = node;
            }
            break;
        case equivalence:
		case implication:
			node->binary_struct.formula_left = makeBoolOperations(node->binary_struct.formula_left);
            node->binary_struct.formula_right = makeBoolOperations(node->binary_struct.formula_right);
			rueck = node;
			break;
        case all:
		case exist:
			rueck = makeBoolOperations(node->quantor_struct.formula);
            node->quantor_struct.formula = rueck;
            rueck = node;
			break;
		default:
			rueck = node;
	}
	return rueck;
}

/**
 * @brief Function to perform all optimizations
 * 
 * @param node First node
 * @return struct node* 
 */
struct node* optimzeFormula(struct node* node)
{
    node = makeFormulaEasier(node);
    printf("Zwischenschritt 1:\n");
    printTree(node,0);
	node = verschiebeNegation(node);
    printf("Zwischenschritt 2:\n");
    printTree(node,0);
    node = entfDoppNegation(node);
    printf("Zwischenschritt 3:\n");
    printTree(node,0);
    node = makeBoolOperations(node);

    return node;
}	