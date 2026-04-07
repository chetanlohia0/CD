#include <stdio.h>
#include <string.h>

#define MAX 10

char op[MAX], arg1[MAX], arg2[MAX], res[MAX];

int main() {
    int n;
    char input[20];

    printf("Enter number of statements: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        printf("Enter statement %d: ", i + 1);
        scanf("%s", input);

        // Example: t=a+b
        res[i] = input[0];
        arg1[i] = input[2];
        op[i] = input[3];
        arg2[i] = input[4];
    }

    // Quadruple
    printf("\nQuadruple Representation:\n");
    printf("Op\tArg1\tArg2\tResult\n");
    for(int i = 0; i < n; i++) {
        printf("%c\t%c\t%c\t%c\n", op[i], arg1[i], arg2[i], res[i]);
    }

    // Triple
    printf("\nTriple Representation:\n");
    printf("Index\tOp\tArg1\tArg2\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t%c\t%c\t%c\n", i, op[i], arg1[i], arg2[i]);
    }

    // Indirect Triple
    printf("\nIndirect Triple Representation:\n");
    printf("Pointer\tIndex\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t%d\n", i, i);
    }

    return 0;
}


















#include <stdio.h>
#include <string.h>

int main() {
    int n;
    char stmt[20];

    printf("Enter number of three address statements: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        printf("Enter statement %d: ", i + 1);
        scanf("%s", stmt);

        // Example: t=a+b OR d=u
        if(strlen(stmt) == 5) {
            // t=a+b
            printf("LOAD %c\n", stmt[2]);

            switch(stmt[3]) {
                case '+': printf("ADD %c\n", stmt[4]); break;
                case '-': printf("SUB %c\n", stmt[4]); break;
                case '*': printf("MUL %c\n", stmt[4]); break;
                case '/': printf("DIV %c\n", stmt[4]); break;
            }

            printf("STORE %c\n", stmt[0]);
        } 
        else if(strlen(stmt) == 3) {
            // d=u
            printf("LOAD %c\n", stmt[2]);
            printf("STORE %c\n", stmt[0]);
        }
    }

    return 0;
}