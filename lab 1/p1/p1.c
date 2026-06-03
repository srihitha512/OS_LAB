#include <stdio.h>

int main()
{
    int n,i;
    int at[20],bt[20],ct[20],wt[20],tat[20],rt[20],start[20];
    float avgwt=0,avgtat=0,avgrt=0;

    printf("Enter number of processes: ");
    scanf("%d",&n);

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

    start[0]=at[0];
    ct[0]=start[0]+bt[0];

    for(i=1;i<n;i++)
    {
        if(ct[i-1] > at[i])
            start[i]=ct[i-1];
        else
            start[i]=at[i];

        ct[i]=start[i]+bt[i];
    }

    for(i=0;i<n;i++)
    {
        tat[i]=ct[i]-at[i];
        wt[i]=tat[i]-bt[i];
        rt[i]=start[i]-at[i];

        avgwt+=wt[i];
        avgtat+=tat[i];
        avgrt+=rt[i];
    }

    printf("\nProcess AT BT CT WT TAT RT\n");

    for(i=0;i<n;i++)
        printf("P%d\t%d %d %d %d %d %d\n",i+1,at[i],bt[i],ct[i],wt[i],tat[i],rt[i]);

    printf("\nAverage Waiting Time = %.2f",avgwt/n);
    printf("\nAverage Turnaround Time = %.2f",avgtat/n);
    printf("\nAverage Response Time = %.2f\n",avgrt/n);

    return 0;
}
