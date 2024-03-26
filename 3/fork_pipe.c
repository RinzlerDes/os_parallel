#include <stdio.h> 
#include <unistd.h> 
#include <string.h>

#define SIZE_MSG 32 

char msg[SIZE_MSG];  
  
int main() 
{ 
    char buf[SIZE_MSG]; 
    int i, pd[2], pid, nbytes; 
  
    if (pipe(pd) < 0) 
        exit(1); 
  
    if ((pid = fork()) > 0) { 
        sleep(5);
	
        for( i = 0; i < 3 ; i++) {
            sprintf(msg, "message %d", i);
            write(pd[1], msg, SIZE_MSG); 
        }   
        close(pd[0]);
        //close(pd[1]); 
        wait(NULL); 
    } 
    else {
        //close(pd[1]); 
        while ((nbytes = read(pd[0], buf, SIZE_MSG)) > 0) 
            printf("% s\n", buf); 

        printf("after while\n");
        if (nbytes != 0) 
            exit(2); 
        printf("reading Done\n");
        close(pd[0]);
    } 
    return 0; 
} 
