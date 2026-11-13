#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t S0, S1;

void *thread0(void *arg)
{
    int i;

    for(i = 0; i < 5; i++)
    {
        sem_wait(&S0);
        printf("0");
        sem_post(&S1);
    }

    return NULL;
}

void *thread1(void *arg)
{
    int i;

    for(i = 0; i < 5; i++)
    {
        sem_wait(&S1);
        printf("1");
        sem_post(&S0);
    }

    return NULL;
}

int main()
{
    pthread_t t0, t1;

    sem_init(&S0, 0, 1);
    sem_init(&S1, 0, 0);

    pthread_create(&t0, NULL, thread0, NULL);
    pthread_create(&t1, NULL, thread1, NULL);

    pthread_join(t0, NULL);
    pthread_join(t1, NULL);

    sem_destroy(&S0);
    sem_destroy(&S1);

    return 0;
}