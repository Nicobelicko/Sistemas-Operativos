#include <stdio.h>

#define NUMELE 100

int array[NUMELE];

int main(void) {
   int i;
   int promedio;

   for(i= 0;i < NUMELE;i++){
      array[i] = 1;
   }

   printf("array = {");
   for(i= 0;i < NUMELE-1;i++){
      printf("array[%d]:%d,",i,array[i]);
   }
   printf("array[%d]:%d}\n",i,array[i]);

   promedio = 0;
   for(i= 0;i < NUMELE;i++){
      promedio += array[i];
   }
   printf("Suma total= %d, Promedio = %d\n",promedio, promedio/NUMELE);

   return 0;
}
