#include "symTab.h"
#include "synTree.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct node *makeAllNode(struct node *var, struct node *formula_node)
{
	struct node* new_node = malloc(sizeof(struct node));
	new_node->type = type_all;
	new_node->synTree.quantor_struct.formula = formula_node;
	new_node->synTree.quantor_struct.var = var;
	return new_node;
}

struct node *makeExistNode(struct node *var, struct node *formula_node)
{
	struct node* new_node = malloc(sizeof(struct node));
	new_node->type = type_exist;
	new_node->synTree.quantor_struct.formula = formula_node;
	new_node->synTree.quantor_struct.var = var;
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
	new_node->type = type_and;
	new_node->synTree.binary_struct.formula_left = formula_left_node;
	new_node->synTree.binary_struct.formula_right = formula_right_node;
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
	new_node->type = type_or ;
	new_node->synTree.binary_struct.formula_left = formula_left_node;
	new_node->synTree.binary_struct.formula_right = formula_right_node;
	return new_node;
}

struct node *makeImplicationNode(struct node *formula_left_node, struct node *formula_right_node)
{
	struct node *new_node = malloc(sizeof(struct node));
	new_node->type = type_implication;
	new_node->synTree.binary_struct.formula_left = formula_left_node;
	new_node->synTree.binary_struct.formula_right = formula_right_node;
	return new_node;
}

struct node *makeEquivalenceNode(struct node *formula_left_node, struct node *formula_right_node)
{
	struct node *new_node = malloc(sizeof(struct node));
	new_node->type = type_equivalence;
	new_node->synTree.binary_struct.formula_left = formula_left_node;
	new_node->synTree.binary_struct.formula_right = formula_right_node;
	return new_node;
}

struct node *makeNegationNode(struct node *formula)
{
	struct node *new_node = malloc(sizeof(struct node));
	new_node->type = type_negation;
	new_node->synTree.unary_junctor.formula = formula;
	return new_node;
}

struct node *makeFunctionNode(tableEntry SymTabEntry, struct node *argumentList)
{
	struct node *new_node = malloc(sizeof(struct node));
	new_node->type = type_function;
	new_node->synTree.function_struct.tableEntry = SymTabEntry;
	new_node->synTree.function_struct.argument = argumentList;
	return new_node;
}
struct node *makePredicateNode(tableEntry SymTabEntry, struct node *argumentList)
{
	struct node *new_node = malloc(sizeof(struct node));
	new_node->type = type_predicate;
	new_node->synTree.predicate_struct.tableEntry = SymTabEntry;
	new_node->synTree.predicate_struct.argument = argumentList;
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
	new_node->type = type_variable;
	new_node->synTree.variable_struct.tableEntry = SymTabEntry;
	return new_node;
}

struct node *makeTrueNode()
{
	struct node *new_node = malloc(sizeof(struct node));
	new_node->type = type_true_node;
	return new_node;
}

struct node *makeFalseNode()
{
	struct node *new_node = malloc(sizeof(struct node));
	new_node->type = type_false_node;
	return new_node;
}
struct node *makeArgumentNode(struct node *arg)
{
	struct node *new_node = malloc(sizeof(struct node));
	new_node->type = type_argument_t;
	new_node->synTree.argument_struct.argument = arg;
	new_node->synTree.argument_struct.next = NULL;
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
	while (temp->synTree.argument_struct.next != NULL)
	{
		temp = temp->synTree.argument_struct.next;
	}
	temp->synTree.argument_struct.next = argument_new;
	argument_new->synTree.argument_struct.next = NULL;
	return argument_left;
}

struct node *makeNumberNode(int number)
{
	struct node *new_node = malloc(sizeof(struct node));
	new_node->type = type_number_t;
	new_node->synTree.number = number;
	return new_node;
}

