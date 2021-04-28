#include <iostream>
#include <pthread.h>
#include <sys/types.h>
#include <sys/sysinfo.h>
#include <xdo.h>
#include <cstring>
#include <fcntl.h>
#include <cstdio>
#include <mqueue.h>

using namespace std;
int flag=0;
mqd_t mq;

void* t_func(void* arg){
    printf("opening thread %lu started\n", pthread_self());

    struct sysinfo si;
    char* buf;

    while (flag==0)
    {
        buf=new char;
        sysinfo(&si);
        string message="system uptime "+ to_string(si.uptime);
        strcpy(buf, message.c_str());
        int result = mq_send(mq,buf,message.length()+1,0);
        if (result == -1) {
            perror("mq_send");
        }else{
            printf("Send to queue: %s\n", buf);
        }
        sleep(1);
    }

    pthread_exit((void*)1);
}

int main() {
    printf("program started\n");
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 16;
    attr.mq_msgsize = 32;
    attr.mq_curmsgs = 0;

    pthread_t id;
    mq= mq_open("/myqueue",O_CREAT | O_WRONLY|O_NONBLOCK, 0644, &attr);
    if (mq==(mqd_t)-1){
        perror("mq_open");
    }
    pthread_create(&id, NULL, t_func, nullptr);
    printf("waiting for a key press\n");
    flag=getchar();
    printf("key was pressed\n");
    int retval;
    pthread_join(id,(void**)&retval);
    printf("%lu thread ended with code %i\n", id, retval);
    mq_close(mq);
    mq_unlink("/myqueue");
    printf("program finished\n");
    return 0;
}
