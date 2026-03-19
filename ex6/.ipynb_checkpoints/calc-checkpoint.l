%{
#include "calc.tab.h"
#include<stdlib.h>
%}

%%

[0-9]+(\.[0-9]+)? {
yylval.num=atof(yytext);
return NUMBER; }
[+\-*/()]
{
return yytext[0];
}
[ \t] ;
\n {
return '\n';
}
.
{
printf("Invalid character \n");
}

%%
int yywrap()
{
return 1;
}

























