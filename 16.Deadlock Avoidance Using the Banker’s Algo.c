
#include <stdio.h>

int n = 5, m = 3;

int available[3] = {3, 3, 2};

int allocation[5][3] = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};

int max[5][3] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};

int need[5][3];

int is_safe(int show)
{
    int work[3], finish[5] = {0};
    int safe[5], count = 0, i, j, found;

    for (j = 0; j < m; j++)
        work[j] = available[j];

    while (count < n)
    {
        found = 0;

        for (i = 0; i < n; i++)
        {
            if (finish[i] == 0)
            {
                for (j = 0; j < m; j++)
                {
                    if (need[i][j] > work[j])
                        break;
                }

                if (j == m)
                {
                    for (j = 0; j < m; j++)
                        work[j] += allocation[i][j];

                    finish[i] = 1;
                    safe[count++] = i;
                    found = 1;
                }
            }
        }

        if (found == 0)
            break;
    }

    if (count == n)
    {
        if (show)
        {
            printf("System is in a SAFE state.\n");
            printf("Safe Sequence: ");

            for (i = 0; i < n; i++)
                printf("P%d%s", safe[i], i == n - 1 ? "\n" : " -> ");
        }

        return 1;
    }

    if (show)
        printf("System is in an UNSAFE state.\n");

    return 0;
}

void request(int p, int req[])
{
    int i;

    printf("\nRequest by P%d: (%d, %d, %d)\n", p, req[0], req[1], req[2]);

    for (i = 0; i < m; i++)
    {
        if (req[i] > need[p][i])
        {
            printf("Error: Maximum claim exceeded.\n");
            return;
        }
    }

    for (i = 0; i < m; i++)
    {
        if (req[i] > available[i])
        {
            printf("Resources not available. P%d must WAIT.\n", p);
            return;
        }
    }

    /* Temporarily allocate resources */
    for (i = 0; i < m; i++)
    {
        available[i] -= req[i];
        allocation[p][i] += req[i];
        need[p][i] -= req[i];
    }

    if (is_safe(0))
    {
        printf("Request GRANTED. ");
        is_safe(1);
    }
    else
    {
        /* Roll back the allocation */
        for (i = 0; i < m; i++)
        {
            available[i] += req[i];
            allocation[p][i] -= req[i];
            need[p][i] += req[i];
        }

        printf("Request would lead to an UNSAFE state.\n");
        printf("Request DENIED (rolled back).\n");
    }
}

int main()
{
    int i, j;

    int r1[3] = {1, 0, 2};
    int r2[3] = {3, 3, 0};
    int r3[3] = {0, 2, 0};

    /* Calculate Need matrix */
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - allocation[i][j];
    }

    printf("Need Matrix:\n");
    printf("     A B C\n");

    for (i = 0; i < n; i++)
    {
        printf("P%d   ", i);

        for (j = 0; j < m; j++)
            printf("%d ", need[i][j]);

        printf("\n");
    }

    printf("\nInitial State:\n");
    is_safe(1);

    request(1, r1);
    request(4, r2);
    request(0, r3);

    return 0;
}
