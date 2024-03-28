#ifndef SYMTAB_H
#define SYMTAB_H

#define MAX 101

enum typ {Predicate, Function, Variable};
enum var_type {Int, NoType};
typedef enum typ typ;
typedef enum var_type var_type;

struct tableEntry_struct {
    char identifier[MAX];
    typ typ; // Typ des Eintrags
    int arity; // Anzahl der Argumente
    var_type var_type; // Art der Variablen
    struct tableEntry_struct *next; //Zeiger auf nächstes Element in der Liste
};

typedef struct tableEntry_struct* tableEntry;

tableEntry insert_right(char identifier[], typ typ, int arity, var_type type);
int checkPredicate(char identifier[]);
int checkVariable(char identifier[]);
int checkFunction(char identifier[]);
tableEntry search_for(char *identifier);
void printTable();
#endif // SYMTAB_H