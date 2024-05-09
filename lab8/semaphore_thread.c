// semaphore_thread.c
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>

sem_t mylock;

void* thread( void* arg)
{
    sem_wait(&mylock);
    printf("\nEntering the critical section..\n");

    sleep(4);

    printf("\nExiting the critical section...\n");
    sem_post(&mylock);
}
 
int main()
{
    sem_init(&mylock, 0, 1);
    pthread_t t1,t2;
    pthread_create(&t1,NULL,thread,NULL);
    sleep(2);
    pthread_create(&t2,NULL,thread,NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    sem_destroy(&mylock);
    return 0;
}
