#include <stdio.h>

#define MAX 50

typedef struct {
    int pid;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
} Process;

void calculateFCFS(Process queue[], int n) {
    int i;
    queue[0].waitingTime = 0;

    for (i = 1; i < n; i++) {
        queue[i].waitingTime = queue[i - 1].waitingTime + queue[i - 1].burstTime;
    }

    for (i = 0; i < n; i++) {
        queue[i].turnaroundTime = queue[i].waitingTime + queue[i].burstTime;
    }
}

void display(Process queue[], int n, char queueName[]) {
    int i;
    float totalWT = 0, totalTAT = 0;

    printf("\n--- %s ---\n", queueName);
    printf("PID\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n",
               queue[i].pid,
               queue[i].burstTime,
               queue[i].waitingTime,
               queue[i].turnaroundTime);

        totalWT += queue[i].waitingTime;
        totalTAT += queue[i].turnaroundTime;
    }

    printf("Average Waiting Time = %.2f\n", totalWT / n);
    printf("Average Turnaround Time = %.2f\n", totalTAT / n);
}

void printGanttChart(Process systemQueue[], int nSys, Process userQueue[], int nUser) {
    int i;
    int time = 0;

    printf("\nGantt Chart:\n|");

    // Print system queue in Gantt
    for (i = 0; i < nSys; i++) {
        printf(" P%d |", systemQueue[i].pid);
    }
    // Print user queue in Gantt
    for (i = 0; i < nUser; i++) {
        printf(" P%d |", userQueue[i].pid);
    }
    printf("\n");

    // Print time line
    printf("0");
    // System queue completion times
    for (i = 0; i < nSys; i++) {
        time += systemQueue[i].burstTime;
        printf("\t%d", time);
    }
    // User queue completion times (starting after system queue)
    for (i = 0; i < nUser; i++) {
        time += userQueue[i].burstTime;
        printf("\t%d", time);
    }
    printf("\n");
}

int main() {
    Process systemQueue[MAX], userQueue[MAX];
    int nSys, nUser, i;

    printf("Enter number of system processes: ");
    scanf("%d", &nSys);

    for (i = 0; i < nSys; i++) {
        systemQueue[i].pid = i + 1;
        printf("Enter burst time for System Process %d: ", i + 1);
        scanf("%d", &systemQueue[i].burstTime);
    }

    printf("\nEnter number of user processes: ");
    scanf("%d", &nUser);

    for (i = 0; i < nUser; i++) {
        userQueue[i].pid = i + 1;
        printf("Enter burst time for User Process %d: ", i + 1);
        scanf("%d", &userQueue[i].burstTime);
    }

    calculateFCFS(systemQueue, nSys);
    calculateFCFS(userQueue, nUser);

    display(systemQueue, nSys, "System Queue (Higher Priority)");
    display(userQueue, nUser, "User Queue (Lower Priority)");

    printf("\nExecution Order:\nSystem Processes -> ");
    for (i = 0; i < nSys; i++) {
        printf("P%d ", systemQueue[i].pid);
    }
    printf("\nUser Processes -> ");
    for (i = 0; i < nUser; i++) {
        printf("P%d ", userQueue[i].pid);
    }
    printf("\n");

    printGanttChart(systemQueue, nSys, userQueue, nUser);

    return 0;
}
