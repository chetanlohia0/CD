%{
    #include<stdio.h>
    int no_of_char=0;
    int no_of_letters=0;
%}
DIGIT[0-9]
ID [a-zA-Z]
%%
{ID} ++no_of_letters;
{DIGIT} ++no_of_char;
%%

int yywrap(){}
int main ( int argc,char **argv )
{

yylex();
printf("totl no of digits= %d",no_of_char);
printf("chr=%d",no_of_letters);
return 0;
}





