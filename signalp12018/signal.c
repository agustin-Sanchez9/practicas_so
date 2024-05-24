#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>


void handler(int s){
    printf("Padre dice hola\n");
}

int main(void) {
    pid_t pid, finh;
    int status;
    pid = fork();
    if (pid > 0) {
        signal(SIGUSR1, handler);
        finh = wait(&status);
    }
    else {
        alarm(5);
        while(1){
            kill(getppid(), SIGUSR1);
        }
        exit(0);
    }
    return 0 ;
}