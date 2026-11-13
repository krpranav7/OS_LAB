#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t A, B, M;
int X = 0;

void *P1(void *arg)
{
    int i;

    for(i = 0; i < 8; i++)
    {
        sem_wait(&B);

        sem_wait(&M);

        printf("$");
        X++;

        if(X == 2)
        {
            X = 0;
            sem_post(&A);
            sem_post(&A);
            sem_post(&A);
        }

        sem_post(&M);
    }

    return NULL;
}

void *P2(void *arg)
{
    int i;

    for(i = 0; i < 12; i++)
    {
        sem_wait(&A);

        sem_wait(&M);

        printf("#");
        X++;

        if(X == 3)
        {
            X = 0;
            sem_post(&B);
            sem_post(&B);
        }

        sem_post(&M);
    }

    return NULL;
}

int main()
{
    pthread_t t1, t2;

    X = 0;

    sem_init(&A, 0, 0);
    sem_init(&B, 0, 2);
    sem_init(&M, 0, 1);

    pthread_create(&t1, NULL, P1, NULL);
    pthread_create(&t2, NULL, P2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    sem_destroy(&A);
    sem_destroy(&B);
    sem_destroy(&M);

    return 0;
}