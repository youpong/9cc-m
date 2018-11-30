#include "9cc.h"
#include "util.h"
#include "y.tab.h"
#include <stdio.h>
#include <stdlib.h>

void codegen();

char **targv;
char **arglim;

Vector *stack;

int main(int argc, char **argv) {
  stack = new_vector();
  
  targv = argv + 1;
  arglim = argv + argc;
  

  printf(".intel_syntax noprefix\n");
  printf(".global main\n");
  printf("main:\n");

  yyparse();
  codegen();

  printf("\tret\n");

  return EXIT_SUCCESS;
}

_Noreturn int yyerror(char *msg) {
  fprintf(stderr, "%s\n", msg);
  exit(EXIT_FAILURE);
}

Element *new_num_element(int num) {
  Element *e = (Element *)malloc(sizeof(Element));
  e->type = NUMBER;
  e->val = num;
  return e;
}

Element *new_element(int type) {
  Element *e = (Element *)malloc(sizeof(Element));
  e->type = type;
  return e;
}
  
void codegen() {
  Element *e;
  
  e = vec_pop(stack);
  if (e == NULL && e->type != NUMBER)
    error("unexpected type of element\n");

  printf("\tmov rax, %d\n", e->val);

  while( (e = vec_pop(stack)) != NULL) {
    switch(e->type) {
    case '+':
      printf("\tadd rax, ");
      break;
    case '-':
      printf("\tsub rax, ");      
      break;
    case NUMBER:
      printf("%d\n", e->val);
      break;
    default:
      error("unexpected type of element\n");
      break;
    }
  }
}
