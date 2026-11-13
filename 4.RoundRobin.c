#include <stdio.h>

struct process
{
    int pno;
    int at;
    int bt;
    int rem;
    int ct;
    int tat;
    int wt;
    int rt;
};

int main()
{
    int n, tq;
    int i, time = 0;
    int completed = 0;
    int queue[100];
    int front = 0, rear = 0;
    int added[20] = {0};
    int p;

    float avgtat = 0, avgwt = 0, avgrt = 0;

    struct process p1[20];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Arrival Time and Burst Time:\n");

    for (i = 0; i < n; i++)
    {
        p1[i].pno = i + 1;

        printf("P%d: ", i + 1);
        scanf("%d %d", &p1[i].at, &p1[i].bt);

        p1[i].rem = p1[i].bt;
        p1[i].rt = 0;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    /* Add processes which have arrived */
    for (i = 0; i < n; i++)
    {
        if (p1[i].at <= time && added[i] == 0)
        {
            queue[rear] = i;
            rear++;
            added[i] = 1;
        }
    }

    while (completed < n)
    {
        /* If queue is empty */
        if (front == rear)
        {
            time++;

            for (i = 0; i < n; i++)
            {
                if (p1[i].at <= time && added[i] == 0)
                {
                    queue[rear] = i;
                    rear++;
                    added[i] = 1;
                }
            }

            continue;
        }

        p = queue[front];
        front++;

        /* Calculate Response Time */
        if (p1[p].rem == p1[p].bt)
        {
            p1[p].rt = time - p1[p].at;
        }

        /* Execute for one time quantum */
        if (p1[p].rem > tq)
        {
            time = time + tq;
            p1[p].rem = p1[p].rem - tq;
        }
        else
        {
            time = time + p1[p].rem;
            p1[p].rem = 0;

            p1[p].ct = time;
            completed++;
        }

        /* Add newly arrived processes */
        for (i = 0; i < n; i++)
        {
            if (p1[i].at <= time && added[i] == 0)
            {
                queue[rear] = i;
                rear++;
                added[i] = 1;
            }
        }

        /* Put unfinished process at the end of queue */
        if (p1[p].rem > 0)
        {
            queue[rear] = p;
            rear++;
        }
    }

    /* Calculate TAT and WT */
    for (i = 0; i < n; i++)
    {
        p1[i].tat = p1[i].ct - p1[i].at;
        p1[i].wt = p1[i].tat - p1[i].bt;

        avgtat = avgtat + p1[i].tat;
        avgwt = avgwt + p1[i].wt;
        avgrt = avgrt + p1[i].rt;
    }

    printf("\nRound Robin Scheduling\n");

    printf("\nP.No\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p1[i].pno,
               p1[i].at,
               p1[i].bt,
               p1[i].ct,
               p1[i].tat,
               p1[i].wt,
               p1[i].rt);
    }

    printf("\nAverage Turnaround Time = %.2f", avgtat / n);
    printf("\nAverage Waiting Time = %.2f", avgwt / n);
    printf("\nAverage Response Time = %.2f\n", avgrt / n);

    return 0;
}