%{
#include "9cc.h"
#include "y.tab.h"
#include <string.h>
#include <math.h>
#include <stdio.h>
%}

%option nounput noinput

delim    [ \t]
digit    [0-9]
letter   [a-zA-Z]

ws       {delim}+
number   {digit}+
id       {letter}({letter}|{digit})*

%%

{ws}     { ; /* ignore white space */ }

{number} {
      int tmp;
      sscanf(yytext, "%d", &tmp);
      yylval.val = tmp;
      return NUMBER;
}

{id}     {
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

\n    lineno++;
.     yyerror("cannot tokenize");

%%

// 以下の5つの行でコメントを使えるようになる（と思う）。
// %s COMMENT COMMENT2
//"/*"          { BEGIN COMMENT; }
//<COMMENT>.    ;
//<COMMENT>\n   { lineno++; }
//<COMMENT>"*/" { BEGIN 0; }
