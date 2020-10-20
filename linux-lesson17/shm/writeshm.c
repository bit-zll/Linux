#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>


#define KEY 0x99999999

int main()
{
    int shmid = shmget(0x99999999,1024,IPC_CREAT | 0664);
    if(shmid < 0)
    {
        perror("shmget");
        return -1;
    }

    void* lp = shmat(shmid,NULL,0);
    int i;
   //for( i = 0;i < 1000000;i++)
    {
        char buf[1024]={0};
        sprintf(buf,"%s-%d\n","linux84",1);
        strcpy((char*)lp,buf);
        sleep(1);
    }

    sleep(5);

    shmdt(lp);
    
    struct shmid_ds buf;
    shmctl(shmid,IPC_STAT,&buf);

    printf("%lu\n",buf.shm_segsz);

    sleep(5);
    shmctl(shmid,IPC_RMID,NULL);
    while(1)
    {
        sleep(1);
    }
    return 0;
}
