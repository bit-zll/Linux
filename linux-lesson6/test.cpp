
//#include "hello.hpp"
#include <stdio.h>
#include <unistd.h>
#include "hello.hpp"
int g_val=100;
int main()
{
    printf("hello~\n");
    pid_t ret=fork();
    if(ret<0)
    {
        perror("fork");
        return 0;
    }
    else if(ret==0)
    {
        //child
       // while(1)
        {
            printf("i am child pid=[%d],ppid=[%d]\n",getpid(),getppid());
            printf("child,g_val:%d\n",g_val);
            print();
            sleep(20);
        }
        
    }
    else
    {
        //ret>0:father
        while(1)
        {
            printf("i am father pid=[%d],ppid=[%d]\n",getpid(),getppid());
            printf("father,g_val:%d\n",g_val); 
            // print();
            sleep(5);
        }
    }
    return 0;
}
