/*
    *Filename:pctl.c
    *copyright:(C)2006 by zhanghonglie
    *Function:父子进程的并发执行
*/

#include "pctl.h"

int main(int argc, char *argv[])
{
    int i;
    int pid;
    int status;
    char* args[] = { "/bin/ls","-a",NULL };
    signal(SIGINT, ((__sighandler_t)sigcat));
    perror("SIGINT");
    pid = fork();
    if (pid < 0)
    {
        printf("Create Process fail!\n");
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
    {
        printf("I am Child process %d\n My father is %d\n", getpid(), getppid());
        pause();
        printf("%d child will Running:\n", getpid());
        if (argv[1] != NULL)
        {
            for (i = 0;argv[i] != NULL;i++)
            {
                printf("%s ", argv[i]);
                printf("\n");
            }
            status = execve(argv[1],&argv[1],NULL);
        }
        else
        {
            for (i = 0;args[i] != NULL;i++)
            {
                printf("%s ", args[i]);
                printf("\n");
            }
            status = execve(args[0], args, NULL);
        }
    }
    else
    {
        printf("\nI am Parent process %d\n", getpid());
        if (argv[1] != NULL)
        {
            printf("%d Waiting for child done.\n\n", getpid());
            waitpid(pid, &status, 0);
            printf("\nMy child exit! status=%d\n\n", status);
        }
        else
        {
            sleep(5);
            if (kill(pid, SIGINT) >= 0)
            {
                printf("%d Wakeup %d child.\n", getpid(), pid);
            }
            printf("%d don`t Wait for child done.\n\n", getpid());
        }
    }
    return EXIT_SUCCESS;
}