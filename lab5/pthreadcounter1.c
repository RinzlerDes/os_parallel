#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
 
pthread_t tid[2];
int counter;

void hello() {
    printf("hello world! Bye Bye world! %lu\n", pthread_self());
    pthread_exit(NULL);
}
 
void* trythis(void *arg)
{
    time_t t; srand((unsigned) time(&t));
    unsigned int i = 0, j =0;
    signal(SIGUSR1, hello);

    for(j=0; j<(0xA);j++) {
        printf("\n THREAD %lu - Job %d has started\n", pthread_self(), counter);
        sleep(i=rand()%5);
        counter += 1;
        //printf("\n THREAD %d - Job %d has finished,sleep=%d\n", pthread_self(), counter-1,i);
    }

    //pthread_exit(NULL);
}
 
int main(void)
{
    int k = 0;
    int error;

    while(k < 2)
    {
        error = pthread_create(&(tid[k]), NULL, &trythis, NULL);
        if (error != 0)
            printf("\nThread can't be created : [%s]", strerror(error));
        k++;
    }

    printf("sleep for 5\n");
    sleep(5);

    for(int i = 0; i < 2; i++) {
        pthread_kill(tid[i], SIGUSR1);
    }


    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    return 0;
}

