#include <stdio.h>

struct process
{
    int pno;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int completed;
};

int main()
{
    int n, i;
    int time = 0, count = 0;
    int min, pos;
    float avgtat = 0, avgwt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Arrival Time and Burst Time:\n");

    struct process p[20];

    for (i = 0; i < n; i++)
    {
        p[i].pno = i + 1;

        printf("P%d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);

        p[i].completed = 0;
    }

    while (count < n)
    {
        min = 9999;
        pos = -1;

        /* Find shortest burst time among arrived processes */
        for (i = 0; i < n; i++)
        {
            if (p[i].completed == 0 && p[i].at <= time)
            {
                if (p[i].bt < min)
                {
                    min = p[i].bt;
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
            p[pos].ct = time + p[pos].bt;
            p[pos].tat = p[pos].ct - p[pos].at;
            p[pos].wt = p[pos].tat - p[pos].bt;

            time = p[pos].ct;

            p[pos].completed = 1;
            count++;

            avgtat = avgtat + p[pos].tat;
            avgwt = avgwt + p[pos].wt;
        }
    }

    printf("\nP.No\tAT\tBT\tCT\tTAT\tWT\n");

    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pno, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Turnaround Time = %.2f", avgtat / n);
    printf("\nAverage Waiting Time = %.2f\n", avgwt / n);

    return 0;
}