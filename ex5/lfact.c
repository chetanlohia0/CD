#include <stdio.h>
#include <string.h>

int main()
{
    int n,i;
    char A;
    char prod[10][20];
    char prefix[20];

    printf("Enter Non-Terminal: ");
    scanf(" %c",&A);

    printf("Enter number of productions: ");
    scanf("%d",&n);

    printf("Enter productions (RHS only):\n");

    for(i=0;i<n;i++)
        scanf("%s",prod[i]);

    int k=0;

    while(1)
    {
        char c = prod[0][k];

        for(i=1;i<n;i++)
            if(prod[i][k]!=c)
                goto stop;

        prefix[k]=c;
        k++;
    }

stop:

    prefix[k]='\0';

    printf("\nAfter Left Factoring:\n");

    printf("%c -> %s%c'\n",A,prefix,A);

    printf("%c' -> ",A);

    for(i=0;i<n;i++)
        printf("%s | ",&prod[i][k]);

    printf("\n");

    return 0;
}