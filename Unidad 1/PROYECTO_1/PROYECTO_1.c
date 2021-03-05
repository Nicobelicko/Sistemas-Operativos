#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *obtenerlinea(void);
void mkdb(char *nombre, int registros);
void mkreg(int ced, char *nomEstudiante, int sem);
void loaddb(FILE *input);
void savedb(FILE *output);
void readall();
void readsize();
void readreg(int cedula);
typedef struct estudiante
{
    int cedula;
    char nombre[30];
    int semestre;
} estudiante;
typedef struct BD
{
    char nombre[20];
    int numRegistros;
    estudiante *registro;

} BD;

BD *ptrBasesDatos;
estudiante *ptrEstudiantes;


int regActual = 0;
int mkdbCONTROL = 0;
int loaddbCONTROL = 0;
int CONTROL = 0;
int main()
{
    int salida = 0;
   
    char comando[100];


    do
    {
        printf("Ingrese el comando\n");
        fscanf(stdin, "%s", comando);
        if (strncmp("mkdb", comando, 4) == 0)
        {
            regActual = 0;

            CONTROL = 1;
            char nombreDB[30];
            int cant_registros;
            fscanf(stdin, "%s", nombreDB);

            fscanf(stdin, "%d", &cant_registros);

            mkdb(nombreDB, cant_registros);
          
        }
        else if (strncmp("mkreg", comando, 5) == 0)
        {
            if (CONTROL == 0)
            {
                printf("PRIMERO DEBE CREAR O CARGAR LA BASE DE DATOS\n");
            }
            {
                char nomEstudiante[30];
                int ced = 0;
                int sem = 0;
                fscanf(stdin, "%d", &ced);
                getc(stdin);
                fscanf(stdin, "%s", nomEstudiante);

                fscanf(stdin, "%d", &sem);

                mkreg(ced, nomEstudiante, sem);
            }
        }
        else if (strncmp("loaddb", comando, 6) == 0)
        {
            regActual = 0,

            CONTROL = 1;
            FILE *input;

            char nombreArchivo[30];
            fscanf(stdin, "%s", nombreArchivo);
            getc(stdin);
            input = fopen(nombreArchivo, "r");
            if (input == NULL)
            {
                perror("Error: NO SE ENCONTRO EL ARCHIVO ESPECIFICADO");
                main();
            }

            loaddb(input);
            fclose(input);
        }
        else if (strncmp("savedb", comando, 6) == 0)
        {
            if (CONTROL == 0)
            {
                printf("PRIMERO DEBE CREAR O CARGAR LA BASE DE DATOS\n");
                main();
            }
            {
                FILE *output;

                char nombreArchivo[30];
                fscanf(stdin, "%s", nombreArchivo);
                getc(stdin);
                output = fopen(nombreArchivo, "w");
                if (output == NULL)
                {
                    perror("Error: NO SE ENCONTRO EL ARCHIVO ESPECIFICADO");
                }
                else
                {

                    savedb(output);
                    fclose(output);
                }
            }
        }
        else if (strncmp("readall", comando, 7) == 0)
        {
            if (CONTROL == 0)
            {
                printf("PRIMERO DEBE CREAR O CARGAR LA BASE DE DATOS\n");
                main();
            }
            {
                readall();
            }
        }
        else if (strncmp("readsize", comando, 8) == 0)
        {
            if (CONTROL == 0)
            {
                printf("PRIMERO DEBE CREAR O CARGAR LA BASE DE DATOS\n");
                main();
            }
            else
            {
                readsize();
            }
        }
        else if (strncmp("readreg", comando, 7) == 0)
        {
            if (CONTROL == 0)
            {
                printf("PRIMERO DEBE CREAR O CARGAR LA BASE DE DATOS\n");
            }
            else
            {
                int cedula = 0;
                fscanf(stdin, "%d", &cedula);
                readreg(cedula);
            }
        }
        else if (strncmp("exit", comando, 4) == 0)
        {
            int opcion = 0;
            FILE *output;
            printf("Quiere guardar la base de datos\n1.SI\n2.NO\n");
            scanf("%d", &opcion);
            switch (opcion)
            {
            case 1:

                output = fopen(ptrBasesDatos->nombre, "w");
                savedb(output);
                fclose(output);
                break;

            default:
                break;
            }
            salida = 1;
        }
    } while (salida == 0);
    free(ptrEstudiantes);
    free(ptrBasesDatos);
    return 0;
}
void mkdb(char *nombreBD, int cantregistros)
{
    
    
    ptrBasesDatos = (BD(*))malloc(sizeof(BD));
    ptrEstudiantes = (estudiante(*))malloc(cantregistros * sizeof(estudiante));
    strcpy(ptrBasesDatos->nombre, nombreBD);
    ptrBasesDatos->numRegistros = cantregistros;

    printf("La base de datos actual es: %s\n", ptrBasesDatos->nombre);
    printf("num de registros de: %s es: %d\n", ptrBasesDatos->nombre, ptrBasesDatos->numRegistros);
}
void mkreg(int ced, char *nomEstudiante, int sem)
{
    if (regActual == ptrBasesDatos->numRegistros)
    {
        printf("YA ALCANZO EL MAXIMO DE REGISTROS POSIBLES\n");
    }
    else
    {

        strcpy(ptrEstudiantes[regActual].nombre, nomEstudiante);
        ptrEstudiantes[regActual].cedula = ced;
        ptrEstudiantes[regActual].semestre = sem;
        regActual++;
        printf("\n---NUEVO REGISTRO CREADO---\n");

        
    }
}
void loaddb(FILE *input)
{
    
    
    int totregistros;
    char nombreDB[30];
    char nomEstudiante[30];
    int cedula = 0;
    int semestre = 0;

    fscanf(input, "%s", nombreDB);

    fscanf(input, "%d", &totregistros);

    mkdb(nombreDB, totregistros);

    for (int i = 0; i < totregistros; i++)
    {
        fscanf(input, "%d %s %d", &cedula, nomEstudiante, &semestre);
        if (cedula != 0 && nomEstudiante != NULL && semestre != 0)
        {
            mkreg(cedula, nomEstudiante, semestre);
        }
    }
}
void savedb(FILE *output)
{

    fprintf(output, "%s", ptrBasesDatos->nombre);
    fprintf(output, "\n");
    fprintf(output, "%d", ptrBasesDatos->numRegistros);
    fprintf(output, "\n");

    for (int i = 0; i < ptrBasesDatos->numRegistros; i++)
    {
        fprintf(output, "%d %s %d", ptrEstudiantes[i].cedula, ptrEstudiantes[i].nombre, ptrEstudiantes[i].semestre);
        fprintf(output, "\n");
    }
}
void readall()
{
    printf("| Cedula | | Nombre | Semestre |\n\n");
    for (int i = 0; i < regActual; i++)
    {
        printf("| %d | %s | %d |\n", ptrEstudiantes[i].cedula, ptrEstudiantes[i].nombre, ptrEstudiantes[i].semestre);

        printf("\n");
    }
    printf("\n");
}
void readsize()
{
    printf("La cantidad de registros actualmente es de: %d\n", regActual);
}
void readreg(int cedula)
{
    for (int i = 0; i < regActual; i++)
    {
        if (ptrEstudiantes[i].cedula == cedula)
        {
            printf("| %d | %s | %d |\n", ptrEstudiantes[i].cedula, ptrEstudiantes[i].nombre, ptrEstudiantes[i].semestre);
            break;
        }
    }
}
