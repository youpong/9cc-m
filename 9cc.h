#include "util.h"

/* lex */
extern char **targv;  /* remembers arguments */
extern char **arglim; /* end of arguments */
int myinput(char *, int);
#define YY_INPUT(buf, result, max) (result = myinput(buf, max))

/* yacc */
_Noreturn int yyerror(char *);

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
Node *new_node_id(char *);

/* 9cc */
extern Vector *assigns;
extern Map *var_tab;
extern int var_cnt;

/* codegen */
void gen(Node *e);
