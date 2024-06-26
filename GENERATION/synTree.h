#ifndef SYNTREE_H
#define SYNTREE_H
#include "symTab.h"

enum nodeType{type_all, type_exist, type_and, type_or, type_implication, type_equivalence, type_negation, type_predicate, type_function, type_variable, type_true_node, type_false_node, type_number_t, type_argument_t};
struct node
{
    enum nodeType type;
    union synTree
    {
        struct quantor { 
            struct node* var;
            struct node* formula;
        }quantor_struct;
        struct binary_juctor {  
            struct node* formula_left;
            struct node* formula_right;
        }binary_struct;
        struct unary_juctor { 
            struct node* formula;
		}unary_junctor;
        struct predicate { 
            tableEntry tableEntry; //struct tableEntry*
            struct node* argument;
        }predicate_struct;
        struct function { 
			tableEntry tableEntry; //struct tableEntry*
            struct node* argument;
        }function_struct;
		struct variable { 
		tableEntry tableEntry; //struct tableEntry*
		}variable_struct;
		int number;
        struct boolean { 
            int value;
        }boolean_struct;
        struct argument { 
            struct node* argument;
            struct node* next;
        }argument_struct;
    }synTree;
};
    
struct node* makeAllNode(struct node* var, struct node* formula_node);

struct node* makeExistNode(struct node* var, struct node* formula_node);

struct node* makeConjunctionNode(struct node* formula_left_node, struct node* formula_right_node);

struct node* makeDisjunctionNode(struct node* formula_left_node, struct node* formula_right_node);

struct node* makeImplicationNode(struct node* formula_left_node, struct node* formula_right_node);

struct node* makeEquivalenceNode(struct node* formula_left_node, struct node* formula_right_node);

struct node* makeNegationNode(struct node* formula);

struct node* makeFunctionNode(tableEntry SymTabEntry, struct node* argumentList);

struct node* makePredicateNode(tableEntry SymTabEntry, struct node* argumentList);

struct node* makeVariableNode(tableEntry SymTabEntry);

struct node* makeTrueNode();

struct node* makeFalseNode();

struct node* makeArgumentNode(struct node* arg);

struct node* appendArgumentNode( struct node* argument_left ,struct node* argument_new);

struct node* makeNumberNode(int number);

struct node* copyOfTeilTree(struct node* node);

void  freeTeilTree(struct node* node);

void printTree(struct node* node, int level);

#endif