#include <stdio.h>
#include <unistd.h>
//调用wait函数用到的文件
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t pid = fork();
    if(pid < 0)
    {
        perror("fork");
        return 0;
    }
    else if(pid == 0)
    {
        int count = 20;
        while(1)
        {
           if(count<=0)
           {
                break;
            }
            printf("i am child pid = [%d],ppid = [%d]\n",getpid(),getppid());
            count--;
            sleep(1);
        }
        exit(10);
    }
    else
    {
        printf("begin--->i am father pid=[%d],ppid=[%d]\n",getpid(),getppid());
        int status;
        printf("child pid num is %d\n",pid);
       while( waitpid(pid,&status,WNOHANG)==0);
       // printf("exit_code : %d\n",(status>>8)&0xFF);
        printf("sig_code : %d\n",status & 0x7F);
        printf("coredump_code : %d\n",(status>>7)&0x1);
        while(1)
        {
            printf("i am father pid=[%d],ppid=[%d]\n",getpid(),getppid());
            sleep(1);
        }
    }
        
    return 0;
}
