#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char FILE_TO_READ[] = "datos_lectura.txt";

int main()
{

    int  won = 0, lost = 0;
    

    char linea;
    char *linea1;

    //char materia[30];
    //char nota[3];
    //char creditos[1];
    struct valores_materia
    {
        double nota;
        double creditos;
    }vmat;
    struct valores_semestre
    {
        int tot_creditos;
        int num_materias;
        double promedio;
        double promedio_ponderado;
    }vsem;
    
    vmat.creditos=0.0;
    vmat.nota=0.0;

    vsem.tot_creditos=0;
    vsem.num_materias=0;
    vsem.promedio=0.0;
    vsem.promedio_ponderado=0.0;
    char almacenador[40];
    
    
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
                vsem.num_materias++;
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
    while (i<vsem.num_materias)
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
            vmat.nota = atof(almacenador);
        }
        if(counter2==3){
            printf("creditos %s",almacenador);
            vmat.creditos=atof(almacenador);
            vsem.tot_creditos+=(int)vmat.creditos;
            counter2=0;
            i++;
            vsem.promedio+=vmat.nota*vmat.creditos;
            printf("Promedio %3.1lf\n",vsem.promedio);
        }
        
        
        counter2++;
        

        
       
        
        if(feof(read)) break;
        
        
    }
    fputc('\n',write);
    
    fprintf(write,"%s %d\n%s %d\n%s %d\n%s %3.1lf\n","Total de materias:",vsem.num_materias,"Materias Ganadas:",won,"Materias perdidas:",lost,"Promedio ponderado:",(double)(vsem.promedio/vsem.tot_creditos));
    
    
    fclose(read);
    fclose(write);
}
    