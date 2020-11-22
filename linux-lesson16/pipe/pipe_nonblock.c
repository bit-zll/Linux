#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd[2];
    int ret = pipe(fd);
    if(ret < 0)
    {
        perror("pipe");
        return -1;
    }

    int flag = fcntl(fd[0],F_GETFL);
    fcntl(fd[0],F_SETFL,flag | O_NONBLOCK);

    int pid = fork();
    if(pid < 0)
    {
        perror("fork");
        return -1;
    }
    else if(pid == 0)
    {
        sleep(2);
        close(fd[1]);
        char buf[2]={0};
        int count = 0;
        while(1)
        {
            ssize_t r_size = read(fd[0],buf,sizeof(buf) - 1);
            if(r_size < 0)
            {
                perror("read");
                printf("r_size:%d\n",r_size);
                break;
            }
            if(r_size == 0)
            {
                printf("r_size:%d\n",r_size);
                break;
            }
            count++;
            printf("count:%d\n",count);
        }
    }
    else
    {
        write(fd[1],"hello",5);
        close(fd[1]);
        while(1)
        {
            sleep(1);
        }
    }
#if 0
    int pid = fork();
    if(pid < 0)
    {
        perror("fork");
        return -1;
    }
    else if(pid == 0)
    {
        close(fd[0]);
        int count = 0;
        while(1)
        {
            ssize_t w_size = write(fd[1],"h",1);
            if(w_size < 0)
            {
                perror("write");
                printf("w_size:%d\n",w_size);
                break;
            }
            count++;
            printf("count:%d\n",count);
        }
    }
    else
    {
        close(fd[0]);
        while(1)
        {
            sleep(1);
        }
    }
#endif
    return 0;
}
