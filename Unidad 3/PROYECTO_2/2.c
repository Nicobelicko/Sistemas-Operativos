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

struct my_msgbuf {
   long mtype;
   char mtext[200];
};

void *envio(void *msqid)
{
struct my_msgbuf buf;
int len;
buf.mtype = 1;

printf("Usuario 1: ");
 while(fgets(buf.mtext, sizeof buf.mtext, stdin) != NULL) 
 {
      len = strlen(buf.mtext);
      if (buf.mtext[len-1] == '\n') buf.mtext[len-1] = '\0';
      if (msgsnd(msqid, &buf, len+1, 0) == -1) 
      perror("msgsnd1");
   }

   strcpy(buf.mtext, "end"); 
   len = strlen(buf.mtext);
   if (msgsnd(msqid, &buf, len+1, 0) == -1) 
   perror("msgsnd2");
   
   if (msgctl(msqid, IPC_RMID, NULL) == -1) {
      perror("msgctl");
      exit(1);
   }
}

void *recibo(void *msqid)
{

struct my_msgbuf buf;
int toend;

   for(;;) { 
      if (msgrcv(msqid, &buf, sizeof(buf.mtext), 0, 0) == -1) {
         perror("msgrcv");
         exit(1);
      }
      printf("Usuario 2: \"%s\"\n", buf.mtext);
      toend = strcmp(buf.mtext,"end");
      if (toend == 0)
      break;
   }
   system("rm msgq2.txt");
}


int main ()
{   
    pthread_t id_hilo1;
    pthread_t id_hilo2;
    int msqid, msqid2;
    key_t key1, key2;

    system("touch msgq2.txt"); 
    if ((key2 = ftok("msgq2.txt", 'B')) == -1)
   {
      perror("ftok");
      exit(1);
   }
    if ((msqid = msgget(key2, PERMS | IPC_CREAT)) == -1)
   {
      perror("msgget");
      exit(1);
   }
     if ((key1 = ftok("msgq.txt", 'B')) == -1)
   {
      perror("ftok");
      exit(1);
   }
    if ((msqid2 = msgget(key1, PERMS | IPC_CREAT)) == -1)
   {
      perror("msgget");
        exit(1);
   }
    pthread_create(&id_hilo1, NULL, &envio , msqid);
    pthread_create(&id_hilo2, NULL, &recibo, msqid2);

    pthread_join(id_hilo1, NULL);
    pthread_join(id_hilo2, NULL);
}