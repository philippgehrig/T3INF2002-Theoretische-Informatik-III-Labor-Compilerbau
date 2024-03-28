#include "symTab.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "synTree.h"
int initialized;
tableEntry actSymTable = NULL;


/**
 * @brief Function to insert a new entry into the list
 *
 * @param identifier ID
 * @param typ
 * @param arity
 * @return tableEntry the new TableENtry
 */
tableEntry insert_right(char identifier[], typ typ, int arity, var_type type)
{
	// check auf redundante definition
	if(search_for(identifier) == NULL){
	printf("SYM: Inserting %s into the symboltable with arity %d\n", identifier, arity);
	tableEntry new_tableEntry;
	new_tableEntry = (tableEntry)malloc(sizeof(struct tableEntry_struct));
	strcpy(new_tableEntry->identifier, identifier);
	new_tableEntry->typ = typ;
	new_tableEntry->arity = arity;
	new_tableEntry->var_type = type;
	new_tableEntry->next = NULL;

	// Initializing actSymTable with the first entry
	if (actSymTable == NULL)
	{
		printf("\n------------initializing symboltable----------\n");
		actSymTable = new_tableEntry;
	}
	// appending
	else
	{
		tableEntry temp = actSymTable;
		// finding the last entry
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = new_tableEntry;
		temp = NULL;
		// free(temp);
	}
	return new_tableEntry;
}
else{
	printf("ID already exists!");
}
}
/**
 * @brief Function to check, if Symboltable-Entry is of type Predicate
 * 
 * @param identifier 
 * @return int: 0 if check unsuccessfull and 1 if check successfull
 */
int checkPredicate(char identifier[]) {
	
	tableEntry temp = search_for(identifier);
	if (temp->typ == Predicate)
		return 1;
	else
		return 0;
}

/**
* @brief Function to check, if Symboltable-Entry is of type Variable
 * 
 * @param identifier 
 * @return int: 0 if check unsuccessfull and 1 if check successfull
 */
int checkVariable(char identifier[]) {

	tableEntry temp = search_for(identifier);
	if (temp->typ == Variable)
		return 1;
	else
		return 0;
}
/**
 * @brief Function to check, if Symboltable-Entry is of type Function
 * 
 * @param identifier 
 * @return int: 0 if check unsuccessfull and 1 if check successfull
 */
int checkFunction(char identifier[]) {

	tableEntry temp = search_for(identifier);
	if (temp->typ == Function)
		return 1;
	else
		return 0;
}


/**
 * @brief Function to print the table
 *
 */
void printList()
{
	printf("\n------Actual symboltable-------:\n");
	char const *typen[] = {"Predicate", "Function", "Variable"};
	char const *var_types[] = {"int", "NoType"};
	int index = 1;
	tableEntry temp = actSymTable;
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
	printf("\n-----------------------------\n", index);
}
	
/**
 * @brief Function to print the Declare to the output file 
 * 
 * @param f output file
 */
void writeOutputDeclare(FILE *f)
{
	
	char const *typen[] = {"PREDICATE", "FUNCTION", "VARIABLE"};
	char const *var_types[] = {"int", "NoType"};

	tableEntry temp = actSymTable;
	while (temp != NULL)
	{
		fprintf(f, "DECLARE ");
		fprintf(f, "%s ", typen[temp->typ]);
		fprintf(f, "%s ", temp->identifier);
		fprintf(f, ": ");
		if(temp->var_type != NoType){
			fprintf(f, "%s\n",var_types[temp->var_type]);
		}
		else{
			fprintf(f, "%d \n", temp->arity);
		}
		
		
		temp = temp->next;
	}
	temp = NULL;
}
	
/**
 * @brief  Funktion um einen Eintrag auf basis des Identifiers zu suchen
 * Zeiger geht die Liste durch, bis er den Eintrag findet oder auf NULL steht
 * 
 * @param identifier identifier, nachdem gesucht wird
 * @return tableEntry gefundener Eintrag oder NULL, wenn Suche erfolglos
 */

tableEntry search_for(char identifier[])
{
	tableEntry temp = actSymTable;
	while (temp != NULL)
	{
		if ((strcmp(temp->identifier, identifier)==0))
			return temp;
		temp = temp->next;
	}
	return NULL;
}