/* lex */
extern char **targv; /* remembers arguments */
extern char **arglim; /* end of arguments */
int myinput(char *, int);
#define YY_INPUT(buf, result, max) (result = myinput(buf, max))

/* yacc */
_Noreturn int yyerror(char *);
