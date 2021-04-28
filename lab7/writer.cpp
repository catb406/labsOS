#include <iostream>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysinfo.h>
#include <xdo.h>
#include <cstring>
#include <wait.h>
#include <fcntl.h>
#include <cstdio>

using namespace std;
int flag=0;
int fd_fifo;

void* t_send(void* arg);
void* t_open(void* arg);
void sig_handler(int signo)
{
    printf("get SIGPIPE\n");
}
void* t_open(void* arg){
    printf("opening thread %lu started\n", pthread_self());

    while (flag==0){
        fd_fifo=open("/tmp/my_named_pipe",O_CREAT|O_WRONLY|O_NONBLOCK);
        pthread_t id_s;

        if (fd_fifo==-1){
            printf("reader does not started\n");
            sleep(1);
        }
        else
        {
            pthread_create(&id_s, nullptr, t_send, nullptr);
            int retval;
            pthread_join(id_s, (void**)&retval);
            printf("%lu thread ended with code %i\n", id_s, retval);
        }
    }
    pthread_exit((void*)1);
}
void* t_send(void* arg){
    printf("sending thread %lu started\n", pthread_self());
    struct sysinfo si;
    char* buf;
    while (flag==0)
    {
        buf=new char;
        sysinfo(&si);
        string message="system uptime "+ to_string(si.uptime);
        strcpy(buf, message.c_str());
        write(fd_fifo, buf, message.size());
        printf("writer: %s\n", buf);
        sleep(1);
    }
    pthread_exit((void *)2);

}

int main() {
    signal(SIGPIPE,sig_handler);
    printf("program started\n");
    pthread_t id;
    mkfifo("/tmp/my_named_pipe", 0644);
    pthread_create(&id, NULL, t_open, nullptr);
    printf("waiting for a key press\n");
    flag=getchar();
    printf("key was pressed\n");
    int retval;
    pthread_join(id,(void**)&retval);
    printf("%lu thread ended with code %i\n", id, retval);

    close(fd_fifo);
    unlink("/tmp/my_named_pipe");
    printf("program finished\n");
    return 0;
}
