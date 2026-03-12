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

    for(i=0;i<n;i++)
    {
        if(prod[i][0]==A)
            strcpy(alpha[a++],&prod[i][1]);
        else
            strcpy(beta[b++],prod[i]);
    }

    if(a==0)
    {
        printf("\nNo Left Recursion\n");
        return 0;
    }

    printf("\nAfter Removing Left Recursion:\n");

    printf("%c -> ",A);

    for(i=0;i<b;i++)
        printf("%s%c' | ",beta[i],A);

    printf("\n%c' -> ",A);

    for(i=0;i<a;i++)
        printf("%s%c' | ",alpha[i],A);

    printf("#\n");

    return 0;
}