#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>


void sigPadre(int sig){}
void sigHijo(int sig){}

int main(){
    pid_t pid = fork();
    char mayus = 'A';
    char minus = 'b';
    int i = 1;
    int fd = open("abcd", O_CREAT| O_WRONLY | O_TRUNC,0777);
    if (pid > 0){
        sleep(1);
        signal(SIGUSR2,sigPadre);
        while(mayus <= 'Z'){
            write(fd,&mayus,1);
            //printf("%c\n",mayus);
            kill(pid,SIGUSR1);
            mayus+=2;
            pause();
        }

    }
    else if(pid == 0){
        signal(SIGUSR1,sigHijo);
        sleep(1);
        while(minus <= 'z'){
            pause();
            write(fd,&minus,1);
            //printf("%c\n",minus);
            kill(getppid(),SIGUSR2);
            minus+=2;
        }
    }
    return 0;
}

