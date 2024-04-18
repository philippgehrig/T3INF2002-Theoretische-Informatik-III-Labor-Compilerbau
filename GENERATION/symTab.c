#include "symTab.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int initialized;
tableEntry SymTable = NULL;

tableEntry insert_right(char identifier[], typ typ, int arity, var_type type)
{
    if(search_for(identifier) == NULL){
        printf("SYM: Inserting %s into the symboltable with arity %d\n", identifier, arity);
        tableEntry new_tableEntry;
        new_tableEntry = (tableEntry)malloc(sizeof(struct tableEntry_struct));
        strcpy(new_tableEntry->identifier, identifier);
        new_tableEntry->typ = typ;
        new_tableEntry->arity = arity;
        new_tableEntry->var_type = type;
        new_tableEntry->next = NULL;

        if (SymTable == NULL)
        {
            printf("\n------------initializing symboltable----------\n");
            SymTable = new_tableEntry;
        }
        else
        {
            tableEntry temp = SymTable;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = new_tableEntry;
            temp = NULL;
            free(temp);
        }
        return new_tableEntry;
    }
    else{
        printf("ID already exists!");
    }
    return NULL;
}

int checkPredicate(char identifier[])
{
    tableEntry temp = SymTable;
    while (temp != NULL)
    {
        if (strcmp(temp->identifier, identifier) == 0)
        {
            if (temp->typ == Predicate)
            {
                return 1;
            }
        }
        temp = temp->next;
    }
    return 0;
}

int checkVariable(char identifier[])
{
    tableEntry temp = SymTable;
    while (temp != NULL)
    {
        if (strcmp(temp->identifier, identifier) == 0)
        {
            if (temp->typ == Variable)
            {
                return 1;
            }
        }
        temp = temp->next;
    }
    return 0;
}

int checkFunction(char identifier[])
{
    tableEntry temp = SymTable;
    while (temp != NULL)
    {
        if (strcmp(temp->identifier, identifier) == 0)
        {
            if (temp->typ == Function)
            {
                return 1;
            }
        }
        temp = temp->next;
    }
    return 0;
}

tableEntry search_for(char *identifier)
{
    tableEntry temp = SymTable;
    while (temp != NULL)
    {
        if (strcmp(temp->identifier, identifier) == 0)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void printTable()
{
	printf("\n------Symboltable-------:\n");
	char const *typen[] = {"Predicate", "Function", "Variable"};
	char const *var_types[] = {"int", "NoType"};
	int index = 1;
	tableEntry temp = SymTable;
	while (temp != NULL)
	{
		printf("\n----%d----\n", index);
		printf("ID: %s \n", temp->identifier);
		printf("Typ: %s \n", typen[temp->typ]);
		printf("Arity: %d \n", temp->arity);
		printf("Arity Typ: %s \n",var_types[temp->var_type]);
		index++;
		temp = temp->next;
	}
	temp = NULL;
	printf("\n-----------------------------\n");
}