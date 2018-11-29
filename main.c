#include "9cc.h"
#include "y.tab.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  printf(".intel_syntax noprefix\n");
  printf(".global main\n");
  printf("main:\n");
  
  yyparse();
  printf("\tret\n");
  
  return EXIT_SUCCESS;
}
