#include <stdio.h>
#include <pthread.h>

void *even(void *arg)
{
    int i;

    for(i = 2; i <= 20; i = i + 2)
    {
        printf("Thread 1 (Even): %d\n", i);
    }

    return NULL; // pthread_exit(0); this terminates the calling thread
}

void *odd(void *arg)
{
    int i;

    for(i = 1; i <= 20; i = i + 2)
    {
        printf("Thread 2 (Odd): %d\n", i);
    }

    return NULL;
}

int main()
{
    pthread_t t1, t2;

    pthread_create(&t1, NULL, even, NULL);
    pthread_create(&t2, NULL, odd, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Main: both threads have finished execution\n");

    return 0;
}