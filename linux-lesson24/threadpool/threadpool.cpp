#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <queue>
#include <vector>

//1.自定义
//数据
//处理数据的方法（函数）

typedef void (*Handler)(int);
class Data
{
    public:
        Data(int data,Handler handler)
        {
            data_ = data;
            handler_ = handler;
        }

        void run()
        {
            handler_(data_);
        }
    private:
        int data_;
        Handler handler_;
};

void func(int data)
{
    printf("data:%d\n",data);
}

//线程安全的队列，队列的类型为自定义类型
//线程数量
class ThreadPoll
{
    public:
        ThreadPoll(int thread_count,int capa)
        {
            pthread_mutex_init(&mutex_,NULL);
            pthread_cond_init(&cond_,NULL);

            capacity_ = capa;
            thread_count_ = thread_count;
            vec_.clear();
            printf("%d\n",thread_count);
            vec_.resize(thread_count);

            flag = false;
        }

        ~ThreadPoll()
        {
            pthread_mutex_destroy(&mutex_);
            pthread_cond_destroy(&cond_);
        }

        int Oninit()
        {
            //启动线程池当中的线程
            int ret = CreatThread();
            if(ret < 0)
            {
                return -1;
            }
            return 0;
        }

        void Push(Data* d)
        {
            pthread_mutex_lock(&mutex_);
            while(que_.size()>=capacity_)
            {
                pthread_mutex_unlock(&mutex_);
                return;
            }
            que_.push(d);
            pthread_mutex_unlock(&mutex_);
            pthread_cond_signal(&cond_);
        }

        void Pop(Data** d)
        {
            *d = que_.front();
            que_.pop();
        }

        void PthreadJoin()
        {
            size_t i;
            for(i = 0;i < vec_.size();i++)
            {
                printf("-----linux-----\n");
                pthread_join(vec_[i],NULL);
            }
        }
    private:
        int CreatThread()
        {
            int i;
            for(i = 0;i<thread_count_;i++)
            {
                int ret = pthread_create(&vec_[i],NULL,ThreadStart,(void*)this);
                if(ret<0)
                {
                    return -1;
                }
            }
            return 0;
        }

        static void* ThreadStart(void* arg)
        {
            ThreadPoll* tp = (ThreadPoll*)arg;
            while(1)
            {
                pthread_mutex_lock(&tp->mutex_);
                while(tp->que_.empty())
                {
                    if(tp->flag)
                    {
                        pthread_exit;
                    }
                    pthread_cond_wait(&tp->cond_,&tp->mutex_);
                }

                Data* d;
                tp->Pop(&d);
                pthread_mutex_unlock(&tp->mutex_);

                d->run();
                delete d;
            }
            return NULL;
        }
    private:
        std::queue<Data*> que_;
        int capacity_;
        pthread_mutex_t mutex_;
        //线程池当中线程（相当于消费线程）使用的条件变量
        pthread_cond_t cond_;

        //线程数量
        int thread_count_;
        std::vector<pthread_t> vec_;

        int flag;
};

int main()
{
    ThreadPoll* tp = new ThreadPoll(4,1);
    if(!tp)
    {
        printf("init threadpool failed\n");
        return -1;
    }

    if(tp->Oninit()<0)
    {
        printf("threadpool create thread failed\n");
        return -1;
    }

    //1.往线程池当中的队列push数据
    int i;
    for(i = 0;i < 500;i++)
    {
        Data* d = new Data(i ,func);
        if(!d)
        {
            continue;
        }
        tp->Push(d);
        usleep(1000);
    }

    //2.等待线程池当中的线程退出
    tp->PthreadJoin();
    delete tp;
    return 0;
}
