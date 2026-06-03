#include <stdio.h>
#include <math.h>

int main() {
    int n, i, j, temp, time;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int b[n], d[n], p[n], id[n];

    for (i = 0; i < n; i++) {
        id[i] = i;
        printf("\nProcess %d:\n", i);
        printf("Burst Time: "); scanf("%d", &b[i]);
        printf("Deadline: "); scanf("%d", &d[i]);
        printf("Period: "); scanf("%d", &p[i]);
    }

    float util = 0;
    for (i = 0; i < n; i++) util += (float)b[i] / p[i];

    // EDF (sort by deadline)
    for (i = 0; i < n-1; i++)
        for (j = i+1; j < n; j++)
            if (d[i] > d[j]) {
                temp=d[i]; d[i]=d[j]; d[j]=temp;
                temp=b[i]; b[i]=b[j]; b[j]=temp;
                temp=id[i]; id[i]=id[j]; id[j]=temp;
            }

    printf("\nEDF Scheduling\nCPU Utilization: %.2f\n", util);
    printf("ID  CT  WT  TAT\n");

    time = 0;
    for (i = 0; i < n; i++) {
        time += b[i];
        printf("%d   %d   %d   %d\n", id[i], time, time-b[i], time);
    }

    // RMS (sort by period)
    for (i = 0; i < n-1; i++)
        for (j = i+1; j < n; j++)
            if (p[i] > p[j]) {
                temp=p[i]; p[i]=p[j]; p[j]=temp;
                temp=b[i]; b[i]=b[j]; b[j]=temp;
                temp=id[i]; id[i]=id[j]; id[j]=temp;
            }

    float bound = n * (pow(2, 1.0/n) - 1);

    printf("\nRMS Scheduling\nCPU Utilization: %.2f\nRM Bound: %.4f\n", util, bound);
    printf("ID  CT  WT  TAT\n");

    time = 0;
    for (i = 0; i < n; i++) {
        time += b[i];
        printf("%d   %d   %d   %d\n", id[i], time, time-b[i], time);
    }

    // ---------------- Proportional ----------------
    printf("\n====== Proportional Scheduling ======\n");
    printf("ID  Burst  Share\n");
    int total=0;
    for (int i = 0; i < n; i++)
        total += b[i];
    for (int i = 0; i < n; i++) {
        float share = (float)b[i] / total;
        printf("%d   %d     %.2f\n", id[i], b[i], share);
    }
    return 0;
}

