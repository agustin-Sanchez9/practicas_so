#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>


int status;

int main(void){
    pid_t pid,finhijo;
    pid = fork();
    printf("esperando a mi primer hijo\n");
    finhijo = wait(&status);
    if( pid > 0){
        pid = fork();
        printf("esperando a mi segundo hijo\n");
        finhijo = wait(&status);
        if( pid > 0){
            pid = fork();
            printf("esperando a mi tercer hijo\n");
            finhijo = wait(&status);
            if( pid > 0){
                pid = fork();
                printf("esperando a mi cuarto hijo\n");
                finhijo = wait(&status);
            }
        }
    }
    if( pid == 0){
        printf("hijo ejecutando\n");
        sleep(2);
        exit(0);
    }
    return 0;
}