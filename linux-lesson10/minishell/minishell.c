#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/wait.h>
char g_command[1024];
int GetCommand()
{
    printf("[minishell@localhost minishell]");
    fflush(stdout);
    memset(g_command,'\0',sizeof(g_command));
    if(fgets(g_command,sizeof(g_command)-1,stdin)==NULL)
    {
        perror("fgets error");
        return -1;
    }
    printf("%s\n",g_command);
    return 0;
}

int ExecCommand(char* argv[])
{
    if(argv[0]==NULL)
    {
        printf("ExecCommand failed\n");
        return -1;
    }
    pid_t pid=fork();
    if(pid<0)
    {
        perror("fork");
        return -1;
    }
    else if(pid==0)
    {
        //child  进程程序替换
        execvp(argv[0],argv);
        exit(0);
    }
    else
    {
        //father  进程等待，防止子进程变成僵尸进程
        waitpid(pid,NULL,0);
    }
}
int DealCommand(char* command)
{
    //ls -l  ls可执行程序  -l 传递给ls的命令行参数
    int argc=0;
    char* argv[1024]={0};
    while(*command)
    {
        //判断当前的字符是否是空格或者\0
        if(!isspace(*command)&&*command!='\0')
        {
            argv[argc]=command;
            argc++;
            while(isspace(*command)&&*command!='\0')
            {
                command++;
            }
            *command='\0';
        }
        command++;
    }
    argv[argc]=NULL;
    int i=0;
    for(i=0;i<argc;i++)
    {
        printf("%d:%s\n",i,argv[i]);
    }
    ExecCommand(argv);
    return 0;
}
int main()
{
    while(1)
    {
        //1.获取用户输入的命令
       if( GetCommand()==-1)
       {
           continue;
       }
        //2.创建子进程
        
        //3.让子进程进行程序替换
        //4.进程等待
        DealCommand(g_command);
    }
    return 0;
}
