#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

char letra = 'a';

void handler(int sig){
    for(int i=0; i<5; i++){
        printf("%c\n",letra);
        letra++;
    }
    exit(0);
}

int main(){
    int n = 5;
    pid_t pid;
    signal(SIGUSR1,handler);
    while(n != 0){
        pid = fork();
        if(pid == 0) break;
        n--;
    }
    if(pid == 0){
        pause();
    }else{
        sleep(1);
        kill(0,SIGUSR1);
        for(int i=0; i<=5; i++){
            wait(NULL);
        }
    }

    return 0;

}


