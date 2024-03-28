
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yyerror(char* err)
{
   printf("Error: %s\n", err);
   return 0;
}

