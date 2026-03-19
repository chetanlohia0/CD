
#include<stdio.h>
#define MAX 10

int n;
int trans[MAX][2];
int final[MAX];
int group[MAX], new_group[MAX];

int main(){
    int i,j,k;
    int groups;
    
    printf("Enter number of states: ");
    scanf("%d", &n);
    printf("\nEnter transition table (input 0 and 1): \n");
    
    for(int i = 0; i < n; i++){
        printf("State %d: ", i);
        scanf("%d %d", &trans[i][0], &trans[i][1]);
    }
    
    printf("\nEnter final states (1 = final, 0 = non-final):\n");
    
    for(i = 0; i < n; i++){
        scanf("%d", &final[i]);
    }
    
    for(i = 0; i < n; i++){
        if(final[i])
            group[i] = 1;
        else
            group[i] = 0;
    }

    int changed;
    
    do{
        changed = 0;
        groups = 2;
        
        for(i = 0; i < n; i++)
            new_group[i] = group[i];

        for(i = 0; i < n; i++){
            for(j = i + 1; j < n; j++){
                if(group[i] == group[j]){
                    for(k = 0; k < 2; k++){
                        if(group[trans[i][k]] != group[trans[j][k]]){
                            new_group[j] = groups++;
                            changed = 1;
                            break;
                        }
                    }
                }
            }
        }
        
        for(i = 0; i < n; i++)
            group[i] = new_group[i];    
        
    } while(changed);

    printf("\nMinimised DFA Groups: \n");

    for(i = 0; i < n; i++){
        printf("State %d -> Group %d\n", i, group[i]);
    }

    return 0;
}