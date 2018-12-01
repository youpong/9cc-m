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

extern Vector *stack;

Element *new_num_element(int);
Element *new_element(int);
