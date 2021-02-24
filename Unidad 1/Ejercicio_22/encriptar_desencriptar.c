#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


int main()
{
    char nameInputFIle[30];
    char nameOutputFIle[30];
    int opcion=0;
    FILE *inputFile, *outputFile;
    
    uint8_t (*NOT)(uint8_t) = NULL;
    uint8_t (*XOR)(uint8_t) = NULL;
    printf("Ingrese el nombre del archivo de entrada: \n");
    scanf("%s", nameInputFIle);
    printf("Ingrese el nombre del archivo de salida: ");
    scanf("%s", nameOutputFIle);

    inputFile = fopen(nameInputFIle, "r");
    if (inputFile == NULL)
    {
        perror("Error: ");
        return EXIT_FAILURE;
    }
    outputFile = fopen(nameOutputFIle, "w");
    if (inputFile == NULL)
    {
        perror("Error: ");
        return EXIT_FAILURE;
    }

    printf("Elija una opcion:\n1.Usar NOT\n2.Usar XOR\n");
    scanf("%d",&opcion);
    
    if (opcion == 1)
    {  
        printf("HOla");
        int  caracter;
        while (1)
        {
            
            
            caracter=fgetc(inputFile);
            if(caracter==EOF){break;}
            caracter=~caracter;
            fputc(caracter,outputFile);
            
        }
        
    }
    else if(opcion == 2){
        int  caracter;
        while (1)
        {
            
            
            caracter=fgetc(inputFile);
            if(caracter==EOF){break;}
            caracter=caracter^0xFF;
            fputc(caracter,outputFile);
        }
    }else{
        printf("Seleccione un valor valido");
    }

    fclose(inputFile);
    fclose(outputFile);
    return 0;
}
