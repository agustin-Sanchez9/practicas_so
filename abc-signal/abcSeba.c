#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

void signal_handler(int sigNUM){
    printf("HIJO SALE DE PAUSA CON:%d\n" , sigNUM);
}
void signal_handler_2(int sigNUM2){
    printf("PADRE SALE DE PAUSA CON:%d\n" , sigNUM2);
}

int main(void){
    pid_t pid;
    int fd = open("abec", O_CREAT| O_WRONLY | O_TRUNC,0777);
    char letra = 'A'; 
    char letrah = 'b';
    char espacio='\n';
    pid = fork();
    if (pid > 0){
        signal(SIGUSR2, signal_handler_2);
        while (letra <= 'Z'){
            write(fd, &letra, 1);
            letra += 2;
            printf("soy el padre mi pid es: %d \n",getpid());
            printf("PADRE ENTRA EN PAUSA\n");
            kill(pid, SIGUSR1);
            pause();

        }
    }else if (pid == 0){
        signal(SIGUSR1, signal_handler);
        while(letrah <= 'z'){
            write(fd, &letrah, 1); 
            letrah += 2;
            printf("soy el hijo mi pid es: %d \n",getpid());
            printf("HIJO ENTRA EN PAUSA\n");
            kill(getppid(), SIGUSR2);
            pause();
        }
    }else {
        printf("error de FORK\n");
    }
    write(fd,&espacio,1);
    close(fd);
    return 0;
}

