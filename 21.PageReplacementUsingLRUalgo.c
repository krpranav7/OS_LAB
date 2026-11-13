#include <stdio.h>

int main()
{
    int n, f, i, j;
    int ref[100], frame[20], last_used[20];
    int hit = 0, fault = 0;
    int found, pos, least;

    printf("Enter number of page references: ");
    scanf("%d", &n);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    printf("Enter reference string:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &ref[i]);

    for (i = 0; i < f; i++)
    {
        frame[i] = -1;
        last_used[i] = 0;
    }

    printf("\nRef No.\tPage");

    for (i = 0; i < f; i++)
        printf("\tF%d", i + 1);

    printf("\tStatus\n");

    for (i = 0; i < n; i++)
    {
        found = 0;

        for (j = 0; j < f; j++)
        {
            if (frame[j] == ref[i])
            {
                found = 1;
                last_used[j] = i + 1;
                break;
            }
        }

        if (found == 1)
        {
            hit++;
        }
        else
        {
            fault++;
            pos = -1;

            // Check for empty frame
            for (j = 0; j < f; j++)
            {
                if (frame[j] == -1)
                {
                    pos = j;
                    break;
                }
            }

            // Apply LRU algorithm
            if (pos == -1)
            {
                least = last_used[0];
                pos = 0;

                for (j = 1; j < f; j++)
                {
                    if (last_used[j] < least)
                    {
                        least = last_used[j];
                        pos = j;
                    }
                }
            }

            frame[pos] = ref[i];
            last_used[pos] = i + 1;
        }

        printf("%-8d%-8d", i + 1, ref[i]);

        for (j = 0; j < f; j++)
        {
            if (frame[j] == -1)
                printf("%-8s", "-");
            else
                printf("%-8d", frame[j]);
        }

        if (found == 1)
            printf("Hit\n");
        else
            printf("Fault\n");
    }

    printf("\nTotal page faults = %d\n", fault);
    printf("Total page hits   = %d\n", hit);
    printf("Hit ratio = %.2f%%   Fault ratio = %.2f%%\n",
           (hit * 100.0) / n, (fault * 100.0) / n);

    return 0;
}
