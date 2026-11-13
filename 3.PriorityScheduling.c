#include <stdio.h>

struct process
{
    int pno;
    int at;
    int bt;
    int priority;
    int rem;
    int ct;
    int tat;
    int wt;
    int rt;
};

int main()
{
    int n, i;
    int time = 0, completed = 0;
    int pos, max;

    float avgtat = 0, avgwt = 0, avgrt = 0;

    struct process p[20];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Arrival Time, Burst Time and Priority:\n");

    for (i = 0; i < n; i++)
    {
        p[i].pno = i + 1;

        printf("P%d: ", i + 1);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].priority);

        p[i].rem = p[i].bt;
        p[i].rt = -1;
    }

    while (completed < n)
    {
        max = -9999;
        pos = -1;

        /* Find highest priority among arrived processes */
        for (i = 0; i < n; i++)
        {
            if (p[i].rem > 0 && p[i].at <= time)
            {
                if (p[i].priority > max)
                {
                    max = p[i].priority;
                    pos = i;
                }
            }
        }

        /* If no process has arrived yet */
        if (pos == -1)
        {
            time++;
        }
        else
        {
            /* Calculate Response Time */
            if (p[pos].rt == -1)
            {
                p[pos].rt = time - p[pos].at;
            }

            /* Execute process for one time unit */
            p[pos].rem--;
            time++;

            /* Check if process is completed */
            if (p[pos].rem == 0)
            {
                p[pos].ct = time;
                completed++;
            }
        }
    }

    /* Calculate TAT and WT */
    for (i = 0; i < n; i++)
    {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        avgtat = avgtat + p[i].tat;
        avgwt = avgwt + p[i].wt;
        avgrt = avgrt + p[i].rt;
    }

    printf("\nPreemptive Priority Scheduling\n");

    printf("\nP.No\tAT\tBT\tPriority\tCT\tTAT\tWT\tRT\n");

    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t%d\t%d\n",
               p[i].pno,
               p[i].at,
               p[i].bt,
               p[i].priority,
               p[i].ct,
               p[i].tat,
               p[i].wt,
               p[i].rt);
    }

    printf("\nAverage Turnaround Time = %.2f", avgtat / n);
    printf("\nAverage Waiting Time = %.2f", avgwt / n);
    printf("\nAverage Response Time = %.2f\n", avgrt / n);

    return 0;
}
