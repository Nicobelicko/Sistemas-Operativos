#include <pthread.h>
#include <stdio.h>

struct parametros_hilo
{
    char caracter;
    int contador;
};

void* imprimir_caracter(void* parametros){
    struct parametros_hilo* p = (struct parametros_hilo*) parametros;
    int i;
    for (i = 0; i<p->contador;i++){
        fputc(p->caracter,stderr);

    }
    return NULL;
}
int main(int argc, char const *argv[])
{
    pthread_t id_hilo_1;
    pthread_t id_hilo_2;

    struct parametros_hilo hilo_1_param;
    struct parametros_hilo hilo_2_param;

    hilo_1_param.caracter = 'x';
    hilo_1_param.contador = 30000;
    pthread_create (&id_hilo_1,NULL,&imprimir_caracter,&hilo_1_param);

    hilo_2_param.caracter = 'O';
    hilo_2_param.contador = 20000;
    pthread_create (&id_hilo_2,NULL,&imprimir_caracter,&hilo_2_param);

    pthread_join(id_hilo_1,NULL);
    pthread_join(id_hilo_2,NULL);

    

    return 0;
}
