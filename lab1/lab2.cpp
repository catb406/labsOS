#include <pthread.h>
#include <iostream>
#include <xdo.h>
#include <semaphore.h>

using namespace std;

typedef struct
{
    int flag;
    char sym;
}threads;
sem_t sem;

void* proc1(void* arg)
{

    threads *args=(threads*) arg;
    printf("Поток %lu запустился\n", pthread_self());
    while (args->flag==0)
    {
        sem_wait(&sem);
        int i=0;
        while (i<4 && args->flag==0)
        {
            putchar(args->sym);
            fflush(stdout);
            i++;
            sleep(1);
        }
        sem_post(&sem);
        sleep(1);
    }
    pthread_exit((void*)1);
}
void *proc2(void *arg)
{
    threads *args=(threads*) arg;
    printf("Поток %lu запустился\n", pthread_self());
    while (args->flag==0)
    {
        sem_wait(&sem);

        int i=0;
        while(i<4 && args->flag==0)
        {
            putchar(args->sym);
            fflush(stdout);
            i++;
            sleep(1);
        }

        sem_post(&sem);
        sleep(1);

    }
    pthread_exit((void*)2);
}

int main() {
    setlocale(LC_ALL,"rus");
    cout<<"Программа начала работу\n";
    threads arg1, arg2;
    arg1.flag=0;
    arg2.flag=0;
    arg1.sym='1';
    arg2.sym='2';
    pthread_t id1;
    pthread_t id2;
    sem_init(&sem, 0, 1);
    pthread_create(&id1, NULL, proc1, &arg1);
    pthread_create(&id2, NULL, proc2, &arg2);
    cout<<"Ожидание нажатия клавиши \n";
    getchar();
    cout<<"Клавиша нажата\n";
    arg1.flag=1;
    arg2.flag=2;

    int exitcode1, exitcode2;

    pthread_join(id1, (void**)&exitcode1);
    printf("Поток %lu завершился с кодом %d\n", id1, exitcode1);
    pthread_join(id2, (void**)&exitcode2);

    printf("Поток %lu завершился с кодом %d\n",id2, exitcode2);
    sem_destroy(&sem);
    cout<<"Программа завершила работу\n";
    return 0;
}
