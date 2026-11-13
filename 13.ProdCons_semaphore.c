#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

#define N 5

int buffer[N];

int in = 0;
int out = 0;

sem_t empty;
sem_t full;
sem_t mutex;

void *producer(void *arg)
{
    int item;
    int i;

    for (i = 1; i <= 10; i++)
    {
        item = rand() % 100;

        sem_wait(&empty);
        sem_wait(&mutex);

        buffer[in] = item;

        printf("%d producer produce %d at %d\n",
               i, item, in);

        in = (in + 1) % N;

        sem_post(&mutex);
        sem_post(&full);

        usleep(100000);
    }

    return NULL;
}

void *consumer(void *arg)
{
    int item;
    int i;

    for (i = 1; i <= 10; i++)
    {
        sem_wait(&full);
        sem_wait(&mutex);

        item = buffer[out];

        printf("%d consumer consume %d from %d\n",
               i, item, out);

        out = (out + 1) % N;

        sem_post(&mutex);
        sem_post(&empty);

        usleep(150000);
    }

    return NULL;
}

int main()
{
    pthread_t producer_thread;
    pthread_t consumer_thread;

    sem_init(&empty, 0, N);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_create(&producer_thread, NULL,
                   producer, NULL);

    pthread_create(&consumer_thread, NULL,
                   consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}