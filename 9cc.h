#include "util.h"

/* lex */
extern char **targv;  /* remembers arguments */
extern char **arglim; /* end of arguments */
int myinput(char *, int);
#define YY_INPUT(buf, result, max) (result = myinput(buf, max))

/* yacc */
_Noreturn int yyerror(char *);

/* 9cc */
typedef struct {
  int type; // '+', '-', NUMBER
  int val;  // value of NUMBER
} Element;

Element *new_num_element(int);
Element *new_element(int);

extern Vector *stack;

/* Node */
typedef struct Node {
  int ty; // 演算子 | ND_NUM | ND_IDENT
  struct Node *lhs;
  struct Node *rhs;
  int val;
  char *name;
} Node;

Node *new_node(int, Node *, Node *);
Node *new_node_num(int);

extern Node *node;

