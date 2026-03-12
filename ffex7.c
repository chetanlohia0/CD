#include<stdio.h>
#include<ctype.h>
#include<string.h>

int n;
char prod[10][10];
int used[26];

void FIRST(char c)
{
    int i;

    if(!isupper(c))
    {
        printf("%c ",c);
        return;
    }

    for(i=0;i<n;i++)
    {
        if(prod[i][0]==c)
        {
            if(prod[i][2]=='#')
                printf("# ");

            else if(!isupper(prod[i][2]))
                printf("%c ",prod[i][2]);

            else
                FIRST(prod[i][2]);
        }
    }
}

void FOLLOW(char c)
{
    int i,j;

    if(prod[0][0]==c)
        printf("$ ");

    for(i=0;i<n;i++)
    {
        for(j=2;j<strlen(prod[i]);j++)
        {
            if(prod[i][j]==c)
            {
                if(prod[i][j+1]!='\0')
                {
                    if(prod[i][j+1] != '#')
                        FIRST(prod[i][j+1]);
                }

                else if(c!=prod[i][0])
                    FOLLOW(prod[i][0]);
            }
        }
    }
}

int main()
{
    int i;

    printf("Enter number of productions: ");
    scanf("%d",&n);

    printf("Enter productions (A=BC format):\n");

    for(i=0;i<n;i++)
        scanf("%s",prod[i]);

    printf("\nFIRST sets:\n");

    memset(used,0,sizeof(used));

    for(i=0;i<n;i++)
    {
        char c=prod[i][0];

        if(!used[c-'A'])
        {
            used[c-'A']=1;
            printf("FIRST(%c) = { ",c);
            FIRST(c);
            printf("}\n");
        }
    }

    printf("\nFOLLOW sets:\n");

    memset(used,0,sizeof(used));

    for(i=0;i<n;i++)
    {
        char c=prod[i][0];

        if(!used[c-'A'])
        {
            used[c-'A']=1;
            printf("FOLLOW(%c) = { ",c);
            FOLLOW(c);
            printf("}\n");
        }
    }

    return 0;
}