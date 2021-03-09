#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mdb(char *nombre, int registros);
void mreg(int ced, char *nomEstudiante, int sem);
void ldb(FILE *input);
void svdb(FILE *output);
void radb();
void rsdb();
void rr(int cedula);
void lsdbs();
void sdb(char* nombre);
void gdb();
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
    int regActuales;
    estudiante *registro;

} BD;

BD *ptrBasesDatos;
estudiante *ptrEstudiantes;
BD *basesDatos[30];

int CONTROL = 0;
int contBD = 0;
int main()
{
    int salida = 0;

    char comando[100];

    do
    {
        printf("Ingrese el comando\n");
        fscanf(stdin, "%s", comando);
        if (strncmp("mdb", comando, 3) == 0)
        {

            CONTROL = 1;
            char nombreDB[30];
            int cant_registros;
            fscanf(stdin, "%s", nombreDB);

            fscanf(stdin, "%d", &cant_registros);

            mdb(nombreDB, cant_registros);
        }
        else if (strncmp("mreg", comando, 4) == 0)
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

                mreg(ced, nomEstudiante, sem);
            }
        }
        else if (strncmp("lsdbs", comando, 5) == 0)
        {
            if (CONTROL == 0)
            {
                printf("PRIMERO DEBE CREAR O CARGAR LA BASE DE DATOS\n");
            }
            {

                lsdbs();
            }
        }
        else if (strncmp("gdb", comando, 3) == 0)
        {
            if (CONTROL == 0)
            {
                printf("PRIMERO DEBE CREAR O CARGAR LA BASE DE DATOS\n");
            }
            {

                gbd();
            }
        }
        else if (strncmp("sdb", comando, 3) == 0)
        {
            if (CONTROL == 0)
            {
                printf("PRIMERO DEBE CREAR O CARGAR LA BASE DE DATOS\n");
            }
            {

                sdb();
            }
        }
        else if (strncmp("ldb", comando, 6) == 0)
        {

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

            ldb(input);
            fclose(input);
        }
        else if (strncmp("svdb", comando, 4) == 0)
        {
            if (CONTROL == 0)
            {
                printf("PRIMERO DEBE CREAR O CARGAR LA BASE DE DATOS\n");
            }
            else
            {
                FILE *output;

                output = fopen(ptrBasesDatos->nombre, "w");
                if (output == NULL)
                {
                    perror("Error: NO SE ENCONTRO EL ARCHIVO ESPECIFICADO");
                }
                else
                {

                    svdb(output);
                    fclose(output);
                }
            }
        }
        else if (strncmp("radb", comando, 4) == 0)
        {
            if (CONTROL == 0)
            {
                printf("PRIMERO DEBE CREAR O CARGAR LA BASE DE DATOS\n");
            }
            else
            {
                radb();
            }
        }
        else if (strncmp("rsdb", comando, 4) == 0)
        {
            if (CONTROL == 0)
            {
                printf("PRIMERO DEBE CREAR O CARGAR LA BASE DE DATOS\n");
            }
            else
            {
                rsdb();
            }
        }
        else if (strncmp("rr", comando, 2) == 0)
        {
            if (CONTROL == 0)
            {
                printf("PRIMERO DEBE CREAR O CARGAR LA BASE DE DATOS\n");
            }
            else
            {
                int cedula = 0;
                fscanf(stdin, "%d", &cedula);
                rr(cedula);
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
                svdb(output);
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
void save(BD *ptrBD)
{
    basesDatos[contBD]=ptrBD;
}
void mdb(char *nombreBD, int cantregistros)
{

    ptrBasesDatos = (BD(*))malloc(sizeof(BD));
    ptrEstudiantes = (estudiante(*))malloc(cantregistros * sizeof(estudiante));
    strcpy(ptrBasesDatos->nombre, nombreBD);
    ptrBasesDatos->numRegistros = cantregistros;
    ptrBasesDatos->regActuales = 0;
    save(ptrBasesDatos);
    contBD++;
    printf("\nLa base de datos actual es: %s\n", ptrBasesDatos->nombre);
    printf("num de registros de %s es: %d\n", ptrBasesDatos->nombre, ptrBasesDatos->numRegistros);
}
void mreg(int ced, char *nomEstudiante, int sem)
{
    if (ptrBasesDatos->regActuales == ptrBasesDatos->numRegistros)
    {
        printf("YA ALCANZO EL MAXIMO DE REGISTROS POSIBLES\n");
    }
    else
    {

        strcpy(ptrEstudiantes[ptrBasesDatos->regActuales].nombre, nomEstudiante);
        ptrEstudiantes[ptrBasesDatos->regActuales].cedula = ced;
        ptrEstudiantes[ptrBasesDatos->regActuales].semestre = sem;
        ptrBasesDatos->regActuales++;
        printf("\n---NUEVO REGISTRO CREADO---\n");
    }
}
void ldb(FILE *input)
{

    int totregistros;
    char nombreDB[30];
    char nomEstudiante[30];
    int cedula = 0;
    int semestre = 0;

    fscanf(input, "%s", nombreDB);

    fscanf(input, "%d", &totregistros);

    mdb(nombreDB, totregistros);

    for (int i = 0; i < totregistros; i++)
    {
        fscanf(input, "%d %s %d", &cedula, nomEstudiante, &semestre);
        if (cedula != 0 && nomEstudiante != NULL && semestre != 0)
        {
            mreg(cedula, nomEstudiante, semestre);
        }
    }
}
void svdb(FILE *output)
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
void radb()
{
    printf("| Cedula | | Nombre | Semestre |\n\n");
    for (int i = 0; i < ptrBasesDatos->regActuales; i++)
    {
        printf("| %d | %s | %d |\n", ptrEstudiantes[i].cedula, ptrEstudiantes[i].nombre, ptrEstudiantes[i].semestre);

        printf("\n");
    }
    printf("\n");
}
void rsdb()
{
    printf("La cantidad de registros actualmente es de: %d\n", ptrBasesDatos->regActuales);
}
void rr(int cedula)
{
    for (int i = 0; i < ptrBasesDatos->regActuales; i++)
    {
        if (ptrEstudiantes[i].cedula == cedula)
        {
            printf("| %d | %s | %d |\n", ptrEstudiantes[i].cedula, ptrEstudiantes[i].nombre, ptrEstudiantes[i].semestre);
            break;
        }
    }
}
void lsdbs(){

    /*for(int i=0;i<contBD;i++){
        printf("%s",basesDatos[i]->nombre);
    }*/
    printf("%s\n",basesDatos[0]->nombre);
    printf("%s\n",basesDatos[1]->nombre);
}
