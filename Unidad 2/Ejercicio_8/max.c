#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <syscall.h>
int main(int argc, char const *argv[])
{
    int max  = atoi(argv[1]);
    for (int i = 1; i < argc; i++)
    {
        if(max<atoi(argv[i])){
            max = atoi(argv[i]);
        }
    }
    printf("Maximo: %d\n", max );
    return 0;
}
