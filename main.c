#include "9cc.h"
#include "y.tab.h"
#include <stdio.h>
#include <stdlib.h>

char **targv;
char **arglim;

int main(int argc, char **argv) {
  targv = argv + 1;
  arglim = argv + argc;

  printf(".intel_syntax noprefix\n");
  printf(".global main\n");
  printf("main:\n");

  yyparse();

  printf("\tret\n");

  return EXIT_SUCCESS;
}

_Noreturn int yyerror(char *msg) {
  fprintf(stderr, "%s\n", msg);
  exit(EXIT_FAILURE);
}
