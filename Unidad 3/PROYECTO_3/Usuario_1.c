#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/wait.h>

#define SIZE_SHM_1 250
#define SIZE_SHM_2 250

sem_t *sw1, *sw2, *sr1, *sr2;
int shm_a, shm_b;

void* writeMsg();
void* readMsg();

void createSem();
void closeSem();
void unlinkSem();

void createShm();
void closeShm();
void unlinkShm(char*);


int main(int argc, char const *argv[])
{

    pthread_t threadWrite, threadRead;
    createShm();
    createSem();
    
    pthread_create(&threadWrite,NULL,&writeMsg,NULL);
    pthread_create(&threadRead,NULL,&readMsg,NULL);

    pthread_join(threadWrite,NULL);
    pthread_join(threadRead,NULL);

    return 0;
}
void* writeMsg(){
    char buffer[SIZE_SHM_1];
    int len;
    char *pointer;
    void *ptrMmap;

    ptrMmap = mmap(NULL, SIZE_SHM_1, PROT_WRITE, MAP_SHARED, shm_a, 0);
        if(ptrMmap == MAP_FAILED){
            perror("ERROR mmap Usuario 1: ");
            exit(1);
        }
    pointer = (char*)ptrMmap;

    while(fgets(buffer, sizeof buffer, stdin) != NULL){
        
        len = strlen(buffer);
        if(buffer[len-1] == '\n') buffer[len-1] = '\0';

        if(sem_post(sw1) == -1){
            perror("Error post sw1 Usuario 1: ");
            exit(1);
        }

        memcpy(pointer, buffer, sizeof(buffer));
        
        if(sem_wait(sr2) == -1){
            perror("ERROR wait sr2 Usuario 1: ");
            exit(1);
        }
    }
    if(munmap(ptrMmap, SIZE_SHM_1) == -1){
            perror("unmapS1: ");
            exit(1);
        }
    closeSem();
    closeShm();
    unlinkSem();
    unlinkShm("SHM_A");
    return NULL;

}
void* readMsg(){
    
    char* pointer;
    void *ptrMmap = mmap(NULL, SIZE_SHM_2, PROT_READ, MAP_SHARED, shm_b, 0);
        if(ptrMmap == MAP_FAILED){
            perror("ERROR mmap shm_b Usuario 1: ");
            exit(1);
        }

    pointer = (char*)ptrMmap;
    for(;;)
    {
        
         if(sem_wait(sw2) == -1){
            perror("ERROR wait sw2 Usuario 1: ");
            exit(1);
        }

        
        fprintf(stdout, "Usuario 2: %s\n",pointer);

        

        if(sem_post(sr1) == -1){
            perror("ERROR post sr1 Usuario 1: ");
            exit(1);
        }
    }
    if(munmap(pointer, SIZE_SHM_2) == -1){
            perror("ERROR munmap read Usuario 1: ");
            exit(1);
        }
    
    return NULL;
}
void createSem(){
    mode_t perms = 0666;
    unsigned int value = 0;
    sw1 = sem_open("Sem_Write_1",O_CREAT, perms, value);
    if(sw1 == SEM_FAILED){
        perror("Error en la creacion/apertura de sw1 en Usuario 1: ");
        exit(1);
    }
    sr1 = sem_open("Sem_Read_1",O_CREAT, perms, value);
    if(sr1 == SEM_FAILED){
        perror("Error en la creacion/apertura de sr1 en Usuario 1: ");
        exit(1);
    }
    sw2 = sem_open("Sem_Write_2",value);
    if(sw2 == SEM_FAILED){
        perror("Error en la apertura de sw2 en Usuario 1: ");
        exit(1);
    }
    sr2 = sem_open("Sem_Read_2",value);
    if(sr2 == SEM_FAILED){
        perror("Error en la apertura de sr2 en Usuario 1: ");
        exit(1);
    }
    
}
void closeSem(){
    if(sem_close(sw1) == -1){
        perror("ERROR en close sw1 Usuario 1: ");
        exit(1);
    }
    if(sem_close(sr1) == -1){
        perror("ERROR en close sr1 Usuario 1: ");
        exit(1);
    }
    if(sem_close(sw2) == -1){
        perror("ERROR en close sw2 Usuario 1: ");
        exit(1);
    }
    if(sem_close(sr2) == -1){
        perror("ERROR en close sw1 Usuario 1: ");
        exit(1);
    }
    
}
void unlinkSem(){
    if(sem_unlink("Sem_Write_1") == -1){
        perror("Error unlink sw1 Usuario 1 ");
        exit(1);
    }
    if(sem_unlink("Sem_Read_1") == -1){
        perror("Error unlink sr1 Usuario 1 ");
        exit(1);
    }
    if(sem_unlink("Sem_Write_2") == -1){
        perror("Error unlink sw2 Usuario 1 ");
        exit(1);
    }
    if(sem_unlink("Sem_Read_2") == -1){
        perror("Error unlink sr2 Usuario 1 ");
        exit(1);
    }
    
}
void createShm(){
    shm_a = shm_open("SHM_A", O_CREAT | O_RDWR, 0600);
    if(shm_a == -1){
        perror("ERROR creando/abriendo shm_a Usuario 1: ");
        exit(1);
    }
    
    if(-1 == ftruncate(shm_a, SIZE_SHM_1 )){
        perror("ERROR ftruncate shm_a Usuario 1: ");
        exit(1);
    }

    shm_b = shm_open("SHM_B", O_RDONLY, 0600);
    if(shm_b == -1){
        perror("ERROR abriendo shm_b Usuario 1: ");
        exit(1);
    }
    
}
void closeShm(){
    if(close(shm_a == -1)){
        perror("ERROR close shm_a Usuario 1: ");
        exit(1);
    }
    if(close(shm_b == -1)){
        perror("ERROR close shm_b Usuario 1: ");
        exit(1);
    }
}
void unlinkShm(char* shm){
    if(shm_unlink(shm) == -1){
        perror("ERROR unlink shm_a Usuario 1: ");
        exit(1);
    }
    
    
}
