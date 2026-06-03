#include <stdio.h>
#include <math.h>

#define MAX 10

struct Process {
    int id;
    int bt;
    int period;
    int deadline;
    int rt;
    int ct, tat, wt;
    int weight;
};

// ---------- CPU UTILIZATION ----------
float calculateUtilization(struct Process p[], int n) {
    float util = 0;
    for (int i = 0; i < n; i++) {
        util += (float)p[i].bt / p[i].period;
    }
    return util;
}

// ---------- EDF (PREEMPTIVE) ----------
void EDF(struct Process p[], int n) {
    printf("\n===== Earliest Deadline First (EDF) Scheduling =====\n");

    float util = calculateUtilization(p, n);
    printf("CPU Utilization: %.2f\n", util);

    if (util <= 1)
        printf("Schedulable (Utilization <= 1)\n");
    else
        printf("Not Schedulable\n");

    int time = 0;

    while (1) {
        int idx = -1, min_deadline = 9999;
        int all_done = 1;

        for (int i = 0; i < n; i++) {
            if (p[i].rt > 0) {
                all_done = 0;

                if (p[i].deadline < min_deadline) {
                    min_deadline = p[i].deadline;
                    idx = i;
                }
            }
        }

        if (all_done) break;

        // execute for 1 unit
        p[idx].rt--;
        time++;

        if (p[idx].rt == 0) {
            p[idx].ct = time;
            p[idx].tat = p[idx].ct;
            p[idx].wt = p[idx].tat - p[idx].bt;
        }
    }

    printf("\nID\tBT\tDL\tCT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].bt, p[i].deadline,
               p[i].ct, p[i].wt, p[i].tat);
    }
}

// ---------- RMS ----------
void RMS(struct Process p[], int n) {
    printf("\n===== Rate Monotonic Scheduling (RMS) =====\n");

    float util = calculateUtilization(p, n);
    printf("CPU Utilization: %.2f\n", util);

    float bound = n * (pow(2, 1.0/n) - 1);
    printf("RM Bound: %.3f\n", bound);

    if (util <= bound)
        printf("Schedulable (Utilization <= RM Bound)\n");
    else
        printf("May not be schedulable\n");

    int time = 0;

    while (1) {
        int idx = -1, min_period = 9999;
        int all_done = 1;

        for (int i = 0; i < n; i++) {
            if (p[i].rt > 0) {
                all_done = 0;

                if (p[i].period < min_period) {
                    min_period = p[i].period;
                    idx = i;
                }
            }
        }

        if (all_done) break;

        p[idx].rt--;
        time++;

        if (p[idx].rt == 0) {
            p[idx].ct = time;
            p[idx].tat = p[idx].ct;
            p[idx].wt = p[idx].tat - p[idx].bt;
        }
    }

    printf("\nID\tBT\tP\tCT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].bt, p[i].period,
               p[i].ct, p[i].wt, p[i].tat);
    }
}

// ---------- PROPORTIONAL ----------
void proportional(struct Process p[], int n) {
    printf("\n===== Proportional Scheduling =====\n");

    int total_weight = 0;
    for (int i = 0; i < n; i++)
        total_weight += p[i].weight;

    printf("Total Weight = %d\n", total_weight);
    printf("CPU Share:\n");

    printf("\nID\tWeight\tCPU Share\n");
    for (int i = 0; i < n; i++) {
        float share = (float)p[i].weight / total_weight;
        printf("%d\t%d\t%.2f\n", p[i].id, p[i].weight, share);
    }
}

// ---------- MAIN ----------
int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[MAX];

    for (int i = 0; i < n; i++) {
        printf("\nProcess %d:\n", i);
        p[i].id = i;

        printf("Burst Time: ");
        scanf("%d", &p[i].bt);

        printf("Deadline (for EDF): ");
        scanf("%d", &p[i].deadline);

        printf("Period (for RMS): ");
        scanf("%d", &p[i].period);

        printf("Weight (for Proportional): ");
        scanf("%d", &p[i].weight);

        p[i].rt = p[i].bt;
    }

    struct Process edf[MAX], rms[MAX], prop[MAX];

    for (int i = 0; i < n; i++) {
        edf[i] = rms[i] = prop[i] = p[i];
    }

    EDF(edf, n);
    RMS(rms, n);
    proportional(prop, n);

    return 0;
}