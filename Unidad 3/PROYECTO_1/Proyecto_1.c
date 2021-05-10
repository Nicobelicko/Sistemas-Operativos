#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main(int argc, char const *argv[])
{
    
    int p1[2];
    int p2[2];
    int tam=0;
    
    while (1)
    {
    char lectura[80];
    if(pipe(p1) == -1){return 1;}
    if(pipe(p2) == -1){return 1;}
    scanf("%s", lectura);
    tam = strlen(lectura);
    int pid = fork();

    if(pid == -1){return 2;}

    if(pid == 0){
        close(p2[1]);
        close(p1[0]);

        if(read(p2[0],lectura,tam) == -1){return 3;}
        printf("Mensaje en el proceso hijo: %s\n",lectura);

        for(int i = 0; i < tam; i++)
        {
            lectura[i] = toupper(lectura[i]);
        }
        if(write(p1[1],lectura,tam) == -1){return 4;}

        close(p2[0]);
        close(p1[1]);
    }else{
        close(p2[0]);
        close(p1[1]);

        
        for(int i = 0;i < tam; i++)
        {
            lectura[i] = tolower(lectura[i]);
        }
        
        if(write(p2[1],lectura,tam) == -1){return 5;}

        if(read(p1[0],lectura,tam) == -1){return 6;}
        printf("Mensaje en el proceso padre: %s\n",lectura);

        close(p2[1]);
        close(p1[0]);
        wait(NULL);
        
    }
    }

    return 0;
}