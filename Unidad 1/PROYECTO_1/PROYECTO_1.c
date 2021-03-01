#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *obtenerlinea(void);
void mkdb(char *nombre, int registros);
void mkreg(int ced, char *nomEstudiante, int sem);
void loaddb(FILE *input);
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

int totBasesDatos = 0;
int regActual = 0;
int mkdbCONTROL = 0;
int loaddbCONTROL = 0;
int main()
{

    //int contador = 0;
    //char *linea;
    //char *cantRegistros;
    //int len = 0;
    char comando[100];

    //linea = obtenerlinea();
    //len = strlen(linea);

    do
    {
        printf("Ingrese el comando\n");
        fscanf(stdin, "%s", comando);
        if (strncmp("mkdb", comando, 4) == 0)
        {
            mkdbCONTROL = 1;
            char nombreDB[30];
            int cant_registros;
            fscanf(stdin, "%s", nombreDB);
            //getc(stdin);
            fscanf(stdin, "%d", &cant_registros);
            //getc(stdin);
            mkdb(nombreDB, cant_registros);
            /*Pedaso de funcion getline o obtenerLInea
        for (int i = 5; i < len-1; i++)
        {
            if (linea[i] == ' ')
            {break;}
            
            contador++;
        }
        char nombreDB[contador];
        getc(stdin);
        fscanf(stdin,"%s",nombreDB);
        printf("%s",nombreDB);
        
        printf("%d\n",contador);
        int j=0;
        for(int i=0;i<contador;i++){
            nombreDB[j]=linea[i+5];
            j++;
        }
        for(int i=len-1;i>=0;i--){
            printf("%d: %c\n",i+1,linea[i]);
        }
        //printf("Nombre Base de datos: %s\n",nombreDB);
        //printf("%s",cantRegistros);
        //mkdb(&nombreDB,)*/
        }
        else if (strncmp("mkreg", comando, 5) == 0)
        {
            if (mkdbCONTROL == 0)
            {
                printf("PRIMERO DEBE CREAR O CARGAR LA BASE DE DATOS\n");
                main();
            }
            char nomEstudiante[30];
            int ced = 0;
            int sem = 0;
            fscanf(stdin, "%d", &ced);
            getc(stdin);
            fscanf(stdin, "%s", nomEstudiante);

            fscanf(stdin, "%d", &sem);

            mkreg(ced, nomEstudiante, sem);
        }
        else if (strncmp("loaddb", comando, 6) == 0)
        {
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
            //printf("llega hasta aqui");
            loaddb(input);
            fclose(input);
        }
    } while (1);
    free(ptrEstudiantes);
    free(ptrBasesDatos);
    return 0;
}
void mkdb(char *nombreBD, int cantregistros)
{

    ptrBasesDatos = (BD(*))malloc(totBasesDatos * sizeof(BD));
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
        printf("YA ALCANZO EL MAXIMO DE REGISTROS POSIBLES");
    }
    else
    {  
        
        strcpy(ptrEstudiantes[regActual].nombre, nomEstudiante);
        ptrEstudiantes[regActual].cedula = ced;
        ptrEstudiantes[regActual].semestre = sem;
        regActual++;
        printf("\n---NUEVO REGISTRO CREADO---\n");
        //printf("%d\n", regActual);

        for (int i = 0; i < regActual; i++)
        {
            printf("Cedula estudiante %d: %d\n", i + 1, ptrEstudiantes[i].cedula);
            printf("Nombre estudiante %d: %s\n", i + 1, ptrEstudiantes[i].nombre);
            printf("Semestre estudiante %d: %d\n", i + 1, ptrEstudiantes[i].semestre);
            printf("\n");
        }
        printf("\n");
    }
}
void loaddb(FILE *input)
{
    //printf("entra a loaddb");

    char caracter;
    int totregistros;
    char nombreDB[30];
    char nomEstudiante[30];
    int cedula = 0;
    int semestre = 0;

    /*while(1){
        caracter=fgetc(input);
        if(caracter=='\n'){break;}
       
       strcat(nombreDB,&caracter);
       
    }*/
    fscanf(input, "%s", nombreDB);

    fscanf(input, "%d", &totregistros);

    mkdb(nombreDB,totregistros);
    
    

    for (int i = 0; i < totregistros; i++)
    {
        fscanf(input, "%d %s %d", &cedula, nomEstudiante, &semestre);
        mkreg(cedula,nomEstudiante,semestre);
        //printf("Cedula: %d\n Nombre: %s\n Semestre: %d\n",cedula,nomEstudiante,semestre);
    }
}
char *obtenerlinea(void)
{
    char *line = malloc(100), *linep = line;
    size_t lenmax = 100, len = lenmax;
    int c;

    if (line == NULL)
        return NULL;

    for (;;)
    {
        c = fgetc(stdin);
        if (c == EOF)
            break;

        if (--len == 0)
        {
            len = lenmax;
            char *linen = realloc(linep, lenmax *= 2);

            if (linen == NULL)
            {
                free(linep);
                return NULL;
            }
            line = linen + (line - linep);
            linep = linen;
        }

        if ((*line++ = c) == '\n')
            break;
    }
    *line = '\0';
    return linep;
}
