/*
Padre envía señal a n hijos para que impriman algo
*/
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>


char letra = 'A';


void handler(int signum){
    printf("%c\n",letra);
    letra += 1;
    exit(0);
}

int main(){
    pid_t pid; 
    int i;
    for (int i = 1; i <= 3; i++){
        pid = fork();
        if(pid == 0){
            signal(SIGUSR1,handler);
            break;
        }
    }
    if(pid > 0) {
            kill(getpid(),SIGUSR1);
            wait(NULL);
        }
    return 0;
}