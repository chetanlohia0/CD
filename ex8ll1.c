#include<stdio.h>
#include<string.h>
#include<ctype.h>

char prod[10][10];
char first[10][10];
char follow[10][10];
char table[10][10][10];

char nt[10],t[10];
int ntc=0,tc=0,n;

void add(char *set,char c)
{
    if(!strchr(set,c))
    {
        int l=strlen(set);
        set[l]=c;
        set[l+1]='\0';
    }
}

void firstSet(char c,char *res)
{
    int i;

    if(!isupper(c))
    {
        add(res,c);
        return;
    }

    for(i=0;i<n;i++)
    {
        if(prod[i][0]==c)
        {
            if(prod[i][2]=='#')
                add(res,'#');
            else
                firstSet(prod[i][2],res);
        }
    }
}

void followSet(char c,char *res)
{
    int i,j;

    if(prod[0][0]==c)
        add(res,'$');

    for(i=0;i<n;i++)
    {
        for(j=2;prod[i][j];j++)
        {
            if(prod[i][j]==c)
            {
                if(prod[i][j+1])
                {
                    if(!isupper(prod[i][j+1]))
                        add(res,prod[i][j+1]);
                }
                else if(c!=prod[i][0])
                    followSet(prod[i][0],res);
            }
        }
    }
}

int main()
{
    int i,j;

    printf("Enter number of productions: ");
    scanf("%d",&n);

    printf("Enter productions (A=BC format):\n");

    for(i=0;i<n;i++)
        scanf("%s",prod[i]);

    /* collect non-terminals */

    for(i=0;i<n;i++)
    {
        if(!strchr(nt,prod[i][0]))
            nt[ntc++]=prod[i][0];
    }

    /* collect terminals */

    for(i=0;i<n;i++)
    {
        for(j=2;prod[i][j];j++)
        {
            if(!isupper(prod[i][j]) && prod[i][j]!='#')
                if(!strchr(t,prod[i][j]))
                    t[tc++]=prod[i][j];
        }
    }

    t[tc++]='$';

    /* FIRST */

    printf("\nFIRST sets\n");

    for(i=0;i<ntc;i++)
    {
        firstSet(nt[i],first[i]);

        printf("FIRST(%c) = { ",nt[i]);
        for(j=0;first[i][j];j++)
            printf("%c ",first[i][j]);
        printf("}\n");
    }

    /* FOLLOW */

    printf("\nFOLLOW sets\n");

    for(i=0;i<ntc;i++)
    {
        followSet(nt[i],follow[i]);

        printf("FOLLOW(%c) = { ",nt[i]);
        for(j=0;follow[i][j];j++)
            printf("%c ",follow[i][j]);
        printf("}\n");
    }

    /* construct table */

    for(i=0;i<n;i++)
    {
        char A=prod[i][0];
        char a=prod[i][2];

        int row=strchr(nt,A)-nt;

        if(a=='#')
        {
            for(j=0;follow[row][j];j++)
            {
                int col=strchr(t,follow[row][j])-t;
                strcpy(table[row][col],prod[i]);
            }
        }
        else
        {
            if(!isupper(a))
            {
                int col=strchr(t,a)-t;
                strcpy(table[row][col],prod[i]);
            }
        }
    }

    /* print table */

    printf("\nPredictive Parsing Table\n\n");

    printf("NT/T\t");

    for(i=0;i<tc;i++)
        printf("%c\t",t[i]);

    printf("\n");

    for(i=0;i<ntc;i++)
    {
        printf("%c\t",nt[i]);

        for(j=0;j<tc;j++)
        {
            if(strlen(table[i][j]))
                printf("%s\t",table[i][j]);
            else
                printf("-\t");
        }

        printf("\n");
    }

    return 0;
}