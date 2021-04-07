#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <syscall.h>
#include <sys/wait.h>
int main(int argc, char *argv[])
{

    __pid_t pid_hijo;
    

    for (int i = 0; i < 2; i++)
    {
        pid_hijo = fork();
        if (pid_hijo == 0)
        {
            if (i == 0) 
            {
                execvp("./p1", argv);
            }
            else if (i == 1)
            { 

                execvp("./p2", argv);
            }
           
        }
        else
        {
            wait(NULL);
        }
    }

    return 0;
}
