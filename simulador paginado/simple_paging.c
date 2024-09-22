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

int menu(const char *title, const char *options[]);
// creates the main menu and shows the options to continue

void input(char *buffer, int size);
// generic function for data input

int int_input();
// for input of a integer

int confirm(char *msg);
// ask for confirmation to the user

void create_frames_chart(struct data_memory *); 
// requires size_memory, size_os and size_frame

void show_data(struct data_memory * , int);

void fill_frame(struct data_memory * , int nframe , unsigned char os);
// used to occupy the frames of the memory



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


void fill_frame(struct data_memory *m , int nframe , unsigned char os){
    (m->fr+nframe)->state = 1; // ocuppied frame
    (m->fr+nframe)->owner = os; // frame 
};



void create_frames_chart(struct data_memory *m){
    if(m->size_memory && m->size_frame && m->size_os){
        m->nframe = m->size_memory / m->size_frame;
        m->nframe_os = m->size_os / m->size_frame;
        if(m->size_os % m->size_frame) m->nframe_os++;
        m->nframes_free = m->nframe - m->nframe_os;
        // free memory
        if(m->fr) free(m->fr);
        m->fr = (struct data_frame *) malloc(sizeof(struct data_frame) * m->nframe);
        memset(m->fr,0,sizeof(struct data_frame) * m->nframe); // m->fr = 0;
        // fill the frames for the os
        for(int i = 0; i < m->nframe_os; i++){
            fill_frame(m,i,1);
        }
    }
    else{
        printf("");
    }
}


void show_data(struct data_memory *m , int option){

    printf("Memory Size: %d\nOs Size: %d\nFrame Size: %d\nMemory Frames: %d\nOs Frames: %d\nFree Frames: %d\n",
		m->size_memory,m->size_os,m->size_frame,m->nframe,m->nframe_os,m->nframes_free);

    if(m->fr){
        struct data_frame *f = m->fr;
        for(int i=0; i < m->nframe; i++,f++){
            printf("FRAME: %d  STATE: %d  OWNER: %d\n",i,(int) f->state,(int) f->owner);
        }
    }
    if(m->pcb){
        struct data_process *p = m->pcb;
        for(int i=0; i < m->nproc; i++, p++){
            printf("PROCESS: %d  SIZE: %dKB  NFRAMES: %d\n",p->pid,p->size_proc,p->nframes_proc);
            if(p->frames_chart){
                for(int j=0; j < p->nframes_proc; j++){
                    printf("\t#PAGE: %d  FRAME: %d\n",j,*(p->frames_chart+j));
                }
            }
        }
    }
}