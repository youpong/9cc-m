#include "9cc.h"
#include "lex.yy.h"
#include "y.tab.h"
#include <stdlib.h>

char **targv;
char **arglim;

int main(int argc, char **argv) {
  targv = argv + 1;
  arglim = argv + argc;

  if (yylex() == NUMBER)
    printf("NUMBER\n");

  return EXIT_SUCCESS;
}
