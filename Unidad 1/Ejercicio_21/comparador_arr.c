#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
uint8_t arrayCommon(int32_t* arr1, int32_t arr1Size,int32_t* arr2, int32_t arr2Size, int32_t* arrRes, int32_t arrResSize);
int contador=0;
int main(void)
{
    int size1=0,size2=0,sizeR=0;
    int mayor=0,menor=0;

    printf("Ingrese el tamaño del primer arreglo: ");
    scanf("%d",&size1);
    int arreglo1 [size1];
    //arr1 = (int (*)[size1])malloc(sizeof (char [size1]));
    for(int i=0;i<size1;i++){
        printf("Ingrese un numero para la pos %d del arreglo: ",i+1);
        scanf("%d",&arreglo1[i]);
    }
    
    

    printf("\nIngrese el tamaño del segundo arreglo: ");
    scanf("%d",&size2);
    printf("\n");
    int arreglo2 [size2];
    for(int j=0;j<size2;j++){
        printf("Ingrese un numero para la pos %d del arreglo: ",j+1);
        scanf("%d",&arreglo2[j]);
    }
    if(size1>=size2){
        
        mayor = size1;
        menor = size2;
    }else{
        mayor = size2;
        menor = size1;
    }
    
    sizeR=mayor;
    
    int arrR[sizeR];
    
    
    arrayCommon(arreglo1,size1,arreglo2,size2,arrR,sizeR);
    printf("\nHay %d elementos comunes entre los arreglos\n",contador);
    printf("\nLos numeros en comun entre los arreglos son:\n");
    for(int i=contador-1;i>=0;i--){
        
        printf("|%d|\n",arrR[i]);
    }
    
return 0;
    
}
uint8_t arrayCommon(int32_t* arr1, int32_t arr1Size,int32_t* arr2, int32_t arr2Size, int32_t* arrRes, int32_t arrResSize){
   
    int mayor=0,menor=0;
    int numComun=0;
    short Repetido;
    int32_t* arrMayor;
    int32_t* arrMenor;
    if(arr1Size>=arr2Size){
        
        mayor = arr1Size;
        menor = arr2Size;
        arrMayor=arr1;
        arrMenor=arr2;
    }else{
        mayor = arr2Size;
        menor = arr1Size;
        arrMayor=arr2;
        arrMenor=arr1;
    }
    for(int i=0;i<mayor;i++){
        
        
        for(int j=0;j<menor;j++){
            
            
            if(arrMayor[i]==arrMenor[j]){
                
                numComun=arrMenor[j];
                
                
                Repetido=0;
                for (int i = 0; i < arrResSize; i++)
                {
                    if(arrRes[i]==numComun){
                        
                        Repetido=1;
                    }
                }
                if(Repetido==0){
                    contador++;
                    for (int i = arrResSize-1; i > 0; i--)
                    {
                        arrRes[i]=arrRes[i-1];
                    }
                    arrRes[0]=numComun;
                    
                }
                 
                
            }
            
        }
        
    }
    
    return contador;
}