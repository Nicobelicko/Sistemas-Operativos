#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[])
{
    int arr[argc-1];
    
    for (int i = 1; i < argc; i++)
    {
        arr[i-1]=atoi(argv[i]);
    }
    int prom = 0;
    int min = arr[0];
    int max = arr[0];
    for (int i = 0; i < argc-1; i++)
    {
        prom += arr[i];
        if (min > arr[i])
        {
            min = arr[i];
        }
        if (max < arr[i])
        {
            max = arr[i];
        }
    }
    printf("El promedio es: %d\n", prom / (argc-1));
    printf("El minimo entero es: %d\n", min);
    printf("El maximo entero es: %d\n", max);
} 