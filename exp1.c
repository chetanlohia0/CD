#include<stdio.h>
#include<string.h>
#define MAX 10

int nfa[MAX][MAX][MAX], nfa_cnt[MAX][MAX];
int dfa[100][MAX], dfa_tr[100][MAX];
int n,m,dfa_cnt=0;

int same(int a[], int b[]){
    for(int i=0; i<n; i++)
        if(a[i]!=b[i]) return 0;
      return 1;
}
int find(int s[]){
    for(int i=0; i<dfa_cnt; i++)
        if(same(dfa[i],s)) return i;
      return -1;
}
void print(int s[]){
    printf("{");
for(int i=0; i<n; i++)
    if(s[i]) printf("%d", i);
    printf("}");
}

int main(){
    printf("Enter NFA states:");
    scanf("%d", &n);
    printf("Enter input symbols;");
    scanf("%d", &m);
for(int i=0; i<n; i++)
    for(int j=0; j<m; j++){
printf("Trasition from %d on %d:", i,j);
scanf("%d",&nfa_cnt[i][j]);
for(int k=0; k<nfa_cnt[i][j]; k++)
    scanf("%d", &nfa[i][j][k]);
    }
dfa[0][0]=1;
dfa_cnt=1;
for(int i=0; i<dfa_cnt; i++){
for(int j=0; j<m; j++){
int next[MAX]={0};
for(int s=0; s<n; s++)
    if(dfa[i][s])
        for(int k=0; k<nfa_cnt[s][j]; k++)
            next[nfa[s][j][k]]= 1;
int pos = find(next);
if(pos== -1){
memcpy(dfa[dfa_cnt],next,sizeof(next));
dfa_tr[i][j]= dfa_cnt++;
}else
    dfa_tr[i][j]= pos;
}
}
printf("\n DFA Transition \n");
for(int i=0; i<dfa_cnt; i++){
print(dfa[i]);
for(int j=0; j<m; j++){
printf("--%d-->", j);
print(dfa[dfa_tr[i][j]]);
}
printf("\n");
    }
return 0;
} 
