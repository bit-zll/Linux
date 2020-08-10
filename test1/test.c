#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid=fork();
    if(pid<0)
    {
        perror("fork");
        return 0;
    }
    else if(pid>0)
    {
        int count=20;
        while(1)
        {
            if(count<=0)
            {
                break;
            }
            printf("i am father,pid=[%d],ppid=[%d]\n",getpid(),getppid());
            count--;
            sleep(1);
        }
    }
    else
    {
        while(1)
       {
            printf("i am child ,pid=[%d],ppid=[%d]\n",getpid(),getppid());
            sleep(2);
       }
    }
    return 0;
}
