#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void sigusr1_handler(int sig) 
{
    // 空处理函数，仅用于唤醒pause()
}

int main(int argc, char* argv[])
{
    char* args1[] = { "/bin/ls","-a",NULL };
    char* args2[] = { "/bin/ps",NULL,NULL };
    int pid1, pid2;
    int status1, status2;
    
    struct sigaction sa;
    sa.sa_handler = sigusr1_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGUSR1, &sa, NULL);
    
    
    while (1)
    {
        printf("wait for 2 seconds\n");
        sleep(2);
        pid1 = fork();
        if (pid1 == 0)
        {
            pause();
            printf("process 1 running \n");
            status1 = execve(args1[0], args1, NULL);
            fflush(stdout);
            exit(status1);
        }
        if (pid1 > 0)
        {
            pid2 = fork();
            if (pid2 == 0)
            {    
                // printf("wait_for %d\n",getppid());
                // fflush(stdout);
                // pause();
                printf("process 2 running \n");
		        status2 = execve(args2[0], args2, NULL);
		        fflush(stdout);
                exit(status2);
            }
            else
            {

                // sleep(1);
                // kill(pid2, SIGUSR1);
                // printf("send_signal %d\n",pid2);
                // fflush(stdout);
                waitpid(pid2, &status2, 0);
                kill(pid1, SIGUSR1);
                waitpid(pid1, &status1, 0);
            }
        }

    }
}