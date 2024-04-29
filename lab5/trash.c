#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

pthread_t tid[2];
int counter;

void hello(int signum) {
    printf("Hello world! Bye Bye world! \n");
    pthread_exit(NULL);
}

void* trythis(void *arg)
{
    time_t t; srand((unsigned) time(&t));
    unsigned int i = 0, j =0;
    signal(SIGUSR1, hello); // Register signal handler

    for(j=0; j<(0xA);j++) {
        printf("\n THREAD %ld - Job %d has started\n", pthread_self(), counter);
        sleep(i=rand()%5);
        counter += 1;
        //printf("\n THREAD %ld - Job %d has finished,sleep=%d\n", pthread_self(), counter-1,i);
    }

    pthread_exit(NULL);
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

    sleep(5); // Sleep for 5 seconds
    // Send SIGUSR1 signal to each thread
    pthread_kill(tid[0], SIGUSR1);
    pthread_kill(tid[1], SIGUSR1);

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    return 0;
}

