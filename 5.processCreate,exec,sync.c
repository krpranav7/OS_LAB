#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t n;

    n = fork();

    if (n < 0)
    {
        printf("fork failed\n");
        exit(1);
    }

    printf("Process ID: %d and value of n = %d\n", getpid(), n);

    if (n == 0)
    {
        // Child process
        execlp("ls", "ls", NULL);

        // This executes only if execlp fails
        printf("execlp failed\n");
        exit(1);
    }
    else
    {
        // Parent process
        wait(NULL);

        printf("Child completed\n");
    }

    return 0;
}