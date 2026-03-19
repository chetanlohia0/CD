#include<stdio.h>
#include<string.h>
#define MAX 20 
#define LEN 100

int main()
{
    char nonTerminal;
    char production[MAX][LEN];
    char alpha[MAX][LEN],beta[MAX][LEN];
    int i, count;
int alphacount=0,betacount=0;
    printf("enter the non termainal:");
    scanf(" %c",&nonTerminal);
    printf("enter the no of production: ");
    scanf("%d",&count);
    printf("enter the production (without A-> part):\n");
    for(i=0;i<count;i++)
{
scanf("%s",production[i]);
}

for (i=0;i<count;i++)
{
if(production[i][0]== nonTerminal ){
strcpy(alpha[alphacount],production[i]+1);
alphacount++;
}
else{
strcpy(beta[betacount],production[i]);
betacount++;
}
}
if (alphacount==0){
printf("\n No of immediate left recursion found:\n");
return 0;
}
printf("grammar after removing left recursion:\n");
printf("%c -> ",nonTerminal);
for(i=0;i<betacount;i++)
{
printf("%s%c'", beta[i],nonTerminal);
    if(i != betacount -1 )
        printf(" | ");
}
printf("\n");
printf("%c' ->",nonTerminal);
for(i=0;i<alphacount;i++)
{
printf("%s%c'",alpha[i],nonTerminal);
    if (i!= alphacount -1 )
        printf(" | ");
}
    printf (" | {E} \n");
return 0;
}





















    
    