%{
#include "9cc.h"
#include "lex.yy.h"
#include "util.h"  
#include <stdio.h>
%}

%union {
       int val;
       Node *node;
}

%token <val> NUMBER

%type <node> mul expr term

%%
statement: expr          { node = $1; }
         ;
expr:      mul           { $$ = $1; }
         | mul  '+' expr { $$ = new_node('+', $1, $3); }
         | mul  '-' expr { $$ = new_node('-', $1, $3); }
         ;
mul:       term          { $$ = $1; }
         | term '*' mul  { $$ = new_node('*', $1, $3); }
	 | term '/' mul  { $$ = new_node('/', $1, $3); }
	 ;
term:      NUMBER        { $$ = new_node_num($1); }
         | '(' expr ')'  { $$ = $2; }
	 ;
%%


