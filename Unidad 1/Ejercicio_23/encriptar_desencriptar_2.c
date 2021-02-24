#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


int main(int argc, char *argv[])
{
    
    char *opcion;
    
    FILE *inputFile, *outputFile;
    

    inputFile = fopen(argv[1], "r");
    if (inputFile == NULL)
    {
        perror("Error: ");
        return EXIT_FAILURE;
    }
    outputFile = fopen(argv[2], "w");
    if (inputFile == NULL)
    {
        perror("Error: ");
        return EXIT_FAILURE;
    }

    opcion = argv[3];

    if ((strncmp("NOT",opcion,3)==0))
    {  
        
        int  caracter;
        while (1)
        {
            
            
            caracter=fgetc(inputFile);
            if(caracter==EOF){break;}
            caracter=~caracter;
            fputc(caracter,outputFile);
            
        }
        
    }
    else if((strncmp("XOR",opcion,3)==0)){
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
