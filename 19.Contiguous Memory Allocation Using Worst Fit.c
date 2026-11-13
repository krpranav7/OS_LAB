#include <stdio.h>

int main()
{
    int block[5] = {100, 500, 200, 300, 600};
    int process[5] = {212, 417, 112, 426, 150};
    int used[5] = {0, 0, 0, 0, 0};
    int alloc[5], frag[5];
    int i, j, worst, total = 0;

    for (i = 0; i < 5; i++)
    {
        alloc[i] = -1;
        frag[i] = 0;
    }

    for (i = 0; i < 5; i++)
    {
        worst = -1;

        for (j = 0; j < 5; j++)
        {
            if (used[j] == 0 && block[j] >= process[i])
            {
                if (worst == -1 || block[j] > block[worst])
                    worst = j;
            }
        }

        if (worst != -1)
        {
            alloc[i] = worst;
            frag[i] = block[worst] - process[i];
            used[worst] = 1;
            total = total + frag[i];
        }
    }

    printf("Process\tSize\tBlock\tBlock Size\tFragment\n");

    for (i = 0; i < 5; i++)
    {
        if (alloc[i] != -1)
        {
            printf("P%d\t%d\tB%d\t%d\t\t%d\n",
                   i + 1, process[i], alloc[i] + 1,
                   block[alloc[i]], frag[i]);
        }
        else
        {
            printf("P%d\t%d\tNot Allocated\n",
                   i + 1, process[i]);
        }
    }

    printf("\nTotal internal fragmentation = %d KB\n", total);

    printf("Unused blocks: ");
    for (i = 0; i < 5; i++)
    {
        if (used[i] == 0)
            printf("B%d (%d KB) ", i + 1, block[i]);
    }

    printf("\n");
    return 0;
}
