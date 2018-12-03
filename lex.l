%{
#include "9cc.h"
#include "y.tab.h"
#include <string.h>
#include <math.h>
#include <stdio.h>
%}

%option nounput noinput

%%
[0-9][0-9]* {
      int tmp;
      sscanf(yytext, "%d", &tmp);
      yylval.val = tmp;
      return NUMBER;
}
[a-z][a-zA-Z0-9]* {
      yylval.name = strdup(yytext);
      return IDENT;
}
==    return EQ;
!=    return NE;
\+    return '+';
-     return '-';
\*    return '*';
\/    return '/';
\(    return '(';
\)    return ')';
;     return ';';
=     return '=';
[ \t] ; /* ignore white space */

\n |
.     yyerror("cannot tokenize");
%%
