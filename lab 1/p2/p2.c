#include <stdio.h>

int main()
{
    int choice,n,i;

    printf("CPU Scheduling\n");
    printf("1. Preemptive SJF (SRTF)\n");
    printf("2. Non-Preemptive SJF\n");
    printf("Enter your choice: ");
    scanf("%d",&choice);

    printf("Enter number of processes: ");
    scanf("%d",&n);

    int at[20],bt[20];

    printf("Enter Arrival Time:\n");
    for(i=0;i<n;i++)
    {
        printf("P%d: ",i+1);
        scanf("%d",&at[i]);
    }

    printf("Enter Burst Time:\n");
    for(i=0;i<n;i++)
    {
        printf("P%d: ",i+1);
        scanf("%d",&bt[i]);
    }

    if(choice==2) // Non Preemptive SJF
    {
        int time=0,count=0,min;
        int ct[20],wt[20],tat[20],rt[20],start[20];
        int completed[20]={0};
        float avgwt=0,avgtat=0,avgrt=0;

        while(count<n)
        {
            min=-1;

            for(i=0;i<n;i++)
            {
                if(at[i]<=time && completed[i]==0)
                {
                    if(min==-1 || bt[i]<bt[min])
                        min=i;
                }
            }

            if(min==-1)
            {
                time++;
            }
            else
            {
                start[min]=time;
                time+=bt[min];
                ct[min]=time;

                tat[min]=ct[min]-at[min];
                wt[min]=tat[min]-bt[min];
                rt[min]=start[min]-at[min];

                completed[min]=1;
                count++;
            }
        }

        printf("\nProcess AT BT CT WT TAT RT\n");

        for(i=0;i<n;i++)
        {
            printf("P%d\t%d %d %d %d %d %d\n",i+1,at[i],bt[i],ct[i],wt[i],tat[i],rt[i]);

            avgwt+=wt[i];
            avgtat+=tat[i];
            avgrt+=rt[i];
        }

        printf("\nAverage Waiting Time = %.2f",avgwt/n);
        printf("\nAverage Turnaround Time = %.2f",avgtat/n);
        printf("\nAverage Response Time = %.2f\n",avgrt/n);
    }

    else if(choice==1) // Preemptive SJF (SRTF)
    {
        int time=0,smallest,count=0;
        int rt[20],ct[20],wt[20],tat[20],res[20];
        int flag[20]={0};
        float avgwt=0,avgtat=0,avgrt=0;

        for(i=0;i<n;i++)
            rt[i]=bt[i];

        while(count<n)
        {
            smallest=-1;

            for(i=0;i<n;i++)
            {
                if(at[i]<=time && rt[i]>0)
                {
                    if(smallest==-1 || rt[i]<rt[smallest])
                        smallest=i;
                }
            }

            if(smallest==-1)
            {
                time++;
                continue;
            }

            if(flag[smallest]==0)
            {
                res[smallest]=time-at[smallest];
                flag[smallest]=1;
            }

            rt[smallest]--;
            time++;

            if(rt[smallest]==0)
            {
                count++;
                ct[smallest]=time;

                tat[smallest]=ct[smallest]-at[smallest];
                wt[smallest]=tat[smallest]-bt[smallest];
            }
        }

        printf("\nProcess AT BT CT WT TAT RT\n");

        for(i=0;i<n;i++)
        {
            printf("P%d\t%d %d %d %d %d %d\n",i+1,at[i],bt[i],ct[i],wt[i],tat[i],res[i]);

            avgwt+=wt[i];
            avgtat+=tat[i];
            avgrt+=res[i];
        }

        printf("\nAverage Waiting Time = %.2f",avgwt/n);
        printf("\nAverage Turnaround Time = %.2f",avgtat/n);
        printf("\nAverage Response Time = %.2f\n",avgrt/n);
    }

    else
    {
        printf("Invalid Choice!");
    }

    return 0;
}
