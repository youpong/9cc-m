#include "9cc.h"
#include "util.h"
#include "y.tab.h"
#include <stdio.h>
#include <stdlib.h>

char **targv;
char **arglim;

Vector *assigns;

int main(int argc, char **argv) {
  assigns = new_vector();

  targv = argv + 1;
  arglim = argv + argc;

  yyparse();

  printf(".intel_syntax noprefix\n");
  printf(".global main\n");
  printf("main:\n");

  printf("\tpush rbp\n");
  printf("\tmov rbp, rsp\n");
  printf("\tsub rsp, %d\n", ('z' - 'a' + 1) * 8);

  while (assigns->len > 0) {
    gen(vec_pop(assigns));
    printf("\tpop rax\n");
  }

  printf("\tmov rsp, rbp\n");
  printf("\tpop rbp\n");
  printf("\tret\n");

  return EXIT_SUCCESS;
}

_Noreturn int yyerror(char *msg) {
  fprintf(stderr, "%s\n", msg);
  exit(EXIT_FAILURE);
}
