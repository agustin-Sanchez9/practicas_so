/*
restas frame de so y marco como ocupados

vector que guarde info de los frames

opcion de monitoreo

Mediante "opciones" permitir eegir que hacer
ej:
    cargar tamaños
    monitoreo
    cargar proceso

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>


struct data_frame {
    unsigned char state; // 0 = free, 1 = ocuppied
    unsigned char owner; // 0 = os, 1 = user
} data_frame;


struct data_memory{
    int size_memory;
    int size_os;
    int size_frame;
    int nframe; // number of existing frames
    int nframe_os; // number of frames ocuppied by the os
    int nframes_free; // number of free frames
    int nproc; // number of processes
    struct data_frame *fr; // pointer to the nframe, can be data_frame or NULL
    struct data_process *pcb; // pointer for every process control block
} data_memory;


struct data_process{
    int pid;
    int size_proc;
    int nframes_proc;
    int *frames_chart; 
} data_process;

/////////////////////// FUNCTIONS ///////////////////////

void create_frames_chart(struct data_memory *); 
// requires size_memory, size_os and size_frame

void show_data(struct data_memory * , int);

void fill_frame(struct data_memory * , int nframe , unsigned char os);
// used to occupy the frames of the memory

int menu(const char *title, const char *options[]);
// creates the main menu and shows the options to continue

void input(char *buffer, int size);
// generic function for data input

int int_input();
// for input of a integer

int confirm(char *msg);
// ask for confirmation to the user




int main(int argc, char **argv){


    return 0;
}



int menu(const char *title , const char *options[]){
    int i, op_counter, op_chosen;
    do{
        printf("\t\t%s\n",title);
        while(options[i]){
            printf("\t%2.0d. %s\n",op_counter,options[i]);
            op_counter++;
            i++;
        }
        printf("\t99. Salir\n");
        printf("Select an option: ");
        op_chosen = int_input();
        if(op_chosen == 99) return 99;
    } while(op_chosen <= 0 || op_chosen > (op_counter-1));
    return op_chosen;

}

void input(char *buffer, int size){
    fgets(buffer,size,stdin);
    buffer[strlen(buffer)-1]='\0';
}


int int_input(){
    char code[20];
    input(code,20);
    return atoi(code);
}

int confirm(char *msg){
    char answer[4];
    do{
        printf("%s (y/n)",msg);
        input(answer,4);
    }while(!(strcasecmp(answer, "y") == 0 || strcasecmp(answer, "n") == 0));
    if (strcasecmp(answer, "y") == 0) return 1;
    else return 0;
}