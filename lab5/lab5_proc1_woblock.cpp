#include <pthread.h>
#include <iostream>
#include <xdo.h>
#include <semaphore.h>
#include <cstring>
#include <fcntl.h>
#include <cstdio>

using namespace std;

typedef struct
{
    FILE* file;
    int flag;
    char sym;
}threads;
sem_t* sem;

void* proc1(void* arg) {
    threads *args = (threads *) arg;
    FILE* f=args->file;
    while (args->flag == 0) {

        if (sem_trywait(sem)!=0)
        {
            printf("ждем общий ресурс\n");
        }
        else {
            for (int i = 0; i < 3; i++) {


                printf("программа 1 пишет в файл\n");
                fflush(stdout);
                fputc(args->sym, f);
                fflush(f);
                sleep(1);
            }

            sem_post(sem);
        }
        sleep(1);
    }
    pthread_exit((void *) 1);
}

int main() {
    setlocale(LC_ALL,"rus");
    cout<<"Программа начала работу\n";
    threads arg1;
    arg1.flag=0;
    arg1.sym='2';
    arg1.file=fopen("lab.txt", "a+");
    pthread_t id1;
    sem=sem_open("sem1", O_CREAT, 0644, 1);
    pthread_create(&id1, NULL, proc1, &arg1);
    cout<<"Ожидание нажатия клавиши \n";
    getchar();
    cout<<"Клавиша нажата\n";
    arg1.flag=1;

    int exitcode1;

    pthread_join(id1, (void**)&exitcode1);
    printf("Поток %lu завершился с кодом %d\n", id1, exitcode1);
    sem_close(sem);
    sem_unlink("sem1");
    fclose(arg1.file);
    cout<<"Программа 2 завершила работу\n";
    return 0;
}
