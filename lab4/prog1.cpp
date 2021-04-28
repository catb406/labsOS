
#include <unistd.h>
#include <cstdio>
#include <iostream>
using namespace std;
int main(int argc, char* argv[]){
    printf("prog1 started\nparent pid: %i\nchild pid: %i\n", getppid(), getpid());

    for (int i=0; i<3; i++)
    {
        printf("%s\t%s\t%s\n", argv[0], argv[1], argv[2]);
        sleep(1);
    }
    exit(1);
}
