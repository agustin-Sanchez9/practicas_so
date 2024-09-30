#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char **argv){
    printf("writer starts\n");
    int fd = open("testfifo",O_WRONLY);
    char buffer[100];
    strcpy(buffer, "test");
    int n = write(fd,buffer,strlen(buffer)+1);
    printf("bytes saved: %d\n",n);
    printf("press enter to end\n");
    fgets(buffer,100,stdin);
    close(fd);
    return 0;
}