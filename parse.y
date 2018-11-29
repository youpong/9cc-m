%{
#include "9cc.h"
#include "lex.yy.h"
#include <stdio.h>

  //  extern int yylval;  
%}

%token NUMBER

%%
statement: NUMBER {
  printf("\tmov rax, %d\n", $1);
 }
%%
