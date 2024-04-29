#include <stdio.h>
#include <signal.h>

void handler() {
    printf("good bye from %d\n", getpid());
    exit(0);
}

int main() {
    pid_t cpid1 = fork();
    pid_t cpid2;


    if(cpid1 == 0) {
        signal(SIGUSR1, handler);
        while(1) {
            printf("%d\n", getpid());
            sleep(2);
        }
    } else {
        cpid2 = fork();

        if(cpid2 == 0) {
            signal(SIGUSR1, handler);
            while(1) {
                printf("%d\n", getpid());
                sleep(2);
            }
        } else {
            sleep(10);
            kill(cpid1, SIGUSR1);
            kill(cpid2, SIGUSR1);
            wait(NULL);
        }
    }
}
