#include <stdio.h>
#include <pthread.h>

void *show(void *arg)
{
    int n = *(int *)arg;

    printf("Thread %d: my ID is %lu\n", n, (unsigned long)pthread_self());

    return NULL;
}

int main()
{
    pthread_t t[6];
    int n[6];
    int i;

    for(i = 0; i < 6; i++)
    {
        n[i] = i;

        pthread_create(&t[i], NULL, show, &n[i]);
    }

    for(i = 0; i < 6; i++)
    {
        pthread_join(t[i], NULL);
    }

    if(pthread_equal(t[0], t[1]))
        printf("pthread_equal(thread[0], thread[1]) = 1 (same thread)\n");
    else
        printf("pthread_equal(thread[0], thread[1]) = 0 (different threads)\n");

    printf("All 6 threads have completed\n");

    return 0;
}