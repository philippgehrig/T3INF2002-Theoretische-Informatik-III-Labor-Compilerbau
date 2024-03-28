#ifndef SYMTAB_H
#define SYMTAB_H
#include <stdio.h>

#define MAX 100
// mögliche Typen in PL1
enum typ{Predicate, Function, Variable};
enum var_type{Int,NoType};
typedef enum typ typ;
typedef enum var_type var_type;
// datentyp eines Symboltabelleneintrags
struct tableEntry_struct{
	char identifier[MAX];
	typ typ;
	int arity;//= Anz. der Argumente
	var_type var_type;
	struct tableEntry_struct *next; // Zeiger auf nächstes Element
};


typedef struct tableEntry_struct* tableEntry;

tableEntry insert_right(char identifier[], typ typ, int arity, var_type type);
int checkPredicate(char identifier[]);
int checkVariable(char identifier[]);
int checkFunction(char identifier[]);


void printList();

void writeOutputDeclare(FILE *f);

tableEntry search_for( char* identifier);

/*
Globale Tabelle
*/
#endif
