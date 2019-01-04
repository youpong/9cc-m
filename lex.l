%{
#include "9cc.h"
#include "y.tab.h"
#include <string.h>
#include <math.h>
#include <stdio.h>
%}

%option nounput noinput


ws     [ \t]
digit  [0-9]
letter [a-zA-Z]

%%


{digit}+ {
      int tmp;
      sscanf(yytext, "%d", &tmp);
      yylval.val = tmp;
      return NUMBER;
}
{letter}({letter}|{digit})* {
      yylval.name = strdup(yytext);
      return IDENT;
}

"="   return '=';
"=="  return EQ;
"!="  return NE;

"+"   return '+';
"-"   return '-';
"*"   return '*';
"/"   return '/';
"("   return '(';
")"   return ')';

";"   return ';';

{ws}+ ; /* ignore white space */
\n    lineno++;
.     yyerror("cannot tokenize");
%%

// 以下の5つの行でコメントを使えるようになる（と思う）。
// %s COMMENT COMMENT2
//"/*"          { BEGIN COMMENT; }
//<COMMENT>.    ;
//<COMMENT>\n   { lineno++; }
//<COMMENT>"*/" { BEGIN 0; }
