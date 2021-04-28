
#include <pthread.h>
#include <iostream>
#include <xdo.h>

using namespace std;

typedef struct
{
    int flag;
    char sym;
} targs;

 void* proc1(void* arg)
{     printf("Potok %lu\n", pthread_self());

    targs * args=(targs*) arg;
    while (args->flag==0)
    {
        putchar(args->sym);
        fflush(stdout);//позволяет выводить символы на экран без буферизации
        sleep(1);
    }

    pthread_exit((void*)1);
}
 void* proc2(void* arg)
{

     printf("Potok %lu\n", pthread_self());
     targs* args=(targs*) arg;
    while (args->flag==0)
    {
        putchar(args->sym);
        fflush(stdout);//позволяет выводить символы на экран без буферизации
        sleep(2);
    }
    pthread_exit((void*)2);
}
int main() {
     setlocale(LC_ALL, "rus");
    cout<<"программа начала работу\n";
    targs arg1;
    targs arg2;
    arg1.flag=0;
    arg1.sym='1';
    arg2.flag=0;
    arg2.sym='2';

    pthread_t id1;
    pthread_t id2;

    int th_val1=pthread_create(&id1, NULL, proc1, &arg1);
    if (th_val1==0)
    {
        printf("поток %lu запустился\n", id1);
    }

    int th_val2=pthread_create(&id2, NULL, proc2, &arg2);
    if (th_val2==0)
    {
        printf("\nпоток %lu запустился\n", id2);
    }
    cout<<"программа ожидает нажатия клавиши\n";
    getchar();
    cout<<"клавиша нажата\n";
    arg1.flag=1;
    arg2.flag=1;
    int exitcode;
    pthread_join(id1,(void**)&exitcode);
    printf("поток %lu завершился с кодом %d\n", id1, exitcode);

    pthread_join(id2,(void**)&exitcode);
    printf("поток %lu завершился с кодом %d\n", id2, exitcode);
    cout<<"программа завершила работу\n";

    return 0;
}
