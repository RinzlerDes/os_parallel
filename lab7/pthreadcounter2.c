#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/mman.h>

pthread_t tid[2];
int counter;

// Shared variables for Petersons 
static int *flag0, *flag1, *turn;

const int WAIT1=1;
const int SLEEP1=1;

void* trythis0(void *arg)
{

    time_t t; srand((unsigned) time(&t));
    unsigned int i = 0, j =0;
    for(j=0; j<(0x3);j++) {
        // thread 0 is ready
        *flag0 = 1;
        // after this turn it is thread 1 turn
        *turn = 1;
        int counter0 = 0;
        // While its not thread 0 turn
        while(*flag1 == 1 && *turn == 1) {
            printf("Thread 0 waiting: %d \n", counter0);
            sleep(WAIT1);
            counter0++;
        }
        // Critical section
        printf("\n0 THREAD %d - Job %d has started\n", pthread_self(), counter);
        sleep(i=rand()%5);
        //sleep(1);
        counter += 1;
        printf("\n0 THREAD %d - Job %d has finished,sleep=%d\n", pthread_self(), counter-1,i);
        // End critical section
        *flag0 = 0;
    }
    pthread_exit(NULL);
}
 
void* trythis1(void *arg)
{

    time_t t; srand((unsigned) time(&t) + 1);
    unsigned int i = 0, j =0;
    for(j=0; j<(0x3);j++) {
        // Thread 1 is ready
        *flag1 = 1;
        // After this turn it is thread 0 turn
        *turn = 0;
        int counter1 = 0;
        // While its not thread 0 turn
        while(*flag0 == 1 && *turn == 0) {
            printf("Thread 1 waiting: %d \n", counter1);
            sleep(WAIT1);
            counter1++;
        }
        // Critical section
        printf("\n1 THREAD %d - Job %d has started\n", pthread_self(), counter);
        sleep(i=rand()%5);
        //sleep(1);
        counter += 1;
        printf("\n1 THREAD %d - Job %d has finished,sleep=%d\n", pthread_self(), counter-1,i);
        // End critical section
        *flag1 = 0;
    }
    pthread_exit(NULL);
}
 
int main(void)
{
    int k = 0;
    int error;

    flag0 = mmap(NULL, sizeof *flag0, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    flag1 = mmap(NULL, sizeof *flag1, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    turn = mmap(NULL, sizeof *turn, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    *flag0 = 0;
    *flag1 = 0;
    *turn = 0;

    int error0 = pthread_create(&(tid[0]), NULL, &trythis0, NULL);
    int error1 = pthread_create(&(tid[1]), NULL, &trythis1, NULL);

    if(error0 != 0 || error1 != 0)
        printf("\nThread can't be created : [%s]", strerror(error));


    // while(k < 2)
    // {
    //     error = pthread_create(&(tid[k]), NULL, &trythis, NULL);
    //     if (error != 0)
    //         printf("\nThread can't be created : [%s]", strerror(error));
    //     k++;
    // }

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    return 0;
}

