#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int tot_materias;
    
    double *espacio_nota;
    char (*espacio_materia)[20];
    int *espacio_credito;
    char *puntero_inicio;
    double num_creditos;
    double promedio;
    
    printf("Ingrese el numero de materias \n");
    scanf("%d", &tot_materias);
    
    espacio_materia = (char (*)[20])malloc(sizeof(char [20]) * tot_materias);
    espacio_credito = (int *)malloc(sizeof(int) * tot_materias);
    espacio_nota = (double *)malloc(sizeof(double) * tot_materias);


    for(int i=0;i<tot_materias;i++)
    {
        printf("Ingrese el nombre de la materia #%d\n",i+1);
        scanf("%s", (char*)(espacio_materia+i));
        getc(stdin);

        printf("Ingrese el numero de creditos de la materia #%d\n",i+1);
        scanf("%d", (int*)(espacio_credito+i));
        getc(stdin);
        num_creditos += *(espacio_credito+i);
        
        printf("Ingrese la definitiva de la materia #%d\n",i+1);
        scanf("%lf", (double *)(espacio_nota+i));
        getc(stdin);

        promedio += (*(espacio_nota+i))*(*(espacio_credito+i));
        
        
    }
    printf("|Materia|Nota|Creditos|\n");
    for(int i=0;i<tot_materias;i++){
        printf("|%7.7s.|%4.1lf|%4d   |\n",(char *)(espacio_materia+i),*(espacio_nota+i),(*(espacio_credito+i)));
    }
    printf("EL promedio ponderado es: %4.1lf",promedio/num_creditos);
    

    free(espacio_credito);
    free(espacio_materia);
    free(espacio_nota);
}
