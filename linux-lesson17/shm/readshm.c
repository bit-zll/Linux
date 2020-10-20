#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>


#define KEY Ox99999999

int main()
{
    int shmid = shmget(0x99999999,1024,IPC_CREAT | 0664);
    if(shmid < 0)
    {
        perror("shmget");
        return -1;
    }

    void* lp = shmat(shmid,NULL,0);
    
    while(1)
    {
        printf("%s\n",((char*)lp));
        sleep(1);
    }
    return 0;
}
