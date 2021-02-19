#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
uint8_t arrayCommon(int32_t* arr1, int32_t arr1Size,int32_t* arr2, int32_t arr2Size, int32_t* arrRes, int32_t arrResSize);

int main(void)
{
    int size1=0,size2=0;

    printf("Ingrese el tamaño del primer arreglo: ");
    scanf("%d",&size1);
    int (*arr1) [size1];
    for(int i=0;i<size1;i++){
        printf("Ingrese un numero para la pos %d del arreglo \n",i+1);
        scanf("%d",arr1[i]);
    }
    
    printf("Ingrese el tamaño del segubdo arreglo: ");
    scanf("%d",&size2);
    int (*arr2) [size2];
    for(int i=0;i<size2;i++){
        printf("Ingrese un numero para la pos %d del arreglo \n",i+1);
        scanf("%d",arr2[i]);
    }

    
}