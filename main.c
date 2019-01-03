#include "9cc.h"
#include "util.h"
#include "y.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char **targv;
char **arglim;

Vector *assigns;
Map *var_tab;
int var_cnt;

int lineno = 1;

int main(int argc, char **argv) {
  bool ast_flg = false;
  assigns = new_vector();
  var_tab = new_map();
  var_cnt = 0;

  if (argc >= 2 && strcmp(argv[1], "-ast") == 0) {
    ast_flg = true;
    argc--;
    argv++;
  }
  
  targv = argv + 1;
  arglim = argv + argc;

  yyparse();

  if (ast_flg == true) {
    printf("graph graphname {\n");
    for (int i = 0; i < assigns->len; i++)
      p_tree((Node *)assigns->data[i]);
    printf("}\n");
    return EXIT_SUCCESS;
  }


  printf(".intel_syntax noprefix\n");
  printf(".global main\n");
  printf("main:\n");

  printf("\tpush rbp\n");
  printf("\tmov rbp, rsp\n");
  printf("\tsub rsp, %d\n", var_cnt * 8);

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
