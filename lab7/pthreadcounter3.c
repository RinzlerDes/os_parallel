#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

#define NUM_THREADS 2

pthread_t tid[NUM_THREADS];
// Data shared between threads
int counter;
pthread_mutex_t lock_counter;

void* try_this(void *arg) {
    time_t t; srand((unsigned) time(&t));
    unsigned int i = 0, j = 0;
    for(j = 0; j < (0x3); j++) {
        // Critical section ---------------------------------------------
        // Lock shared var
        pthread_mutex_lock(&lock_counter);
        printf("\nTHREAD %d - Job %d has started\n", pthread_self(), counter);
        sleep(i=rand()%5);
        printf("\nTHREAD %d - Job %d has finished, sleep = %d\n", pthread_self(), counter, i);
        counter++;
        // Unlock shared var
        pthread_mutex_unlock(&lock_counter);
        // End of critical section -------------------------------------------
        // Sleep to prevent the first thread from starving other threads
        printf("Sleep 0\e");
        sleep(0);
    }
    pthread_exit(NULL);
}

int main() {
    int error;

    // Init mutex
    pthread_mutex_init(&lock_counter, NULL);
    
    // Spawn threads
    for(int i = 0; i < NUM_THREADS; i++) {
        error = pthread_create(&(tid[i]), NULL, &try_this, NULL);
        if(error != 0) {
            printf("\nThread can't be created : [%s]", strerror(error));
        }
    }
    
    // Join threads
    for(int i = 0; i < NUM_THREADS; i++) {
        pthread_join(tid[i], NULL);
    }

    return 0;
}
