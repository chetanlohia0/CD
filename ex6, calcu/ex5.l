Procedure:
1. Place the following files
in a folder ex3.l , ex3.y
and a sample input file
2. Run the following flex
ex3.l or lex -d ex3.lex
3. Run the following
commands: yacc -d
ex3.yacc or bison ex3.y
gcc y.tab.c lex.yy.c
./a.out
4. Based on the input file the output is generated
Program:


/* Bison file: calc.y */
%{
#include <stdio.h>
#include <stdlib.h>
void yyerror(const char *s);
int yylex();
%}
/* Operator precedence and associativity */
%left '+' '-'
%left '*' '/'
%right UMINUS /* Unary minus */
%token NUMBER
%%
equation:
expression '\n' { printf("Result: %d\n", $1); }
;
expression:
expression '+' expression { $$ = $1 + $3; }
| expression '-' expression { $$ = $1 - $3; }
| expression '*' expression { $$ = $1 * $3; }
| expression '/' expression { $$ = $1 / $3; }
| '-' expression %prec UMINUS { $$ = -$2; } /* Unary minus */
| '(' expression ')' { $$ = $2; }
| NUMBER { $$ = $1; }
;
%%

void yyerror(const char *s) {
fprintf(stderr, "Error: %s\n", s);
}
int main() {
printf("Enter an arithmetic expression:\n");
yyparse();
return 0;
}

/* Flex file: calc.l */
%{
#include "calc.tab.h"
#include <stdio.h>
%}
%%
[0-9]+ { yylval = atoi(yytext); return NUMBER; }
[+\-*/()] { return yytext[0]; }
[ \t] { /* Ignore whitespace */ }
\n { return '\n'; }
. { printf("Invalid character: %s\n", yytext); }
%%
int yywrap() {
return 1;
}

Steps to Compile and Run:
1. Generate Bison file and Flex file
2. Compile everything
flex calc.l
bison -d calc.y
gcc calc.tab.c lex.yy.c -o calc -lm
3. Run the calculator:
./calc
Output:
Enter an arithmetic expression:
5 + 3 * 2
Result: 11