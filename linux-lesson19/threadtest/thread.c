#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
void* start_thread(void* arg)
{
   //while(1)
    {
        printf("84-linux\n");
        sleep(1);
    }
}

int main()
{
    pthread_t tid;
    int ret = pthread_create(&tid,NULL,start_thread,NULL);
    if(ret<0)
    {
        perror("pthread_creat");
        return -1;
    }
    while(1)
    {
        printf("i am main thread\n");
        sleep(1);
    }
    return 0;
}
