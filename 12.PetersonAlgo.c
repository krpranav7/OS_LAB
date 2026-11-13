#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int shareData = 0;

int interested[2] = {0, 0};
int turn = 0;

int count = 0;

void entry(int process)
{
    int other = 1 - process;

    interested[process] = 1;
    turn = process;

    while(interested[other] == 1 && turn == process)
    {
        // busy waiting
    }
}

void exit_section(int process)
{
    interested[process] = 0;
}

void *critical_section(void *arg)
{
    int id = *(int *)arg;

    while(count <= 10)
    {
        entry(id);

        printf("Thread %d enter CS, share Data = %d\n",
               id, shareData);

        usleep(100000);

        shareData++;

        printf("Thread %d exit CS, share Data = %d\n",
               id, shareData);

        count++;

        exit_section(id);

        usleep(100000);
    }

    return NULL;
}

int main()
{
    pthread_t thread[2];
    int id[2] = {0, 1};

    pthread_create(&thread[0], NULL,
                   critical_section, &id[0]);

    pthread_create(&thread[1], NULL,
                   critical_section, &id[1]);

    pthread_join(thread[0], NULL);
    pthread_join(thread[1], NULL);

    printf("\nFinal shareData = %d\n", shareData);

    return 0;
}