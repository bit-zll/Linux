#include <stdio.h>

#include <unistd.h>

int main()
{
    //execl 进程程序替换
    printf("hahaha,begin...\n");
#if 0
    getchar();
    //如果看到pwd结果，表示替换成功
    printf("pid:%d\n",getpid());
    execl("/usr/bin/pwd","pwd",NULL);
    printf("execl failed\n");
#endif

#if 0
    execlp("ls","ls","-l",NULL);
    printf("execlp failed\n");
#endif

#if 0
    char* argv[10];
    argv[0]="ls";
    argv[1]="-l";
    argv[2]="..";
    argv[3]=NULL;
    execv("/usr/bin/ls",argv);
#endif
    char* argv[10];                                               
    argv[0]="ls";                                                 
    argv[1]="-l";                                                 
    argv[2]="..";                                                 
    argv[3]=NULL;

    char *envp[10];
    envp[0]="PATH=/usr/bin";
    envp[1]=NULL;
    execve("/usr/bin/ls",argv,envp);
    return 0;
}