void freeTeilTree(struct node* node){
	if (node != NULL)
	{
		switch (node->type)
		{
			case type_all:
			case type_exist:
				freeTeilTree(node->synTree.quantor_struct.formula);
				free(node);
				break;
			case type_and:
			case type_or:
			case type_implication:
			case type_equivalence:
				freeTeilTree(node->synTree.binary_struct.formula_left);
				freeTeilTree(node->synTree.binary_struct.formula_right);
				free(node);
				break;
			case type_negation:
				freeTeilTree(node->synTree.unary_junctor.formula);
				free(node);
				break;
			case type_predicate:
				freeTeilTree(node->synTree.predicate_struct.argument);
				free(node);
				break;
			case type_function:
				freeTeilTree(node->synTree.function_struct.argument);
				free(node);
				break;
			case type_variable:
				free(node);
				break;
			case type_true_node:
				free(node);
				break;
			case type_false_node:
				free(node);
				break;
			case type_number_t:
				free(node);
				break;
			case type_argument_t:
				freeTeilTree(node->synTree.argument_struct.argument);
				freeTeilTree(node->synTree.argument_struct.next);
				free(node);
				break;
			default:
				printf("OPT: ERROR couldn't free node (current type = %d)", node->type);
				exit(1);
		}
	}
}

struct node *copyOfTeilTree(struct node* node){
	struct node * copyNode = NULL;
	
