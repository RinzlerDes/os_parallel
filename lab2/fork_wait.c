#include<stdio.h> 
#include<sys/wait.h> 
#include<unistd.h> 

int main() 
{ 
    pid_t childpid = fork();

    if (childpid == 0) { 
        printf("hello from child. My pid: %d\n", getpid());
        sleep(10);
    }
    else
{ 
        printf("hello from parent. My child pid: %d\n", childpid); 
        //wait(NULL); 
        printf("child has terminated\n"); 
    } 
    printf("ByeBye from: %d\n", getpid()); 
    return 0; 
}
