#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void bubbleSort(int);
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

   ptrlinea = (lineaVar(*))malloc((cantidad + 1) * sizeof(lineaVar));

   fclose(input);

   input = fopen(argv[1], "r");
   for (int i = 0; i < cantidad; i++)
   {
      fscanf(input, "%s %d", claveTemp, &valorTemp);
      strcpy(ptrlinea[i].clave, claveTemp);
      ptrlinea[i].valor = valorTemp;
   }

   bubbleSort(cantidad);

   output = fopen(argv[2], "w");
   for (int i = 0; i < cantidad; i++)
   {

      if (ptrlinea[i].valor > -1001 && ptrlinea[i].valor < 1001)
      {

         fprintf(output, "%s %d", ptrlinea[i].clave, ptrlinea[i].valor);
         fprintf(output, "\n");
      }
   }
   printf("PROCESO 1 LISTO\n");
   fclose(input);
   fclose(output);
   return 0;
}
void bubbleSort(int cantidad)
{

   lineaVar temp;
   int i, j;

   bool swapped = false;

   // loop through all numbers
   for (i = 0; i < cantidad; i++)
   {
      swapped = false;

      // loop through numbers falling ahead
      for (j = 0; j < cantidad - (i + 1); j++)
      {

         if (ptrlinea[j].valor < ptrlinea[j + 1].valor)
         {
            temp = ptrlinea[j];
            ptrlinea[j] = ptrlinea[j + 1];
            ptrlinea[j + 1] = temp;

            swapped = true;
         }
      }

      if (!swapped)
      {
         break;
      }
   }
}
