#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define THREAD_COUNT 4

struct ThreadData
{
    int num_;
    ThreadData()
    {
        num_ = -1;
    }
};

class Data
{
    public:
        void SetData(int data)
        {
            data_=data;
        }
        int GetData()
        {
            return data_;
        }
    private:
        int data_;
};
void* ThreadStrat(void* arg)
{
    //ThreadData* td = (ThreadData*)arg;
    Data* d = (Data*)arg;
    //while(1)
    {
        printf("i am work thread:%d\n",d->GetData());
        sleep(1);
    }
    //释放堆上的内存，应该在线程的内部去释放，当线程不在
    //用的时候
    pthread_exit(NULL);
    while(1)
    {
        sleep(1);
    }
    delete d;
}
int main()
{
    pthread_t tid;
    int i;
    for(i = 0;i < THREAD_COUNT;i++)
    {
        //struct ThreadData* td = new ThreadData;
        //td->num_ = i;
        Data* d = new Data;
        d->SetData(i);
        int ret = pthread_create(&tid,NULL,ThreadStrat,(void*)d);
        if(ret < 0)
        {
            perror("pthread_create");
            return -1;
        }
    }
    while(1)
    {
        printf("i am main thread\n");
        sleep(1);
    }
    return 0;
}
