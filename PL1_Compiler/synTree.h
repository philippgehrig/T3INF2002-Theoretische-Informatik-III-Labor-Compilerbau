#ifndef SYNTREE_H
#define SYNTREE_H
#include "symTab.h"

enum nodeT{all, exist, and, or, implication, equivalence, negation, predicate, function, variable,true_node, false_node, number_t, argument_t};
struct node
{
    enum nodeT nodeType; //Knotentyp zuordnen
    union {
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
		// = TRUE
		// 
        // bool True; ---------> ??
        // bool False;
		int number;
		
        struct argument { 
            struct node* argument;
            struct node* next;
        }argument_struct;
    };
    
};

// make_binary_node, ...
// Symboltabelleneintrag �bergeben und argumentliste



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

void writeOutputFormula(struct node* node, FILE *f);

void printTree(struct node* node, int level);

#endif