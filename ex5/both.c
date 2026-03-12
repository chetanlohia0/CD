#include <stdio.h>
#include <string.h>

int main()
{
    int n,i;
    char A;
    char prod[10][20];
    char alpha[10][20],beta[10][20];
    int a=0,b=0;

    printf("Enter Non-Terminal: ");
    scanf(" %c",&A);

    printf("Enter number of productions: ");
    scanf("%d",&n);

    printf("Enter productions (RHS only):\n");

    for(i=0;i<n;i++)
        scanf("%s",prod[i]);

    /* LEFT RECURSION */

    for(i=0;i<n;i++)
    {
        if(prod[i][0]==A)
            strcpy(alpha[a++],&prod[i][1]);
        else
            strcpy(beta[b++],prod[i]);
    }

    if(a>0)
    {
        printf("\nAfter Removing Left Recursion:\n");

        printf("%c -> ",A);

        for(i=0;i<b;i++)
            printf("%s%c' | ",beta[i],A);

        printf("\n%c' -> ",A);

        for(i=0;i<a;i++)
            printf("%s%c' | ",alpha[i],A);

        printf("#\n");
    }

    /* LEFT FACTORING */

    printf("\nAfter Left Factoring:\n");

    char prefix[20];
    int k=0;

    while(prod[0][k]==prod[1][k])
    {
        prefix[k]=prod[0][k];
        k++;
    }

    prefix[k]='\0';

    printf("%c -> %s%c'\n",A,prefix,A);

    printf("%c' -> ",A);

    for(i=0;i<n;i++)
        printf("%s | ",&prod[i][k]);

    printf("\n");

    return 0;
}