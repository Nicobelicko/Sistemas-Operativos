#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include <ctype.h>

typedef struct linea
{
   int edad;
   char nombre[20];
   char ocupacion[20];

} lineaVar;
typedef struct parametro
{
   char output_file[20];
   int cantidad;
} param;

lineaVar *ptrlinea;

void *reves(void *parametros)
{
   param *p = (param *)parametros;
   FILE *output;
   lineaVar *vecReves;
   vecReves = (lineaVar(*))malloc((p->cantidad + 1) * sizeof(lineaVar));
   for (int i = 0; i < p->cantidad; i++)
   {
      vecReves[i]=ptrlinea[i];
      vecReves[i].ocupacion[0]=toupper( vecReves[i].ocupacion[0]);
   }
   

   output = fopen(p->output_file, "w");

   for (int i = p->cantidad-1; i >= 0; i--)
   {

      fprintf(output, "%s %d %s", vecReves[i].nombre, vecReves[i].edad, vecReves[i].ocupacion);
      fprintf(output, "\n");
   }

   fclose(output);
   free(vecReves);

   return NULL;
}

void *alfabetico(void *parametros)
{
   param *p = (param *)parametros;
   FILE *output;
   output = fopen(p->output_file, "w");
   lineaVar *vecAlfabetico;
   vecAlfabetico = (lineaVar(*))malloc((p->cantidad + 1) * sizeof(lineaVar));
   for (int i = 0; i < p->cantidad; i++)
   {
      vecAlfabetico[i]=ptrlinea[i];
      vecAlfabetico[i].ocupacion[0]=toupper( vecAlfabetico[i].ocupacion[0]);
   }
   lineaVar temp;
   int i, j;
   bool swapped = false;

   

   for (i = 0; i < p->cantidad; i++)
   {
      swapped = false;

      for (j = 0; j < p->cantidad - (i + 1); j++)
      {
         if (strcmp(vecAlfabetico[j].ocupacion, vecAlfabetico[j + 1].ocupacion) > 0)
         {
            temp = vecAlfabetico[j];
            vecAlfabetico[j] = vecAlfabetico[j + 1];
            vecAlfabetico[j + 1] = temp;

            swapped = true;
         }
      }
      if (!swapped)
      {
         break;
      }
   }
   for (int i = 0; i < p->cantidad; i++)
   {
      fprintf(output,"%s %d %s",vecAlfabetico[i].nombre,vecAlfabetico[i].edad,vecAlfabetico[i].ocupacion);
      fprintf(output,"\n");
   }
   

   fclose(output);
   free(vecAlfabetico);

   return NULL;
}

int main(int argc, char const *argv[])
{

   FILE *input;

   char nombreTemp[20];
   char ocupacionTemp[20];
   char aux[20];
   int edadTemp = 0;
   int cantidad = 0;
   input = fopen(argv[1], "r");

   while (1)
   {
      if (feof(input))
         break;
      else
      {
         fscanf(input, "%s %s %s", aux, aux, aux);

         cantidad++;
      }
   }

   ptrlinea = (lineaVar(*))malloc((cantidad + 1) * sizeof(lineaVar));

   fclose(input);

   input = fopen(argv[1], "r");

   for (int i = 0; i < cantidad; i++)
   {
      fscanf(input, "%s %d %s", nombreTemp, &edadTemp, ocupacionTemp);
      ocupacionTemp[0]=toupper(ocupacionTemp[0]);
      strcpy(ptrlinea[i].nombre, nombreTemp);
      strcpy(ptrlinea[i].ocupacion, ocupacionTemp);
      ptrlinea[i].edad = edadTemp;
      printf("%s %d %s\n", ptrlinea[i].nombre, ptrlinea[i].edad, ptrlinea[i].ocupacion);
   }
   printf("\n");
   fclose(input);

   pthread_t id_hilo1;

   param hilo1_param;

   strcpy(hilo1_param.output_file, argv[2]);
   hilo1_param.cantidad = cantidad;
   pthread_create(&id_hilo1, NULL, &reves, &hilo1_param);

   

   pthread_t id_hilo2;
   param hilo2_param;

   strcpy(hilo2_param.output_file, argv[3]);
   hilo2_param.cantidad = cantidad;
   pthread_create(&id_hilo2, NULL, &alfabetico, &hilo2_param);

   pthread_join(id_hilo1, NULL);

   pthread_join(id_hilo2, NULL);

   input = fopen(argv[2], "r");
   printf("RESULTADO HILO 1\n\n");

   for (int i = 0; i < cantidad; i++)
   {
      fscanf(input, "%s %d %s", nombreTemp, &edadTemp, ocupacionTemp);
      
      printf("%s %d %s", nombreTemp, edadTemp, ocupacionTemp);
      printf("\n");
   }
   fclose(input);
   printf("\n");
   input = fopen(argv[3], "r");
   printf("RESULTADO HILO 2\n\n");

   for (int i = 0; i < cantidad; i++)
   {
      fscanf(input, "%s %d %s", nombreTemp, &edadTemp, ocupacionTemp);
      
      printf("%s %d %s", nombreTemp, edadTemp, ocupacionTemp);
      printf("\n");
   }
   fclose(input);
   free(ptrlinea);
   return 0;
}
