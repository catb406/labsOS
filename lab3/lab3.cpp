#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <linux/kernel.h>
#include <cstdio>
#include <cstring>
using namespace std;

typedef struct
{
    int flag;
} targs;

int fd[2];

void* writer(void* args)
{
    targs* arg= (targs*) args;
    printf("---writer %lu started---\n", pthread_self());
    char buf[64];
    struct sysinfo si;
    while(arg->flag!=1)
    {
        sysinfo(&si);
        string message="system uptime: "+ to_string(si.uptime/60)+" minutes "+to_string(si.uptime%60)+" seconds";
        strcpy(buf, message.c_str());
        write(fd[1], buf, message.size());
        sleep(1);
    }
    printf("---writer %lu ended---\n", pthread_self());
    pthread_exit(NULL);
}
void* reader(void* args)
{
    targs * arg=(targs*) args;
    printf("---reader %lu started---\n", pthread_self());
    char buf[64];
    while (arg->flag!=1)
    {
        read(fd[0], buf, 64);
        printf("%s\n", buf);
        sleep(1);
    }

    printf("---reader %lu ended---\n", pthread_self());
    pthread_exit(NULL);
}

int main() {
    cout<<"---Program started---\n";
    targs wr_args, read_args;
    wr_args.flag=0;
    read_args.flag=0;
    pthread_t wr;
    pthread_t read;
    pipe(fd);
    pthread_create(&wr, NULL, writer, &wr_args);
    pthread_create(&read, NULL, reader, &read_args);
    cout<<"---Waiting for a key press---\n";
    getchar();
    cout<<"---The key has been pressed---\n";
    wr_args.flag=1;
    read_args.flag=1;
    pthread_join(wr, NULL);
    pthread_join(read, NULL);

    close(fd[0]);
    close(fd[1]);
    cout<<"---Program ended---\n";
    return 0;
}
