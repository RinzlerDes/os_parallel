#include <stdlib.h>
#include <stdio.h>
#include <signal.h> /*for signal() and raise()*/

void hello(int signum){
    printf("Hello World!\n");
}

int main(){
    signal(SIGUSR1, hello);   //execute hello() when receiving signal SIGUSR1  
    raise(SIGUSR1);   //send SIGUSR1 to the calling process  
}
