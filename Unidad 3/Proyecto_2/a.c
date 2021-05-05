#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <mqueue.h>

#define ARR_SIZE 8192
int main()
{
    mqd_t mqWR;
    mqd_t mqRW;
	char arr1[80], arr2[ARR_SIZE];
	while (1)
	{
        mqWR = mq_open("/WriteReadQueue",O_WRONLY | O_CREAT,0666,NULL);
        
        if(mqWR == -1){
            return 1;
        }
        
		fgets(arr1, 80, stdin);
        mq_send(mqWR,arr1,strlen(arr1) + 1, 0 );
        mq_close(mqWR);
        
		mqRW = mq_open("/ReadWriteQueue",O_RDONLY | O_CREAT,0666,NULL);
        if(mqRW == -1){
            return 2;
        }
        mq_receive(mqRW, arr2, ARR_SIZE, NULL);

		printf("User2: %s\n", arr2);
        mq_close(mqRW);
        

		
	}
	return 0;
}
