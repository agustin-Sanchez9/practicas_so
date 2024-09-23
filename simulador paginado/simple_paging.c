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

    const char *opc[8] = {"MEMORY SIZE","OS SIZE","FRAME SIZE","RUN PROCESS","KILL PROCESS","SHOW DATA","MAPPING",NULL};

    int option = 0;
    struct data_memory mem;
    memset(&mem,0,sizeof(struct data_memory)); // set mem to 0

    do{
        option = menu("SIMPLE PAGING SIMULATOR", opc);
        switch(option){

            // memory size
            case 1: 
                printf("Enter the memory size (KB): ");
                mem.size_memory = int_input();
                break;

            // os size
            case 2:
                printf("Enter the os size (KB): ");
                mem.size_os = int_input();
                break;
            
            // frame size and then shows data
            case 3:
                printf("Enter the frame size (KB): ");
                mem.size_frame = int_input();
                create_frames_chart(&mem);
                show_data(&mem, 0);
                break;

            // run process
            case 4:
                printf("Enter PID: ");
                int proc_pid = int_input();
                printf("Enter the process size (KB): ");
                int proc_size = int_input();
                int proc_frames = proc_size / mem.size_frame;
                if(proc_size % mem.size_frame) proc_frames++;

                // if free frames are not enough
                if(mem.nframes_free < proc_frames){
                    printf("ERROR: NOT ENOUGH FREE FRAMES FOR THE PROCESS.");
                }
                else{
                    // if free frames are enough
                    mem.nproc++;
                    if(mem.pcb){
                        mem.pcb = (struct data_process *) realloc(mem.pcb, sizeof(struct data_process) * mem.nproc);
                    }
                    else{
                        mem.pcb = (struct data_process *) malloc(sizeof(struct data_process) * mem.nproc);
                    }
                }
                struct data_process *np = mem.pcb + (mem.nproc-1);
                np->pid = proc_pid;
                np->size_proc = proc_size;
                np->nframes_proc = proc_frames;

                // creation of frames chart
                np->frames_chart = (int *) malloc(sizeof(int)*np->nframes_proc);

                // fill frames
                struct data_frame *pf = mem.fr + mem.nframe_os;
                int *pt = np->frames_chart;
                int i = mem.nframe_os;
                int pq = 0;
                for(;i < mem.nframe && pq < np->nframes_proc; i++, pf++){
                    // find free frame
                    if(pf->state == 0){
                        *pt = i;
                        fill_frame(&mem, i, 0);
                        pq++;
                        pt++;
                    }
                }
                mem.nframes_free-=np->nframes_proc;
                show_data(&mem, 0);
                
                break;

            // kill process
            case 5:
                
                printf("Enter the PID: ");
                int kill_proc = int_input();

                printf("//////////////////debug for");
                for(int i=0 ; i < mem.nproc ; i++){
                    if(kill_proc == mem.pcb[i].pid){
                        struct data_process *kp = mem.pcb + i;
                        mem.nframes_free+=kp->nframes_proc;
                        //struct data_frame *pf = mem.fr + i;
                        //free_frame(&mem,);
                        free(kp);
                        printf("////////////////debug free");
                        break;
                    }
                }
                printf("PROCESS %d KILLED", kill_proc);



            // exit
            case 99:
                if(!confirm("WANT TO EXIT? (Y/N): ")) option = 0;
                break;  
        }

    } while(option != 99);

    // free memory
    if(mem.fr) free(mem.fr);
    if(mem.pcb){
        struct data_process *p = mem.pcb;
        for(int j=0; j < mem.nproc; j++,p++){
            if(p->frames_chart) free(p->frames_chart);
        }
        free(mem.pcb);
    }

    return 0;
}



int menu(const char *title , const char *options[]){
    int i, op_counter, op_chosen = 0;
    do{
        op_counter = 1; i = 0;
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
        printf("%s",msg);
        input(answer,4);
    }while(!(strcasecmp(answer, "y") == 0 || strcasecmp(answer, "n") == 0));
    if (strcasecmp(answer, "y") == 0) return 1;
    else return 0;
}


void fill_frame(struct data_memory *m , int nframe , unsigned char os){
    (m->fr+nframe)->state = 1; // ocuppied frame
    (m->fr+nframe)->owner = os; // frame 
};

void free_frame(struct data_memory *m , int nframe , unsigned char os){
    (m->fr+nframe)->state = 0; // ocuppied frame
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
        printf("Fail to create frame charts\n");
    }
}


void show_data(struct data_memory *m , int option){

    printf("--------------------------------------------------------\n");
    printf("MEMORY SIZE: %d\nOS SIZE: %d\nFRAME SIZE: %d\nMEMORY FRAMES: %d\nOS FRAMES: %d\nFREE FRAMES: %d\n",
		m->size_memory,m->size_os,m->size_frame,m->nframe,m->nframe_os,m->nframes_free);
    printf("--------------------------------------------------------\n");

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
    printf("--------------------------------------------------------\n");
}