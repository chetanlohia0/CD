%{
    #include<math.h>
%}
DIGIT [0-9]
ID [a-z][a-z0-9]*
%%
{DIGIT}+ {printf( "An integer: %s (%d)\n", yytext,atoi( yytext ) );}
{DIGIT}+"."{DIGIT}* {printf( "a float: %s (%g)\n", yytext,atof( yytext ) );}
int|main|return|if|then|begin|end|procedure|function {printf("A keyword:%s\n", yytext);}
{ID} printf( "An identifier: %s\n", yytext);
"+"|"-"|"*"|"/" printf("An opertor: %s\n",yytext);
"{"[\^{}}\n]*"}" 
[ \t\n]+
,|; {printf("special symols: %s\n", yytext);}

. printf( "Unrecogized character: %s\n", yytext );
%%

int yywrap(){}
int main ( int argc, char **argv )
{
FILE *fp;
char filename[50];
printf("Enter the filename: \n");
scanf("%s",filename);
fp= fopen(filename,"r");
yyin = fp;
yylex();
return 0;
}





