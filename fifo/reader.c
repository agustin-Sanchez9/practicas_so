#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char **argv){
    printf("reader starts\n");
    int fd = open("testfifo",O_RDONLY);
    char buffer[100];
    memset(buffer, 0, 100);
    int n = read(fd,buffer,strlen(buffer)+1);
    printf("content: %s\nbytes readed: %d\n",buffer,n);
    printf("press enter to end\n");
    fgets(buffer,100,stdin);
    close(fd);
    return 0;
}