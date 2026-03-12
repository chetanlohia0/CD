%{
int count = 0;
%}
%%
[A-Z] {printf("%s capital letter\n", yytext);
count++;}
. {printf("%s not a capital letter\n", yytext);}
\n {return 0;}
%%
int yywrap(){}
int main(){
yylex();
printf("\nNumber of Capital letters in the given input - %d\n", count);
return 0;
}







int no_of_lines = 0;
int no_of_chars = 0;
%}
%%
\n ++no_of_lines;
. ++no_of_chars;

end return 0;
%%
/*** User code section***/
int yywrap(){}
int main(int argc, char **argv)
{
yylex();
printf("number of lines = %d, number of chars = %d\n",
no_of_lines, no_of_chars );
return 0;
}