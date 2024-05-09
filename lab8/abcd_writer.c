// semaphore_thread.c
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>

void check_letter_count(char x, int count);

#define ARR_SIZE 16
const int LETTER_COUNT = ARR_SIZE/4;

// Shared semaphore
sem_t mylock;

// Shared data
char letters[ARR_SIZE];
int letter_index = 0;

void* threadA( void* arg) {
    for(int i = 0; i < LETTER_COUNT; i++) {
        // Critical section
        sem_wait(&mylock);

        printf("\nEntering the critical section for A\n");
        printf("Index: %d\n", letter_index);

        letters[letter_index] = 'A';
        letter_index++;

        printf("\nExiting the critical section for A\n");

        // Increment semaphore
        sem_post(&mylock);
        sleep(0);
    } 
}

void* threadB( void* arg) {
    for(int i = 0; i < LETTER_COUNT; i++) {
        // Critical section
        sem_wait(&mylock);

        printf("Entering the critical section for B\n");
        printf("Index: %d\n", letter_index);

        letters[letter_index] = 'B';
        letter_index++;

        printf("Exiting the critical section for B\n");

        // Increment semaphore
        sem_post(&mylock);
        sleep(0);
    } 
}

void* threadC( void* arg) {
    for(int i = 0; i < LETTER_COUNT; i++) {
        // Critical section
        sem_wait(&mylock);

        printf("Entering the critical section for C\n");
        printf("Index: %d\n", letter_index);

        letters[letter_index] = 'C';
        letter_index++;

        printf("Exiting the critical section for C\n");

        // Increment semaphore
        sem_post(&mylock);
        sleep(0);
    } 
}

void* threadD( void* arg) {
    for(int i = 0; i < LETTER_COUNT; i++) {
        // Critical section
        sem_wait(&mylock);

        printf("Entering the critical section for D\n");
        printf("Index: %d\n", letter_index);

        letters[letter_index] = 'D';
        letter_index++;

        printf("Exiting the critical section for D\n");

        // Increment semaphore
        sem_post(&mylock);
        sleep(0);
    } 
}

int main() {
    sem_init(&mylock, 0, 1);

    pthread_t t1,t2, t3, t4;

    pthread_create(&t1,NULL,threadA,NULL);
    pthread_create(&t2,NULL,threadB,NULL);
    pthread_create(&t3,NULL,threadC,NULL);
    pthread_create(&t4,NULL,threadD,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    pthread_join(t4,NULL);

    sem_destroy(&mylock);

    printf("\nArray Size: %d, Numbers for each letter: %d\n", ARR_SIZE, LETTER_COUNT);
    printf("Final array: ");
    for(int i = 0; i < ARR_SIZE; i++) {
        printf("%c ", letters[i]);
    }
    printf("\n");

    // Count letters
    int a = 0, b = 0, c = 0, d = 0;

    for(int i = 0; i < ARR_SIZE; i++) {
        switch (letters[i]) {
            case 'A':
                a++;
                break;
            case 'B':
                b++;
                break;
            case 'C':
                c++;
                break;
            case 'D':
                d++;
                break;
            default:
                printf("default case error\n");
        }
    }

    check_letter_count('A', a);
    check_letter_count('B', b);
    check_letter_count('C', c);
    check_letter_count('D', d);

    return 0;
}

void check_letter_count(char x, int count) {
    if(count == LETTER_COUNT)
        printf("%c has %d occurences\n", x, count);
    else
        printf("%c does not occurs %d times instead of %d times\n", x, count, LETTER_COUNT);
}

