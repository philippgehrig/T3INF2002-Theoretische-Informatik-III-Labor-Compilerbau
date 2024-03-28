#include "symTab.h"
#include "synTree.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct node *makeAllNode(struct node *var, struct node *formula_node)
{
	struct node* new_node = malloc(sizeof(struct node));
	new_node->nodeType = all;
	new_node->quantor_struct.formula = formula_node;
	new_node->quantor_struct.var = var;
	return new_node;
}

struct node *makeExistNode(struct node *var, struct node *formula_node)
{
	struct node* new_node = malloc(sizeof(struct node));
	new_node->nodeType = exist;
	new_node->quantor_struct.formula = formula_node;
	new_node->quantor_struct.var = var;
	return new_node;
}

/**
 * @brief Creates Conjunction
 *
 * @param formula_left_node
 * @param formula_right_node
 * @return struct node*
 */
struct node *makeConjunctionNode(struct node *formula_left_node, struct node *formula_right_node)
{
	struct node *new_node = malloc(sizeof(struct node));
	new_node->nodeType = and;
	new_node->binary_struct.formula_left = formula_left_node;
	new_node->binary_struct.formula_right = formula_right_node;
	return new_node;
}
/**
 * @brief Creates Disjunction
 *
 * @param formula_left_node
 * @param formula_right_node
 * @return struct node*
 */
struct node *makeDisjunctionNode(struct node* formula_left_node, struct node *formula_right_node)
{
	struct node *new_node = malloc(sizeof(struct node));
	new_node->nodeType = or ;
	new_node->binary_struct.formula_left = formula_left_node;
	new_node->binary_struct.formula_right = formula_right_node;
	return new_node;
}

struct node *makeImplicationNode(struct node *formula_left_node, struct node *formula_right_node)
{
	struct node *new_node = malloc(sizeof(struct node));
	new_node->nodeType = implication;
	new_node->binary_struct.formula_left = formula_left_node;
	new_node->binary_struct.formula_right = formula_right_node;
	return new_node;
}

struct node *makeEquivalenceNode(struct node *formula_left_node, struct node *formula_right_node)
{
	struct node *new_node = malloc(sizeof(struct node));
	new_node->nodeType = equivalence;
	new_node->binary_struct.formula_left = formula_left_node;
	new_node->binary_struct.formula_right = formula_right_node;
	return new_node;
}

struct node *makeNegationNode(struct node *formula)
{
	struct node *new_node = malloc(sizeof(struct node));
	new_node->nodeType = negation;
	new_node->unary_junctor.formula = formula;
	return new_node;
}

struct node *makeFunctionNode(tableEntry SymTabEntry, struct node *argumentList)
{
	struct node *new_node = malloc(sizeof(struct node));
	new_node->nodeType = function;
	new_node->function_struct.tableEntry = SymTabEntry;
	new_node->function_struct.argument = argumentList;
	return new_node;
}
struct node *makePredicateNode(tableEntry SymTabEntry, struct node *argumentList)
{
	struct node *new_node = malloc(sizeof(struct node));
	new_node->nodeType = predicate;
	new_node->predicate_struct.tableEntry = SymTabEntry;
	new_node->predicate_struct.argument = argumentList;
	return new_node;
}
/**
 * @brief Create Variable Node
 *
 * @param SymTabEntry
 * @return struct node*
 */
struct node *makeVariableNode(tableEntry SymTabEntry)
{

	struct node *new_node = malloc(sizeof(struct node));
	new_node->nodeType = variable;
	new_node->variable_struct.tableEntry = SymTabEntry;
	return new_node;
}

struct node *makeTrueNode()
{
	struct node *new_node = malloc(sizeof(struct node));
	new_node->nodeType = true_node;
	return new_node;
}

struct node *makeFalseNode()
{
	struct node *new_node = malloc(sizeof(struct node));
	new_node->nodeType = false_node;
	return new_node;
}
struct node *makeArgumentNode(struct node *arg)
{
	struct node *new_node = malloc(sizeof(struct node));
	new_node->nodeType = argument_t;
	new_node->argument_struct.argument = arg;
	new_node->argument_struct.next = NULL;
	return new_node;
}
/**
 * @brief Anhängen des neuen Terms
 *
 * @param argument_left
 * @param argument_new
 * @return struct node*
 */
struct node *appendArgumentNode(struct node *argument_left, struct node *argument_new)
{
	struct node *temp = argument_left;
	while (temp->argument_struct.next != NULL)
	{
		temp = temp->argument_struct.next;
	}
	temp->argument_struct.next = argument_new;
	argument_new->argument_struct.next = NULL;
	return argument_left;
}

