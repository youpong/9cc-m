#include "9cc.h"
#include "util.h"
#include "y.tab.h"
#include <stdio.h>
#include <stdlib.h>

static void codegen(Node *node);

char **targv;
char **arglim;

Vector *assigns;

int main(int argc, char **argv) {
  assigns = new_vector();

  targv = argv + 1;
  arglim = argv + argc;

  printf(".intel_syntax noprefix\n");
  printf(".global main\n");
  printf("main:\n");

  yyparse(); 

  while(assigns->len > 0) {
    codegen(vec_pop(assigns));
    printf("\tpop rax\n");    
  }

  printf("\tret\n");

  return EXIT_SUCCESS;
}

_Noreturn int yyerror(char *msg) {
  fprintf(stderr, "%s\n", msg);
  exit(EXIT_FAILURE);
}

static void codegen(Node *node) {
  if (node->ty == NUMBER) {
    printf("\tpush %d\n", node->val);
    return;
  }

  codegen(node->lhs);
  codegen(node->rhs);

  printf("\tpop rdi\n");
  printf("\tpop rax\n");

  switch (node->ty) {
  case '+':
    printf("\tadd rax, rdi\n");
    break;
  case '-':
    printf("\tsub rax, rdi\n");
    break;
  case '*':
    printf("\tmul rdi\n");
    break;
  case '/':
    printf("\tmov rdx, 0\n");
    printf("\tdiv rdi\n");
    break;
  default:
    error("unknown operator");
  }

  printf("\tpush rax\n");
}
