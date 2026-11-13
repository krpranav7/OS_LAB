#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *factorial(void *arg)
{
    int n = *(int *)arg;
    int i;
    int *res;

    res = malloc(sizeof(int));

    *res = 1;

    for (i = 1; i <= n; i++)
    {
        *res = *res * i;
    }

    pthread_exit(res); // return result
}

int main()
{
    pthread_t t[5];
    int n[5];
    int *result;
    int i;

    for (i = 0; i < 5; i++)
    {
        n[i] = i + 1;

        pthread_create(&t[i], NULL, factorial, &n[i]);
    }

    for (i = 0; i < 5; i++)
    {
        pthread_join(t[i], (void **)&result);

        printf("Thread for n=%d computed factorial = %d\n", n[i], *result);

        free(result);
    }

    printf("All threads have returned their results\n");

    return 0;
}