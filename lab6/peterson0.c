#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <time.h>


//Shared Global variables to control processes 
static int *flag0;
static int *flag1;
static int *turn;

const int WAIT1=1;
const int SLEEP1=1;


int main(int argc, char const *argv[])
{  
    flag0 = mmap(NULL, sizeof *flag0, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    flag1 = mmap(NULL, sizeof *flag1, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    turn = mmap(NULL, sizeof *turn, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    *flag0 = 0;
    *flag1 = 0;
    *turn;

    // creates child process
    pid_t pid = fork();

    //prcess 1 (parent):
    if(pid > 0){
        // initialize random seed
        srand(time(NULL));

        //process ready
        *flag0 = 1;
        // turn selector
        *turn = 1;
        int counter = 0;
        //while to wait for turn change
        while (*flag1 && *turn == 1)
        {
            // busy wait
            printf("Parent waiting: %d sec------------------.\n", counter);
            sleep(WAIT1);
            counter++;
        }

        // second loop
        int counter1 = 0;
        int sleepTimer;
        while (counter1 < 10) {
            sleepTimer = rand() % 5;
            printf("Parent waiting: %d sec.\n", sleepTimer);
            sleep(sleepTimer);
            counter1++;
        }

        // critical section
        printf("PARENT: critical section\n");
        sleep(SLEEP1);         
        // end of critical section
        *flag0 = 0;
    }

    //process 2 (child): 
    if(pid == 0){
        // initialize random seed
        srand(time(NULL) + 1);
        
        //process ready
        *flag1 = 1;
        // turn selector
        *turn = 0;
        //while to wait for turn change
        int counter = 0;
        int sleepTimer;
        while (*flag0 == 1 && *turn == 0)
        {
            // busy wait
            sleepTimer = rand() % 5;
            printf("Child waiting: %d sec.\n", sleepTimer);
            sleep(sleepTimer);
            counter++;
        }
        // critical section
        printf("CHILD: Critical section\n");
        sleep(SLEEP1);         
        // end of critical section
        *flag1 = 0;
    }

    wait(); // wait for child
    return 0;
}
