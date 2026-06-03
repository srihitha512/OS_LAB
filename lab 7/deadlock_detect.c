#include <stdio.h>

int main() {
    int n,m,i,j,k;
    printf("enter number of processes and resources:");
    scanf("%d%d",&n,&m);

    int alloc[n][m], req[n][m];
    int avail[m], finish[n];
    printf("Enter allocation matrix:\n");
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            scanf("%d",&alloc[i][j]);
    printf("Enter request matrix:\n");
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            scanf("%d",&req[i][j]);
    printf("Enter Available Resources:\n");
    for(i=0;i<m;i++)
        scanf("%d",&avail[i]);

    for(i=0;i<n;i++)
        finish[i]=0;

    for(i=0;i<n;i++) {
        if(!finish[i]) {

            for(j=0;j<m;j++)
                if(req[i][j]>avail[j])
                    break;

            if(j==m) {
                for(k=0;k<m;k++)
                    avail[k]+=alloc[i][k];

                finish[i]=1;
            }
        }
    }

    for(i=0;i<n;i++) {
        if(!finish[i])
            printf("Deadlock at P%d\n",i);
    }

    return 0;
}