struct node *makeNumberNode(int number)
{
	struct node *new_node = malloc(sizeof(struct node));
	new_node->nodeType = number_t;
	new_node->number = number;
	return new_node;
}

void freeTeilTree(struct node* node){
	if (node != NULL)
	{
		switch (node->nodeType)
		{
			case all:
			case exist:
				freeTeilTree(node->quantor_struct.formula);
				free(node);
				break;
			case and:
			case or:
			case implication:
			case equivalence:
				freeTeilTree(node->binary_struct.formula_left);
				freeTeilTree(node->binary_struct.formula_right);
				free(node);
				break;
			case negation:
				freeTeilTree(node->unary_junctor.formula);
				free(node);
				break;
			case predicate:
				freeTeilTree(node->predicate_struct.argument);
				free(node);
				break;
			case function:
				freeTeilTree(node->function_struct.argument);
				free(node);
				break;
			case variable:
				free(node);
				break;
			case true_node:
				free(node);
				break;
			case false_node:
				free(node);
				break;
			case number_t:
				free(node);
				break;
			case argument_t:
				freeTeilTree(node->argument_struct.argument);
				freeTeilTree(node->argument_struct.next);
				free(node);
				break;
			default:
				printf("OPT: ERROR couldn't free node (current nodeType = %d)", node->nodeType);
				exit(1);
		}
	}
}

struct node *copyOfTeilTree(struct node* node){
	struct node * copyNode = NULL;
	
	if (node != NULL)
	{
		switch (node->nodeType)
		{
			case all:
				copyNode = makeAllNode(copyOfTeilTree(node->quantor_struct.var),copyOfTeilTree(node->quantor_struct.formula));
				break;
			case exist:
				copyNode = makeExistNode(copyOfTeilTree(node->quantor_struct.var), copyOfTeilTree(node->quantor_struct.formula));
				break;
			case and:
				copyNode = makeConjunctionNode(copyOfTeilTree(node->binary_struct.formula_left),copyOfTeilTree(node->binary_struct.formula_right));
				break;
			case or:
				copyNode = makeDisjunctionNode(copyOfTeilTree(node->binary_struct.formula_left),copyOfTeilTree(node->binary_struct.formula_right));
				break;
			case implication:
				copyNode = makeImplicationNode(copyOfTeilTree(node->binary_struct.formula_left),copyOfTeilTree(node->binary_struct.formula_right));
				break;
			case equivalence:
				copyNode = makeEquivalenceNode(copyOfTeilTree(node->binary_struct.formula_left),copyOfTeilTree(node->binary_struct.formula_right));
				break;
			case negation:
				copyNode = makeNegationNode(copyOfTeilTree(node->unary_junctor.formula));
				break;
			case predicate:
				copyNode = makePredicateNode(node->predicate_struct.tableEntry,copyOfTeilTree(node->predicate_struct.argument));
				break;
			case function:
				copyNode = makeFunctionNode(node->function_struct.tableEntry,copyOfTeilTree(node->function_struct.argument));
				break;
			case variable:
				copyNode = makeVariableNode(node->function_struct.tableEntry);
				break;
			case true_node:
				copyNode = makeTrueNode();
				break;
			case false_node:
				copyNode = makeFalseNode();
				break;
			case number_t:
				copyNode = makeNumberNode(node->number);
				break;
			case argument_t:
				copyNode = makeArgumentNode(copyOfTeilTree(node->argument_struct.argument));
				copyNode->argument_struct.next = copyOfTeilTree(node->argument_struct.next);
				break;
			default:
				printf("OPT: ERROR couldn't copy node (current nodeType = %d)", node->nodeType);
				exit(1);
		}
	}
	return copyNode;
}


/**
 * @brief Function to print the Syntax of the SyntaxTree as Output file
 * 
 * @param node 
 * @param f 
 */
