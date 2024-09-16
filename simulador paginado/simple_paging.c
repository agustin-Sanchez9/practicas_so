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
} data_memory;



// funcion ocupar frames
// funcion mostrar datos