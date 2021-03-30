#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <syscall.h>
#include <sys/wait.h>
int main(int argc, char *argv[])
{

    __pid_t pid_hijo;
    int minimo, maximo, promedio;

    for (int i = 0; i < 3; i++)
    {
        pid_hijo = fork();
        if (pid_hijo == 0)
        {
            if (i == 0) // minimo
            {
                execvp("./min", argv);
            }
            else if (i == 1)
            { //maximo

                execvp("./max", argv);
            }
            else if (i == 2)
            { // promedio

                execvp("./prom", argv);
            }
        }
        else
        {
            wait(NULL);
        }
    }

    return 0;
}
