#include <stdio.h>

struct process
{
    int pno;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
};

int main()
{
    int n, i, j;
    struct process p[20], temp;
    float avgtat = 0, avgwt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Arrival Time and Burst Time:\n");

    for (i = 0; i < n; i++)
    {
        p[i].pno = i + 1;
        printf("P%d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
    }

    /* Arrange processes according to Arrival Time */
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (p[i].at > p[j].at)
            {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    p[0].ct = p[0].at + p[0].bt;

    for (i = 1; i < n; i++)
    {
        if (p[i].at > p[i - 1].ct)
            p[i].ct = p[i].at + p[i].bt;
        else
            p[i].ct = p[i - 1].ct + p[i].bt;
    }

    for (i = 0; i < n; i++)
    {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        avgtat = avgtat + p[i].tat;
        avgwt = avgwt + p[i].wt;
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