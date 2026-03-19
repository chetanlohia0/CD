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