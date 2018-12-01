%{
#include "9cc.h"
#include "lex.yy.h"
#include "util.h"  
#include <stdio.h>
%}

%union {
       int val;
       char name;
       Node *node;
}

%token <val> NUMBER
%token <name> IDENT

%type <node> assign expr mul term

%%
program:   assign ';'         { vec_push(assigns, $1); }
         | assign ';' program { vec_push(assigns, $1); }
	 ;
assign:    expr            { $$ = $1; }
         | expr '=' assign { $$ = new_node('=', $1, $3); }
         ;
expr:      mul             { $$ = $1; }
         | mul  '+' expr   { $$ = new_node('+', $1, $3); }
         | mul  '-' expr   { $$ = new_node('-', $1, $3); }
         ;
mul:       term            { $$ = $1; }
         | term '*' mul    { $$ = new_node('*', $1, $3); }
         | term '/' mul    { $$ = new_node('/', $1, $3); }
         ;
term:      NUMBER          { $$ = new_node_num($1); }
         | IDENT           { $$ = new_node_id($1); }
         | '(' expr ')'    { $$ = $2; }
         ;
%%


