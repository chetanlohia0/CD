#include <stdio.h>
#include <string.h>

#define MAX 20

char stack[MAX], input[MAX], productions[MAX][MAX];
int top = -1;
int n; // number of productions

// Push onto stack
void push(char c) {
    stack[++top] = c;
    stack[top + 1] = '\0';
}

// Remove k characters from stack
void pop(int k) {
    top -= k;
    stack[top + 1] = '\0';
}

// Try to reduce the stack
int reduce() {
    for (int i = 0; i < n; i++) {
        char lhs = productions[i][0];     // Left-hand side
        char rhs[MAX];
        int j = 0;

        // Extract RHS (after ->)
        for (int k = 3; productions[i][k] != '\0'; k++) {
            rhs[j++] = productions[i][k];
        }
        rhs[j] = '\0';

        int len = strlen(rhs);

        // Check if RHS matches top of stack
        if (top + 1 >= len) {
            if (strncmp(&stack[top - len + 1], rhs, len) == 0) {
                pop(len);
                push(lhs);
                printf("%-15s %-15s Reduce %s\n", stack, input, productions[i]);
                return 1; // reduction happened
            }
        }
    }
    return 0; // no reduction
}

int main() {
    int i = 0, ip = 0;

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (format: A->xyz):\n");
    for (i = 0; i < n; i++) {
        scanf("%s", productions[i]);
    }

    printf("Enter input string: ");
    scanf("%s", input);

    strcat(input, "$"); // append $

    // Initialize stack with $
    stack[++top] = '$';
    stack[top + 1] = '\0';

    printf("\nStack           Input           Action\n");
    printf("------------------------------------------------\n");

    while (1) {
        // Shift
        push(input[ip]);
        printf("%-15s %-15s Shift %c\n", stack, input + ip + 1, input[ip]);
        ip++;

        // Try reduction repeatedly
        while (reduce());

        // Accept condition
        if (strcmp(stack, "$S") == 0 && input[ip] == '$') {
            printf("%-15s %-15s Accept\n", stack, input + ip);
            break;
        }

        // Reject condition
        if (input[ip] == '\0') {
            printf("Rejected\n");
            break;
        }
    }

    return 0;
}