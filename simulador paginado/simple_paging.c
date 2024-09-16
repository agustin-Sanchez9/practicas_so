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


struct data_frame {
    unsigned char state; // 0 = free, 1 = ocuppied
    unsigned char owner; // 0 = os, 1 = user
} data_frame;


struct data_memory{
    int size_memory;
    int size_so;
    int size_frame;
    int nframe; // number of existing frames
    int nframe_os; // number of os frames
    int nframes_free; // number of free frames
} data_memory;


struct data_process{
    // pid_t pid
    // int nframes_proc (number of pages of the process)
    // int proc_frames[] (integers array to save the pages the process owns)
} data_process;

// funcion ocupar frames
// funcion mostrar datos
// a la hora de agregar un proceso chequear si entra en los frames disponibles
// bloque de control de procesos "bcp"
