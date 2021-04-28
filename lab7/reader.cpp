#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysinfo.h>
#include <xdo.h>
#include <cstring>
#include <fcntl.h>
#include <cstdio>

using namespace std;
int flag=0;
int fd_fifo;

void* t_read(void* arg){
    printf("reading thread %lu started\n", pthread_self());
    struct sysinfo si;
    while (flag==0)
    {
        char buf [64];
        if (read(fd_fifo, &buf, 64) > 0)
        {
            printf("Reader: %s\n", buf);
        }
        else
        {
            printf("reading fifo is empty\n");
        }

        sleep(1);
    }
    pthread_exit((void *)3);

}

int main() {

    printf("program started\n");
    pthread_t id;
    mkfifo("/tmp/my_named_pipe", 0644);
    fd_fifo = open("/tmp/my_named_pipe", O_CREAT|O_RDONLY|O_NONBLOCK);
    pthread_create(&id, NULL, t_read, nullptr);
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

