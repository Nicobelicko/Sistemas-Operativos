#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <syscall.h>
int main(int argc, char const *argv[])
{
    int prom = 0;
    for (int i = 1; i < argc; i++)
    {
        prom += atoi(argv[i]);
    }
    printf("Promedio: %d\n", prom / (argc - 1));
    return 0;
}