void writeOutputFormula(struct node* node, FILE *f){

	if (node != NULL)
	{
		switch (node->nodeType)
		{
		case all:
			fprintf(f, "All[");
			writeOutputFormula(node->quantor_struct.var, f);
			fprintf(f, "]");
			writeOutputFormula(node->quantor_struct.formula, f);
			break;
		case exist:
			fprintf(f, "EXIST[");
			writeOutputFormula(node->quantor_struct.var, f);
			fprintf(f, "]");
			writeOutputFormula(node->quantor_struct.formula, f);
			break;
		case and:
			writeOutputFormula(node->binary_struct.formula_left, f);
			fprintf(f, " & ");
			writeOutputFormula(node->binary_struct.formula_right, f);
			break;
		case or:
			writeOutputFormula(node->binary_struct.formula_left, f);
			fprintf(f, " | ");
			writeOutputFormula(node->binary_struct.formula_right, f);
			break;
		case implication:
			writeOutputFormula(node->binary_struct.formula_left, f);
			fprintf(f, " -> ");
			writeOutputFormula(node->binary_struct.formula_right, f);
			break;
		case equivalence:
			writeOutputFormula(node->binary_struct.formula_left, f);
			fprintf(f, " <-> ");
			writeOutputFormula(node->binary_struct.formula_right, f);
			break;
		case negation:
			fprintf(f, "~(");
			writeOutputFormula(node->unary_junctor.formula, f);
			fprintf(f, ")");
			break;
		case predicate:
			fprintf(f,"%s(", node->predicate_struct.tableEntry->identifier);
			writeOutputFormula(node->predicate_struct.argument, f);
			fprintf(f, ")");
			break;
		case function:
			fprintf(f, "%s(", node->function_struct.tableEntry->identifier);
			writeOutputFormula(node->function_struct.argument, f);
			fprintf(f, ")");
			break;
		case variable:
			fprintf(f, "%s", node->variable_struct.tableEntry->identifier);
			break;
		case true_node:
			fprintf(f, "TRUE");
			break;
		case false_node:
			fprintf(f, "FALSE");
			break;
		case number_t:
			fprintf(f, "%d", node->number);
			break;
		case argument_t:
			writeOutputFormula(node->argument_struct.argument, f);
			if (node->argument_struct.next != NULL){ 
			fprintf(f, ",");
			writeOutputFormula(node->argument_struct.next, f);
			}
			break;
		default:
			printf("OUT: ERROR (current nodeType = %d)", node->nodeType);
			fprintf(f,"ERROR: %d", node->nodeType);
			exit(1);
		}
	}
}
// enum nodeT{all, exist, and, or, implication, equivalence, negation, predicate, function, variable,true_node, false_node, number, argument_t};
/**
 * @brief Function to print the Syntax Tree
 * 
 * @param node 
 * @param level 
 */
void printTree(struct node* node, int level)
{
	if (node != NULL)
	{
		if (node->nodeType != argument_t)
		{
			printf("STP: ");
			for (int i = 0; i < level; i++)
			{
				printf(".");
			}
		}
		switch (node->nodeType)
		{
		case all:
			printf("All\n");
			printTree(node->quantor_struct.var, level + 1);
			printTree(node->quantor_struct.formula, level + 1);
			break;
		case exist:
			printf("EXIST\n");
			printTree(node->quantor_struct.var, level + 1);
			printTree(node->quantor_struct.formula, level + 1);
			break;
		case and:
			printf("AND\n");
			printTree(node->binary_struct.formula_left, level + 1);
			printTree(node->binary_struct.formula_right, level + 1);
			break;
		case or:
			printf("OR\n");
			printTree(node->binary_struct.formula_left, level + 1);
			printTree(node->binary_struct.formula_right, level + 1);
			break;
		case implication:
			printf("IMPLICATION\n");
			printTree(node->binary_struct.formula_left, level + 1);
			printTree(node->binary_struct.formula_right, level + 1);
			break;
		case equivalence:
			printf("EQUIVALENCE\n");
			printTree(node->binary_struct.formula_left, level + 1);
			printTree(node->binary_struct.formula_right, level + 1);
			break;
		case negation:
			printf("NEGATION\n");
			printTree(node->unary_junctor.formula, level + 1);
			break;
		case predicate:
			printf("PREDICATE: %s\n", node->predicate_struct.tableEntry->identifier);
			printTree(node->predicate_struct.argument, level + 1);
			break;
		case function:
			printf("FUNCTION: %s\n", node->function_struct.tableEntry->identifier);
			printTree(node->function_struct.argument, level + 1);
			break;
		case variable:
			printf("VARIABLE: %s\n", node->variable_struct.tableEntry->identifier);
			break;
		case true_node:
			printf("TRUE\n");
			break;
		case false_node:
			printf("FALSE\n");
			break;
		case number_t:
			printf("NUMBER %d\n", node->number);
			break;
		case argument_t:
			printTree(node->argument_struct.argument, level);
			if (node->argument_struct.next != NULL){ //try
			printTree(node->argument_struct.next, level);
			}
			break;
		default:
			printf("unknown syntax Node\n");
			exit(1);
		}
	}
}