#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 20

int n;
char prod[MAX][MAX];

char first[26][MAX], follow[26][MAX];
int fcount[26], flcount[26];

char table[26][MAX][MAX];
int used[26];

char terminals[MAX];
int tcount = 0;

void addTerminal(char c) {
    if (isupper(c) || c == '#') return;

    for (int i = 0; i < tcount; i++)
        if (terminals[i] == c) return;

    terminals[tcount++] = c;
}
    
    void addSet(char set[26][MAX], int count[], char A, char c) {
    int idx = A - 'A';
    for (int i = 0; i < count[idx]; i++)
        if (set[idx][i] == c) return;

    set[idx][count[idx]++] = c;
}

void computeFirst() {

    int changed = 1;

    while (changed) {

        +
        changed = 0;

        for (int i = 0; i < n; i++) {

            char A = prod[i][0];
            used[A - 'A'] = 1;

            int nullable = 1;

            for (int j = 2; prod[i][j] != '\0'; j++) {

                char X = prod[i][j];

                // If terminal
                if (!isupper(X)) {

                    if (!strchr(first[A - 'A'], X)) {
                        addSet(first, fcount, A, X);
                        changed = 1;
                    }

                    nullable = 0;
                    break;
                }

                // If non-terminal
                else {

                    for (int k = 0; k < fcount[X - 'A']; k++) {

                        char symbol = first[X - 'A'][k];

                        if (symbol != '#') {

                            if (!strchr(first[A - 'A'], symbol)) {
                                addSet(first, fcount, A, symbol);
                                changed = 1;
                            }
                        }
                    }

                    if (!strchr(first[X - 'A'], '#')) {
                        nullable = 0;
                        break;
                    }
                }
            }

            if (nullable) {
                if (!strchr(first[A - 'A'], '#')) {
                    addSet(first, fcount, A, '#');
                    changed = 1;
                }
            }
        }
    }
}
void computeFollow() {

    addSet(follow, flcount, prod[0][0], '$');

    int changed = 1;

    while (changed) {

        changed = 0;

        for (int i = 0; i < n; i++) {

            char A = prod[i][0];

            for (int j = 2; prod[i][j] != '\0'; j++) {

                if (isupper(prod[i][j])) {

                    char B = prod[i][j];
                    int nullable = 1;

                    for (int k = j + 1; prod[i][k] != '\0'; k++) {

                        char next = prod[i][k];

                        if (!isupper(next)) {

                            if (!strchr(follow[B-'A'], next)) {
                                addSet(follow, flcount, B, next);
                                changed = 1;
                            }

                            nullable = 0;
                            break;
                        }
                        else {

                            for (int x = 0; x < fcount[next-'A']; x++) {

                                char symbol = first[next-'A'][x];

                                if (symbol != '#') {

                                    if (!strchr(follow[B-'A'], symbol)) {
                                        addSet(follow, flcount, B, symbol);
                                        changed = 1;
                                    }
                                }
                            }

                            if (!strchr(first[next-'A'], '#')) {
                                nullable = 0;
                                break;
                            }
                        }
                    }

                    if (nullable) {

                        for (int x = 0; x < flcount[A-'A']; x++) {

                            char symbol = follow[A-'A'][x];

                            if (!strchr(follow[B-'A'], symbol)) {
                                addSet(follow, flcount, B, symbol);
                                changed = 1;
                            }
                        }
                    }
                }
            }
        }
    }
}
int getTerminalIndex(char c) {
    for (int i = 0; i < tcount; i++)
        if (terminals[i] == c) return i;
    return -1;
}

void constructTable() {

    for (int i = 0; i < n; i++) {

        char A = prod[i][0];
        int nullable = 1;

        for (int j = 2; prod[i][j] != '\0'; j++) {

            char X = prod[i][j];

            if (!isupper(X)) {
                int col = getTerminalIndex(X);

                if (strlen(table[A - 'A'][col]) != 0)
                    printf("Conflict at M[%c,%c]\n", A, X);

                strcpy(table[A - 'A'][col], prod[i]);
                nullable = 0;
                break;
            }
            else {
                for (int k = 0; k < fcount[X - 'A']; k++) {

                    char t = first[X - 'A'][k];

                    if (t != '#') {
                        int col = getTerminalIndex(t);

                        if (strlen(table[A - 'A'][col]) != 0)
                            printf("Conflict at M[%c,%c]\n", A, t);

                        strcpy(table[A - 'A'][col], prod[i]);
                    }
                }

                if (!strchr(first[X - 'A'], '#')) {
                    nullable = 0;
                    break;
                }
            }
        }

        if (nullable) {
            for (int k = 0; k < flcount[A - 'A']; k++) {
                int col = getTerminalIndex(follow[A - 'A'][k]);

                if (strlen(table[A - 'A'][col]) != 0)
                    printf("Conflict at M[%c,%c]\n", A,
                           follow[A - 'A'][k]);

                strcpy(table[A - 'A'][col], prod[i]);
            }
        }
    }
}

void printFirstFollow() {

    printf("\nFIRST Sets:\n");
    for (int i = 0; i < 26; i++)
        if (used[i]) {
            printf("FIRST(%c) = { ", i + 'A');
            for (int j = 0; j < fcount[i]; j++)
                printf("%c ", first[i][j]);
            printf("}\n");
        }

    printf("\nFOLLOW Sets:\n");
    for (int i = 0; i < 26; i++)
        if (used[i]) {
            printf("FOLLOW(%c) = { ", i + 'A');
            for (int j = 0; j < flcount[i]; j++)
                printf("%c ", follow[i][j]);
            printf("}\n");
        }
}

void printTable() {

    printf("\nPREDICTIVE PARSING TABLE\n\n");

    printf("%10s", "");
    for (int i = 0; i < tcount; i++)
        printf("%10c", terminals[i]);
    printf("\n");

    for (int i = 0; i < 26; i++) {
        if (used[i]) {
            printf("%10c", i + 'A');
            for (int j = 0; j < tcount; j++) {
                if (strlen(table[i][j]) != 0)
                    printf("%10s", table[i][j]);
                else
                    printf("%10s", "-");
            }
            printf("\n");
        }
    }
}

int main() {

    printf("Use '#' for epsilon\n");
    printf("One production per line (A=alpha)\n\n");

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions:\n");

    for (int i = 0; i < n; i++) {
        scanf("%s", prod[i]);

        used[prod[i][0] - 'A'] = 1;

        for (int j = 2; prod[i][j] != '\0'; j++)
            addTerminal(prod[i][j]);
    }

    addTerminal('$');

    computeFirst();
    computeFollow();
    constructTable();

    printFirstFollow();
    printTable();

    return 0;
}