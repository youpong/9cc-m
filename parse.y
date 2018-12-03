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

%type <node> expr

%token <val> NUMBER
%token <name> IDENT
%token EQ /* == */
%token NE /* != */

/* precedence table */
%right '='
%left  EQ  NE
%left  '+' '-'
%left  '*' '/'

%%
program:   expr ';'         { vec_push(assigns, $1); }
         | expr ';' program { vec_push(assigns, $1); }
	 ;
expr:   
           NUMBER          { $$ = new_node_num($1); }
         | IDENT           { $$ = new_node_id( $1); }
         | '(' expr ')'    { $$ = $2; }
         | expr '=' expr   { $$ = new_node('=', $1, $3); }
	 | expr EQ  expr   { $$ = new_node(EQ,  $1, $3); }
	 | expr NE  expr   { $$ = new_node(NE,  $1, $3); }
         | expr '+' expr   { $$ = new_node('+', $1, $3); }
         | expr '-' expr   { $$ = new_node('-', $1, $3); }
         | expr '*' expr   { $$ = new_node('*', $1, $3); }
         | expr '/' expr   { $$ = new_node('/', $1, $3); }
         ;
         ;
%%


