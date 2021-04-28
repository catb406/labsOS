#include <pthread.h>
#include <unistd.h>
#include <linux/kernel.h>
#include <cstdio>
#include <cstring>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/mman.h>
using namespace std;

typedef struct
{
    int flag;
} targs;

sem_t* sem_r;
sem_t* sem_w;
int shm;
int *addr;

void* func1(void* args)
{
    printf("thread %lu has started\n", pthread_self());
    targs* arg=(targs*) args;
    while(arg->flag!=1)
    {
        sem_wait(sem_w);
        printf("read: uptime %i seconds\n", *addr);
        sem_post(sem_r);
    }
    pthread_exit((void*)1);
}

int main() {
    printf("program has started\n");
    targs args;
    pthread_t p;
    shm = shm_open("my_shared_memory", O_CREAT|O_RDWR, 0644);
    addr= (int*)mmap(0,sizeof(int),PROT_WRITE|PROT_READ,MAP_SHARED,shm,0);
    ftruncate(shm,sizeof(int));
    sem_r = sem_open("sem_read",O_CREAT,0644,0);
    sem_w = sem_open("sem_write",O_CREAT,0644,0);
    pthread_create(&p, NULL, func1, &args);
    printf("waiting for key press\n");
    getchar();
    args.flag=1;
    printf("key was pressed\n");
    int retval;
    pthread_join(p, (void**)&retval);
    printf("thread exit with code: %i\n", retval);
    munmap(addr, sizeof(int));
    sem_close(sem_r);
    sem_close(sem_w);
    close(shm);
    shm_unlink("my_shared_memory");
    shm_unlink("sem_read");
    shm_unlink("sem_write");
    printf("program finished\n");
    return 0;
}