	if (node != NULL)
	{
		switch (node->type)
		{
			case type_all:
				copyNode = makeAllNode(copyOfTeilTree(node->synTree.quantor_struct.var),copyOfTeilTree(node->synTree.quantor_struct.formula));
				break;
			case type_exist:
				copyNode = makeExistNode(copyOfTeilTree(node->synTree.quantor_struct.var), copyOfTeilTree(node->synTree.quantor_struct.formula));
				break;
			case type_and:
				copyNode = makeConjunctionNode(copyOfTeilTree(node->synTree.binary_struct.formula_left),copyOfTeilTree(node->synTree.binary_struct.formula_right));
				break;
			case type_or:
				copyNode = makeDisjunctionNode(copyOfTeilTree(node->synTree.binary_struct.formula_left),copyOfTeilTree(node->synTree.binary_struct.formula_right));
				break;
			case type_implication:
				copyNode = makeImplicationNode(copyOfTeilTree(node->synTree.binary_struct.formula_left),copyOfTeilTree(node->synTree.binary_struct.formula_right));
				break;
			case type_equivalence:
				copyNode = makeEquivalenceNode(copyOfTeilTree(node->synTree.binary_struct.formula_left),copyOfTeilTree(node->synTree.binary_struct.formula_right));
				break;
			case type_negation:
				copyNode = makeNegationNode(copyOfTeilTree(node->synTree.unary_junctor.formula));
				break;
			case type_predicate:
				copyNode = makePredicateNode(node->synTree.predicate_struct.tableEntry,copyOfTeilTree(node->synTree.predicate_struct.argument));
				break;
			case type_function:
				copyNode = makeFunctionNode(node->synTree.function_struct.tableEntry,copyOfTeilTree(node->synTree.function_struct.argument));
				break;
			case type_variable:
				copyNode = makeVariableNode(node->synTree.function_struct.tableEntry);
				break;
			case type_true_node:
				copyNode = makeTrueNode();
				break;
			case type_false_node:
				copyNode = makeFalseNode();
				break;
			case type_number_t:
				copyNode = makeNumberNode(node->synTree.number);
				break;
			case type_argument_t:
				copyNode = makeArgumentNode(copyOfTeilTree(node->synTree.argument_struct.argument));
				copyNode->synTree.argument_struct.next = copyOfTeilTree(node->synTree.argument_struct.next);
				break;
			default:
				printf("OPT: ERROR couldn't copy node (current type = %d)", node->type);
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
		switch (node->type)
		{
		case type_all:
			fprintf(f, "All[");
			writeOutputFormula(node->synTree.quantor_struct.var, f);
			fprintf(f, "]");
			writeOutputFormula(node->synTree.quantor_struct.formula, f);
			break;
		case type_exist:
			fprintf(f, "EXIST[");
			writeOutputFormula(node->synTree.quantor_struct.var, f);
			fprintf(f, "]");
			writeOutputFormula(node->synTree.quantor_struct.formula, f);
			break;
		case type_and:
			writeOutputFormula(node->synTree.binary_struct.formula_left, f);
			fprintf(f, " & ");
			writeOutputFormula(node->synTree.binary_struct.formula_right, f);
			break;
		case type_or:
			writeOutputFormula(node->synTree.binary_struct.formula_left, f);
			fprintf(f, " | ");
			writeOutputFormula(node->synTree.binary_struct.formula_right, f);
			break;
		case type_implication:
			writeOutputFormula(node->synTree.binary_struct.formula_left, f);
			fprintf(f, " -> ");
			writeOutputFormula(node->synTree.binary_struct.formula_right, f);
			break;
		case type_equivalence:
			writeOutputFormula(node->synTree.binary_struct.formula_left, f);
			fprintf(f, " <-> ");
			writeOutputFormula(node->synTree.binary_struct.formula_right, f);
			break;
		case type_negation:
			fprintf(f, "~(");
			writeOutputFormula(node->synTree.unary_junctor.formula, f);
			fprintf(f, ")");
			break;
		case type_predicate:
			fprintf(f,"%s(", node->synTree.predicate_struct.tableEntry->identifier);
			writeOutputFormula(node->synTree.predicate_struct.argument, f);
			fprintf(f, ")");
			break;
		case type_function:
			fprintf(f, "%s(", node->synTree.function_struct.tableEntry->identifier);
			writeOutputFormula(node->synTree.function_struct.argument, f);
			fprintf(f, ")");
			break;
		case type_variable:
			fprintf(f, "%s", node->synTree.variable_struct.tableEntry->identifier);
			break;
		case type_true_node:
			fprintf(f, "TRUE");
			break;
		case type_false_node:
			fprintf(f, "FALSE");
			break;
		case type_number_t:
			fprintf(f, "%d", node->synTree.number);
			break;
		case type_argument_t:
			writeOutputFormula(node->synTree.argument_struct.argument, f);
			if (node->synTree.argument_struct.next != NULL){ 
			fprintf(f, ",");
			writeOutputFormula(node->synTree.argument_struct.next, f);
			}
			break;
		default:
			printf("OUT: ERROR (current type = %d)", node->type);
			fprintf(f,"ERROR: %d", node->type);
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
		if (node->type !=type_argument_t)
		{
			printf("STP: ");
			for (int i = 0; i < level; i++)
			{
				printf(".");
			}
		}
		switch (node->type)
		{
		case type_all:
			printf("All\n");
			printTree(node->synTree.quantor_struct.var, level + 1);
			printTree(node->synTree.quantor_struct.formula, level + 1);
			break;
		case type_exist:
			printf("EXIST\n");
			printTree(node->synTree.quantor_struct.var, level + 1);
			printTree(node->synTree.quantor_struct.formula, level + 1);
			break;
		case type_and:
			printf("AND\n");
			printTree(node->synTree.binary_struct.formula_left, level + 1);
			printTree(node->synTree.binary_struct.formula_right, level + 1);
			break;
		case type_or:
			printf("OR\n");
			printTree(node->synTree.binary_struct.formula_left, level + 1);
			printTree(node->synTree.binary_struct.formula_right, level + 1);
			break;
		case type_implication:
			printf("IMPLICATION\n");
			printTree(node->synTree.binary_struct.formula_left, level + 1);
			printTree(node->synTree.binary_struct.formula_right, level + 1);
			break;
		case type_equivalence:
			printf("EQUIVALENCE\n");
			printTree(node->synTree.binary_struct.formula_left, level + 1);
			printTree(node->synTree.binary_struct.formula_right, level + 1);
			break;
		case type_negation:
			printf("NEGATION\n");
			printTree(node->synTree.unary_junctor.formula, level + 1);
			break;
		case type_predicate:
			printf("PREDICATE: %s\n", node->synTree.predicate_struct.tableEntry->identifier);
			printTree(node->synTree.predicate_struct.argument, level + 1);
			break;
		case type_function:
			printf("FUNCTION: %s\n", node->synTree.function_struct.tableEntry->identifier);
			printTree(node->synTree.function_struct.argument, level + 1);
			break;
		case type_variable:
			printf("VARIABLE: %s\n", node->synTree.variable_struct.tableEntry->identifier);
			break;
		case type_true_node:
			printf("TRUE\n");
			break;
		case type_false_node:
			printf("FALSE\n");
			break;
		case type_number_t:
			printf("NUMBER %d\n", node->synTree.number);
			break;
		case type_argument_t:
			printTree(node->synTree.argument_struct.argument, level);
			if (node->synTree.argument_struct.next != NULL){ //try
			printTree(node->synTree.argument_struct.next, level);
			}
			break;
		default:
			printf("unknown syntax Node\n");
			exit(1);
		}
	}
}