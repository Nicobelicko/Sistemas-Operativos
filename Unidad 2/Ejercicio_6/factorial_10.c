#include <syscall.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
void fact(pid_t pid);

int main(int argc, char const *argv[])
{
      
    
    pid_t pid_hijo1, pid_hijo2,pid_hijo3;
    int status;
    
    if ((pid_hijo1=fork()) == 0)
    {
        printf("HIJO 1\n");
        fact(getpid());
    }
    else
    {
        
        if ((pid_hijo2=fork()) == 0)
        {
            printf("HIJO 2\n");
            fact(getpid());
        }
        else
        {
            if((pid_hijo3=fork())==0){
                printf("HIJO 3\n");
                fact(getpid());
            }else{
            wait(&status);
            wait(&status);
            wait(&status);
            }
        }
    }

    return 0;
}
void fact(pid_t pid)
{
    
    
    int fact = 1;
    for (int i = 1; i <= 10; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            fact *= j;
        }
        printf("Proc: %d, fact(%d): %d\n",pid, i, fact);
        fact = 1;
    }
    

}
