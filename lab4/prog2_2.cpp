#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <cstring>
#include <wait.h>

int main() {
    int status;
    printf("program strted\n");
    pid_t pid = fork();
    char arg0[]="lab_4_0";
    char arg1[]="lab_4_1";
    char arg2[]="lab_4_2";
    int rv;
    //int status;
    if (pid==0)
    {
        //child process
        printf("Child process id: %i\n", getpid());
        rv=execl("./prog1", arg0,arg1, arg2,"./prog1", NULL);
        if (rv==-1)
        {
            printf("Failed run a program with error %s\n", strerror(errno));
        }
    }
    else if (pid==-1)
    {
        //error
        printf("Failed create a process with error %s\n", strerror(errno));
    }
    else
    {
        //parent process
        printf("Parent process id: %i\n", getpid());
        while(waitpid(pid, &status, WNOHANG)==0)
        {
            printf("Waiting...\n");
            usleep(500000);
        }
        printf("Prog1 finished with code %i\n", WEXITSTATUS(status));

    }
    printf("Program finished\n");
    exit(0);
}
