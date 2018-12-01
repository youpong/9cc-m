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
      yylval.val = tmp;
      return NUMBER;
}
[a-z] {
      yylval.name = yytext[0];
      return IDENT;
}
\+    return '+';
-     return '-';
\*    return '*';
\/    return '/';
\(    return '(';
\)    return ')';
;     return ';';
[ \t] ; /* ignore white space */

\n |
.     yyerror("cannot tokenize");
%%
