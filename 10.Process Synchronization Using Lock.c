#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int shared_resource = 0;
volatile int lock = 0;
int inside = 0;

void entry_section(int id)
{
    int waiting = 0;

    while (lock != 0)
    {
        if (waiting == 0)
        {
            printf("Thread %d is waiting...\n", id);
            waiting = 1;
        }
    }

    lock = 1;
}

void exit_section()
{
    lock = 0;
}

void *criticalSection(void *arg)
{
    int id = (int)(long)arg;

    printf("Thread %d wants to enter CS\n", id);

    entry_section(id);

    printf("Thread %d entered CS, shared data = %d\n",
           id, shared_resource);

    inside++;

    if (inside > 1)
        printf(">>> Mutual Exclusion NOT achieved <<<\n");

    usleep(1000000);

    shared_resource++;

    inside--;

    printf("Thread %d exits CS, shared data = %d\n",
           id, shared_resource);

    exit_section();

    return NULL;
}

int main()
{
    pthread_t thread[5];

    for (int i = 0; i < 5; i++)
    {
        pthread_create(&thread[i], NULL, criticalSection, (void *)(long)i);
    }

    for (int i = 0; i < 5; i++)
    {
        pthread_join(thread[i], NULL);
    }

    printf("\nFinal shared data = %d\n", shared_resource);

    return 0;
}