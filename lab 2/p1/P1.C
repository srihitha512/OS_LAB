#include <stdio.h>

int main()
{
    int choice, n, i, j, pos, temp;
    int bt[10], wt[10], tat[10], p[10], pr[10], at[10], rt[10];
    int time, completed, highest;
    float avg_wt = 0, avg_tat = 0;

    printf("CPU Scheduling - Priority\n");
    printf("1. Non-Preemptive Priority\n");
    printf("2. Preemptive Priority\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    printf("Enter number of processes: ");
    scanf("%d", &n);

    switch (choice)
    {

    // NON PREEMPTIVE PRIORITY
    case 1:

        for (i = 0; i < n; i++)
        {
            printf("Enter Burst Time and Priority for P%d: ", i + 1);
            scanf("%d%d", &bt[i], &pr[i]);
            p[i] = i + 1;
        }

        // Sorting according to priority
        for (i = 0; i < n; i++)
        {
            pos = i;
            for (j = i + 1; j < n; j++)
            {
                if (pr[j] < pr[pos])
                    pos = j;
            }

            temp = pr[i];
            pr[i] = pr[pos];
            pr[pos] = temp;

            temp = bt[i];
            bt[i] = bt[pos];
            bt[pos] = temp;

            temp = p[i];
            p[i] = p[pos];
            p[pos] = temp;
        }

        wt[0] = 0;

        for (i = 1; i < n; i++)
            wt[i] = wt[i - 1] + bt[i - 1];

        printf("\nProcess\tBT\tPriority\tWT\tTAT\n");

        for (i = 0; i < n; i++)
        {
            tat[i] = bt[i] + wt[i];
            avg_wt += wt[i];
            avg_tat += tat[i];

            printf("P%d\t%d\t%d\t\t%d\t%d\n", p[i], bt[i], pr[i], wt[i], tat[i]);
        }

        printf("\nAverage Waiting Time = %.2f", avg_wt / n);
        printf("\nAverage Turnaround Time = %.2f\n", avg_tat / n);

        break;

    // PREEMPTIVE PRIORITY
    case 2:

        for (i = 0; i < n; i++)
        {
            printf("Enter Arrival Time, Burst Time and Priority for P%d: ", i + 1);
            scanf("%d%d%d", &at[i], &bt[i], &pr[i]);
            rt[i] = bt[i];
        }

        time = 0;
        completed = 0;

        while (completed < n)
        {
            highest = -1;

            for (i = 0; i < n; i++)
            {
                if (at[i] <= time && rt[i] > 0)
                {
                    if (highest == -1 || pr[i] < pr[highest])
                        highest = i;
                }
            }

            if (highest == -1)
            {
                time++;
                continue;
            }

            rt[highest]--;
            time++;

            if (rt[highest] == 0)
            {
                completed++;
                tat[highest] = time - at[highest];
                wt[highest] = tat[highest] - bt[highest];

                avg_wt += wt[highest];
                avg_tat += tat[highest];
            }
        }

        printf("\nProcess\tWT\tTAT\n");

        for (i = 0; i < n; i++)
            printf("P%d\t%d\t%d\n", i + 1, wt[i], tat[i]);

        printf("\nAverage Waiting Time = %.2f", avg_wt / n);
        printf("\nAverage Turnaround Time = %.2f\n", avg_tat / n);

        break;

    default:
        printf("Invalid Choice");
    }

    return 0;
}
