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
[ \t] ; /* ignore white space */

\n |
.  return yytext[0];
%%
