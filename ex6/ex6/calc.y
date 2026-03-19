%{
#include <stdio.h>
#include <stdlib.h>
void yyerror(const char *s);
int yylex();

%}

%left '+''-'
%left '*''/'
%right UMINUS
%token NUMBER

%%
equation:
    expression '\n' { printf("result:%d\n", $1); }
    ;

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

void yyerror(const char *s)
{
    fprintf(stderr, "Error:%s\n",s);
}

int main()
{
    printf("enter expression:");
    yyparse();
    return 0;
}













