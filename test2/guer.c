#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    pid_t pid=fork();
    if(pid<0)
    {
        perror("fork");
        return 0;
    }
    else if(pid==0)
    {
        sleep(5);
        printf("i am child pid=[%d],ppid=[%d]\n",getpid(),getppid());
    }
    else
    {
        printf("i am father pid=[%d],ppid=[%d]\n",getpid(),getppid());
        sleep(2);
    }
    return 0;
}
