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
	char arr1[ARR_SIZE], arr2[80];
	while (1)
	{
        mqWR = mq_open("/WriteReadQueue",O_RDONLY);
        
        if(mqWR == -1){
            return 1;
        }
        mq_receive(mqWR, arr1, ARR_SIZE, NULL);

        printf("User1: %s\n", arr1);
        
        mq_close(mqWR);

		fgets(arr2, 80, stdin);
        

		mqRW = mq_open("/ReadWriteQueue",O_WRONLY);
        if(mqRW == -1){
            return 2;
        }
        mq_send(mqRW, arr2, ARR_SIZE, 0);
        mq_close(mqRW);
		
        
		
	}
    
	return 0;
}
