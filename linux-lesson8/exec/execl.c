#include <stdio.h>
#include <unistd.h>
#if 0
int main(int argc,char* argv[],char* env[])
{
    //argc:命令行参数的个数
    //argv:命令行参数的内容
    //env:环境变量
    printf("argc:%d\n",argc);
    int i=0;
    for(i=0;i<argc;i++)
    {
        printf("%s\n",argv[i]);
    }
    return 0;
}
#endif

int main()
{
    printf("---begin---\n");
    execl("/usr/bin/ls","ls","-al",NULL);
    printf("----end----\n");
    return 0;
}
