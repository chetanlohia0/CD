#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 20

int n;
char prod[MAX][MAX];
char first[26][MAX], follow[26][MAX];
int fcount[26], flcount[26];
int used[26];

void add(char set[26][MAX], int count[], char nt, char c) {
    int i, idx = nt - 'A';
    for(i = 0; i < count[idx]; i++)
        if(set[idx][i] == c) return;
    set[idx][count[idx]++] = c;
}

void computeFirst() {
    int changed = 1;

    while(changed) {
        changed = 0;

        for(int i = 0; i < n; i++) {
            char A = prod[i][0];
            used[A - 'A'] = 1;

            for(int j = 2; prod[i][j] != '\0'; j++) {

                char X = prod[i][j];

                if(!isupper(X)) {
                    if(!strchr(first[A-'A'], X)) {
                        add(first, fcount, A, X);
                        changed = 1;
                    }
                    break;
                }
                else {
                    int k;
                    for(k = 0; k < fcount[X-'A']; k++) {
                        if(first[X-'A'][k] != '#')
                            add(first, fcount, A,
                                first[X-'A'][k]);
                    }
                    if(!strchr(first[X-'A'], '#'))
                        break;
                }
            }
        }
    }
}

void computeFollow() {

    add(follow, flcount, prod[0][0], '$');

    int changed = 1;

    while(changed) {
        changed = 0;

        for(int i = 0; i < n; i++) {
            char A = prod[i][0];

            for(int j = 2; prod[i][j] != '\0'; j++) {

                if(isupper(prod[i][j])) {

                    char B = prod[i][j];
                    int k = j + 1;

                    if(prod[i][k] != '\0') {

                        char next = prod[i][k];

                        if(!isupper(next)) {
                            add(follow, flcount, B, next);
                        }
                        else {
                            for(int x = 0; x < fcount[next-'A']; x++)
                                if(first[next-'A'][x] != '#')
                                    add(follow, flcount, B,
                                        first[next-'A'][x]);
                        }
                    }
                    else {
                        for(int x = 0; x < flcount[A-'A']; x++)
                            add(follow, flcount, B,
                                follow[A-'A'][x]);
                    }
                }
            }
        }
    }
}

int main() {

    printf("Use '#' for epsilon\n");
    printf("One production per line (A=alpha)\n\n");

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions:\n");
    for(int i = 0; i < n; i++)
        scanf("%s", prod[i]);

    computeFirst();
    computeFollow();

    printf("\nFIRST Sets:\n");
    for(int i = 0; i < 26; i++)
        if(used[i]) {
            printf("FIRST(%c) = { ", i+'A');
            for(int j = 0; j < fcount[i]; j++)
                printf("%c ", first[i][j]);
            printf("}\n");
        }

    printf("\nFOLLOW Sets:\n");
    for(int i = 0; i < 26; i++)
        if(used[i]) {
            printf("FOLLOW(%c) = { ", i+'A');
            for(int j = 0; j < flcount[i]; j++)
                printf("%c ", follow[i][j]);
            printf("}\n");
        }

    return 0;
}