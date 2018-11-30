%{
#include "9cc.h"
#include "lex.yy.h"
#include "util.h"  
#include <stdio.h>
%}

%token NUMBER

%%
statement: expr
expr: NUMBER          { vec_push(stack, new_num_element($1)); }
    | NUMBER '+' expr { vec_push(stack, new_element('+'));
                        vec_push(stack, new_num_element($1)); }
    | NUMBER '-' expr { vec_push(stack, new_element('-'));
			vec_push(stack, new_num_element($1)); }
    ;
%%


