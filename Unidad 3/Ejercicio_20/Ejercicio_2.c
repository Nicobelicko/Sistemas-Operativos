#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

static long glob = 0;
pthread_mutex_t sum_mutex;
static void *threadFunc(void *arg)
{
    int loops = *((int *)arg);
    long loc;

    for (int j = 0; j < loops; j++)
    {
        pthread_mutex_lock(&sum_mutex);
        loc = glob;
        loc++;
        glob = loc;
        pthread_mutex_unlock(&sum_mutex);
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t t1, t2;
    int loops, s;

    loops = (argc > 1) ? atol(argv[1]) : 10000000;
    printf("LOOP: %d\n",loops);
    pthread_mutex_init(&sum_mutex,NULL);

    s = pthread_create(&t1, NULL, threadFunc, &loops);
    if (s != 0)
        perror("pthread create");
    s = pthread_create(&t2, NULL, threadFunc, &loops);
    if (s != 0)
        perror("pthread create");

    s = pthread_join(t1, NULL);
    if (s != 0)
        perror("pthread_join");
    printf("glob 1 = %ld\n", glob);

    s = pthread_join(t2, NULL);
    if (s != 0)
        perror("pthread_join");
    pthread_mutex_destroy(&sum_mutex);
    printf("glob 2 = %ld\n", glob);
    exit(EXIT_SUCCESS);
}