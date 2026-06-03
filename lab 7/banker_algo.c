#include <stdio.h>

int main() {

    int n, m;
    int i, j, k;

    printf("Enter number of processes and resources:\n");
    scanf("%d%d", &n, &m);

    int alloc[n][m], max[n][m], need[n][m];
    int avail[m];

    printf("Enter Allocation Matrix:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Max Matrix:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Available Resources:\n");
    for(i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    // Calculate Need Matrix
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    // ---------------- RESOURCE REQUEST ----------------

    int p;
    int request[m];

    printf("Enter process number requesting resources:\n");
    scanf("%d", &p);

    printf("Enter request vector:\n");
    for(i = 0; i < m; i++)
        scanf("%d", &request[i]);

    // Check Request <= Need
    for(i = 0; i < m; i++) {
        if(request[i] > need[p][i]) {
            printf("Error: Process exceeded maximum claim\n");
            return 0;
        }
    }

    // Check Request <= Available
    for(i = 0; i < m; i++) {
        if(request[i] > avail[i]) {
            printf("Resources not available. Process must wait.\n");
            return 0;
        }
    }

    // Pretend allocation
    for(i = 0; i < m; i++) {
        avail[i] -= request[i];
        alloc[p][i] += request[i];
        need[p][i] -= request[i];
    }

    // ---------------- SAFETY ALGORITHM ----------------

    int finish[n], safe[n];
    int work[m];

    for(i = 0; i < m; i++)
        work[i] = avail[i];

    for(i = 0; i < n; i++)
        finish[i] = 0;

    int count = 0;

    while(count < n) {

        int found = 0;

        for(i = 0; i < n; i++) {

            if(finish[i] == 0) {

                for(j = 0; j < m; j++) {
                    if(need[i][j] > work[j])
                        break;
                }

                // Process can execute
                if(j == m) {

                    for(k = 0; k < m; k++)
                        work[k] += alloc[i][k];

                    safe[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if(found == 0)
            break;
    }

    // ---------------- RESULT ----------------

    if(count == n) {

        printf("Request can be granted.\n");
        printf("System is in SAFE state.\n");

        printf("Safe Sequence: ");
        for(i = 0; i < n; i++)
            printf("P%d ", safe[i]);

        printf("\n");
    }
    else {

        // Rollback
        for(i = 0; i < m; i++) {
            avail[i] += request[i];
            alloc[p][i] -= request[i];
            need[p][i] += request[i];
        }

        printf("Request cannot be granted.\n");
        printf("System would become UNSAFE.\n");
    }

    return 0;
}
