#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "delays.h"
#include "process.h"

int main(void){

    printf("Before the fork: PID = %d, PPID = %d\n", getpid(), getppid());
    pid_t ret = pfork();

    if(ret == 0){
        printf("I'm the child: PID = %d, PPID = %d\n", getpid(), getppid());
        for(int i=0; i<10; i++){
            printf("%d\n",i);
        }
    }else{
        printf("I'm the parent: PID = %d, PPID = %d\n", getpid(), getppid());
        pwait(NULL);
        printf("SUCESS\n");
        printf("I'm the parent: PID = %d, PPID = %d\n", getpid(), getppid());
        printf("I'm the child: PID = %d, PPID = %d\n", getpid(), getppid());
    }

    return EXIT_SUCCESS;
}