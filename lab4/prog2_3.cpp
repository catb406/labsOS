#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <cstring>
#include <wait.h>
static int ChildFunc(void* arg)
{
    for (int i=0; i<3; i++)
    {
        printf("Parent pid: %i\nChild pid: %i\n", getppid(), getpid());
        sleep(1);
    }
    exit(1);
}
#define STACK_SIZE (1024*1024)

int main(){
    printf("Program started\n");
    int status;
    char* stack;
    char* stackTop;
    stack=(char*)malloc(STACK_SIZE);
    pid_t child_pid=clone(ChildFunc, stackTop, SIGCHLD, NULL);
    if (child_pid == -1){
        printf("Failed clone a process with error %s\n", strerror(errno));
    }else{
        printf("Child process id: %i\n", getpid());
        printf("Parent process id: %i\n", getppid());
        while (waitpid(child_pid, &status, WNOHANG)==0)
        {
            printf("Waiting...\n");
            usleep(500000);
        }
        printf("Child process finished with code %i\n", WEXITSTATUS(status));
    }
    printf("Program finished\n");
    exit(0);
}