#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>
#define PERMS 0644

void* envio(void*);
void* recibo(void*);

struct msg {
   long mtype;
   char mtext[200];
};

void *envio(void *msVar)
{
struct msg buf;
int len;
buf.mtype = 1;
int *msqid = (int*)msVar;

 while(fgets(buf.mtext, sizeof buf.mtext, stdin) != NULL) 
 {
      len = strlen(buf.mtext);
      if (buf.mtext[len-1] == '\n') buf.mtext[len-1] = '\0';
      if (msgsnd(*msqid, &buf, len+1, 0) == -1) 
      perror("Error en el mensaje de 1");
   }

   strcpy(buf.mtext, "end"); 
   len = strlen(buf.mtext);
   if (msgsnd(*msqid, &buf, len+1, 0) == -1) 
   perror("msgsnd2");

   return NULL;
   
}

void *recibo(void *msVar)
{

struct msg buf;
int toend;
int *msqid = (int*)msVar;

   for(;;) { 
      if (msgrcv(*msqid, &buf, sizeof(buf.mtext), 0, 0) == -1) {
         perror("msgrcv");
         exit(1);
      }
      printf("Usuario 2: \"%s\"\n", buf.mtext);
      toend = strcmp(buf.mtext,"end");
      if (toend == 0)
      break;
   }
   system("rm msgq.txt");
   
   return NULL;
}


int main ()
{   
    pthread_t id_hilo1;
    pthread_t id_hilo2;
    int msqid, msqid2;
    key_t key1, key2;
    int *msqidP1, *msqidP2;

    system("touch msgq.txt"); 
    if ((key1 = ftok("msgq.txt", 'B')) == -1)
   {
      perror("ftok");
      exit(1);
   }
    if ((msqid = msgget(key1, PERMS | IPC_CREAT)) == -1)
   {
      perror("msgget");
      exit(1);
   }
     if ((key2 = ftok("msgq2.txt", 'B')) == -1)
   {
      perror("ftok");
      exit(1);
   }
    if ((msqid2 = msgget(key2, PERMS | IPC_CREAT)) == -1)
   {
      perror("msgget");
        exit(1);
   }
   msqidP1 = &msqid;
   msqidP2 = &msqid2;
    pthread_create(&id_hilo1, NULL, &envio , msqidP1);
    pthread_create(&id_hilo2, NULL, &recibo, msqidP2);

    pthread_join(id_hilo1, NULL);
    pthread_join(id_hilo2, NULL);
}