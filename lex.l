%{
#include "9cc.h"
#include "y.tab.h"
#include <math.h>
#include <stdio.h>
%}

%option nounput noinput

%%
[0-9][0-9]* {
    int tmp;
    sscanf(yytext, "%d", &tmp);
    yylval = tmp;
    return NUMBER;
}
\+  return '+';
-   return '-';
[ \t] ; /* ignore white space */

\n |
.   yyerror("cannot tokenize"); 
%%
