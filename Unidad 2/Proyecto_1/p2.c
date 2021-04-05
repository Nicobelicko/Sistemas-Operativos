#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct linea
{
    int valor;
    char clave[20];
} lineaVar;

lineaVar *ptrlinea;
int main(int argc, char const *argv[])
{

    FILE *input, *output;

    char claveTemp[20];
    char aux[20];
    int valorTemp = 0;
    int cantidad = 0;
    input = fopen(argv[1], "r");

    while (1)
    {
        if (feof(input))
            break;
        else
        {
            fscanf(input, "%s", aux);
            fscanf(input, "%s", aux);
            
            cantidad++;
        }
    }
    

    ptrlinea = (lineaVar(*))malloc(sizeof(lineaVar) * cantidad);

    fclose(input);
    input = fopen(argv[1], "r");
    for (int i = 0; i < cantidad; i++)
    {
        fscanf(input, "%s %d", claveTemp, &valorTemp);
        strcpy(ptrlinea[i].clave, claveTemp);
        ptrlinea[i].valor = valorTemp;
    }

    output = fopen(argv[3], "w");
    for (int i = cantidad - 1; i >= 0; i--)
    {
        if (ptrlinea[i].valor > -1001 && ptrlinea[i].valor < 1001)
        {

            fprintf(output, "%s %d", ptrlinea[i].clave, ptrlinea[i].valor);
            fprintf(output, "\n");
        }
    }
    printf("PROCESO 2 LISTO\n");
    fclose(input);
    fclose(output);
    return 0;
}
