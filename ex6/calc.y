%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int yyerror(const char *s);
int yylex();

%}

%union{
double num;
}
%token <num> NUMBER
%type <num> expression

%left '+' '-'
%left '*' '/'
%right UMINUS

%%
input:
    expression { printf("result:%.2lf\n", $1); };
    expression:
    expression '+' expression { $$= $1 + $3 ;}
    | expression '-' expression { $$ = $1 -$3;}
    | expression '*' expression { $$ = $1 *$3;}
    | expression '/' expression { $$ = $1 / $3;}
    | '-'expression %prec UMINUS { $$ = -$2;} 
    | '(' expression ')' {$$=$2;}
    | NUMBER { $$ = $1;}
;
%%

int yyerror(const char *s)
{
printf("Error:%s\n",s);
return 0;
}
int main()
{
printf("enter expression:");
yyparse();
return 0;
}













