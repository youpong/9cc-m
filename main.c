#include "9cc.h"
#include "util.h"
#include "y.tab.h"
#include <stdio.h>
#include <stdlib.h>

static void gen(Node *e);
static void gen_lval(Node *);

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
  printf("\tsub rsp, %d\n", ('z'-'a' + 1) *8);
  
  while(assigns->len > 0) {
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

static void gen_lval(Node *node) {
  if(node->ty != IDENT)
    error("lvalue must var");

  printf("\tmov rax, rbp\n");
  printf("\tsub rax, %d\n",
	 ('z' - node->name + 1) * 8);
  printf("\tpush rax\n");
}

static void gen(Node *node) {
  if (node->ty == NUMBER) {
    printf("\tpush %d\n", node->val);
    return;
  }

  if (node->ty == IDENT) {
    gen_lval(node);
    printf("\tpop rax\n");
    printf("\tmov rax, [rax]\n");
    printf("\tpush rax\n");
    return;
  }

  if (node->ty == '=') {
    gen_lval(node->lhs);
    gen(node->rhs);

    printf("\tpop rdi\n");
    printf("\tpop rax\n");
    printf("\tmov [rax], rdi\n");
    printf("\tpush rdi\n");
    return;
  }
  
  gen(node->lhs);
  gen(node->rhs);

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
