#include <stdio.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int main() {
    pid_t childpid = fork();
    char path[] = "/home/rinzler/OneDrive/school/os_parallel/lab2/SeekReadWrite";

    if(childpid == 0) {
        printf("I am the child with pid: %d\n", getpid());
        execlp(path, (char *) NULL);
    }
    else {
        printf("I am the parent with pid: %d. My childs pid is: %d\n", getpid(), childpid);
        wait(NULL);
        printf("child has terminated\n");
    }
    
    printf("ByeBye from: %d\n", getpid());

    return 0;
}
