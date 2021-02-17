#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char FILE_TO_READ[] = "datos_lectura.txt";

int main()
{

    int num_materias = 0, won = 0, lost = 0;
    double promedio = 0, promedio_ponderado = 0;

    char linea;
    char *linea1;

    //char materia[30];
    //char nota[3];
    //char creditos[1];
    char almacenador[40];
    double nota=0.0;
    double creditos=0.0;
    int tot_creditos=0;
    int counter = 1;
    int counter2=1;
    FILE *read, *write;

    read = fopen(FILE_TO_READ, "r");
    write = fopen("informe.txt", "r+");
    if (read == NULL)
    {
        printf("Error al abrir el archivo: %s", FILE_TO_READ);
    }
    while (1)
    {
        if (feof(read))
            break;
        linea = fgetc(read);

        if (linea == '\n')
        {
            if (counter == 3)
            {
                if (feof(read))
                    break;
                num_materias++;
                fputc(' ', write);
                fputc(' ', write);
            }
            else
            {
                fputc('-', write);
                fputc('-', write);
            }
            if (feof(read))
                break;
            linea = fgetc(read);

            if (counter == 3)
            {
                fputc('\n', write);
                counter = 0;
                if (feof(read))
                    break;
            }
            counter++;
        }

        fputc(linea, write);
    }
    
    read = fopen(FILE_TO_READ, "r");
    int i=0;
    while (i<num_materias)
    {
        

        if (feof(read))
            break;
        
        fgets(almacenador,40,read);

        if(counter2==1){
            printf("Materia %s",almacenador);
            
        }
        if(counter2==2){
            printf("nota %s",almacenador);
            if((atof(almacenador)-3.0)<0){
                lost+=1;
            }else{
                won+=1;
            }
            nota = atof(almacenador);
        }
        if(counter2==3){
            printf("creditos %s",almacenador);
            creditos=atof(almacenador);
            tot_creditos+=(int)creditos;
            counter2=0;
            i++;
            promedio+=nota*creditos;
            printf("Promedio %3.1lf\n",promedio);
        }
        
        
        counter2++;
        

        
       
        
        if(feof(read)) break;
        
        
    }
    printf("Ganadas: %d\nPerdidas: %d\n", won, lost);
    printf("Total de creditos: %d\n",tot_creditos);
    printf("Promedio ponderado: %3.4lf",promedio/tot_creditos);
    fclose(read);
    fclose(write);
}
    