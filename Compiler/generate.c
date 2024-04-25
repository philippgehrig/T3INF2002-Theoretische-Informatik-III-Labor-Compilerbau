#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "symTab.h"
#include "generate.h"


void generate(struct node *node)
{
    generate_helper(node, NULL, false);
}

/**
 * Generates code for a given node in the abstract syntax tree (AST).
 *
 * @param node The current node in the AST.
 * @param parent The parent node of the current node.
 * @param right A boolean value indicating whether the current node is the right child of its parent.
 */
void generate_helper(struct node *node, struct node *parent, bool right)
{
    if (node == NULL)
        return;

    // The initial entry point for each node's generation should not directly use addBracket
    if (parent == NULL)
    {
        switch (node->type)
        {
        case type_all:
            printf("ALL[");
            generate_helper(node->synTree.quantor_struct.var, node, false);
            printf("] ");
            generate_helper(node->synTree.quantor_struct.formula, node, false);
            break;
        case type_exist:
            printf("EXIST[");
            generate_helper(node->synTree.quantor_struct.var, node, false);
            printf("] ");
            generate_helper(node->synTree.quantor_struct.formula, node, false);
            break;
        case type_and:
            generate_helper(node->synTree.binary_struct.formula_left, node, false);
            printf(" & ");
            generate_helper(node->synTree.binary_struct.formula_right, node, true);
            break;
        case type_or:
            generate_helper(node->synTree.binary_struct.formula_left, node, false);
            printf(" | ");
            generate_helper(node->synTree.binary_struct.formula_right, node, true);
            break;
        case type_implication:
            generate_helper(node->synTree.binary_struct.formula_left, node, false);
            printf(" -> ");
            generate_helper(node->synTree.binary_struct.formula_right, node, true);
            break;
        case type_equivalence:
            generate_helper(node->synTree.binary_struct.formula_left, node, false);
            printf(" <-> ");
            generate_helper(node->synTree.binary_struct.formula_right, node, true);
            break;
        case type_negation:
            printf("~ ");
            generate_helper(node->synTree.unary_junctor.formula, node, false);
            break;
        case type_predicate:
            // printf("PREDICATE ");
            printf("%s(", node->synTree.predicate_struct.tableEntry->identifier);
            generate_helper(node->synTree.predicate_struct.argument, node, false);
            printf(")");
            break;
        case type_function:
            // printf("FUNCTION ");
            printf("%s(", node->synTree.function_struct.tableEntry->identifier);
            generate_helper(node->synTree.function_struct.argument, node, false);
            printf(") ");
            break;
        case type_variable:
            printf("%s", node->synTree.variable_struct.tableEntry->identifier);
            break;
        case type_number_t:
            printf("%d", node->synTree.boolean_struct.value);
            break;
        case type_true_node:
            printf("TRUE");
            break;
        case type_false_node:
            printf("FALSE");
            break;
        case type_argument_t:
            generate_helper(node->synTree.argument_struct.argument, node, false);
            if (node->synTree.argument_struct.next != NULL)
            {
                printf(", ");
                generate_helper(node->synTree.argument_struct.next, node, false);
            }
            break;
        default:
            printf("default");
            break;
        }
    }
    else
    {
        // If not root node, decide on brackets based on parent context
        addBracket(node, right, parent);
        return;
    }
}

/**
 * Adds a bracket to the syntax tree.
 *
 * This function adds a bracket node to the syntax tree. The bracket can be added either on the left or right side of the given node.
 *
 * @param node The node to which the bracket will be added.
 * @param right A boolean value indicating whether the bracket should be added on the right side (true) or left side (false) of the node.
 * @param parent The parent node of the given node.
 */
void addBracket(struct node *node, bool right, struct node *parent)
{
    if (node == NULL)
        return;

    bool needsBrackets = false;

    if (parent != NULL)
    {
        switch (parent->type)
        {
        case type_negation:
            // Avoid brackets for simple negations directly applied
            needsBrackets = !(node->type == type_predicate || node->type == type_function || node->type == type_variable || node->type == type_number_t || node->type == type_true_node || node->type == type_false_node);
            break;
        case type_and:
        case type_or:
            // Logical operators might need brackets depending on their interaction with other operators
            if (node->type == type_implication || node->type == type_equivalence || (node->type == type_or && parent->type == type_and))
            {
                needsBrackets = true;
            }
            break;
        case type_implication:
        case type_equivalence:
            // Implication and equivalence are the least tightly binding and right-associative
            // Reduce bracket use: only add if switching between different types or for clarity in complex expressions
            // needsBrackets = right && (node->type != parent->type);
            break;
        default:
            break;
        }
    }

    if (needsBrackets)
    {
        printf("(");
        generate(node);
        printf(")");
    }
    else generate(node);
}
