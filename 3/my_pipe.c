#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h>  //make the warning gone.

#define SIZE_MSG 32 

char  msg[SIZE_MSG] ; 
  
int main() 
{ 
    char buf[SIZE_MSG]; 
    int pd[2], i; 
 
    printf("pipe here\n"); 
//first error is here
    if (pipe(pd) < 0) {
        printf("init failure. exit if failure.\n");
        exit(1); 
    }
    
    // the second error is here.
    for (i = 0; i < 3; i ++) {
	sprintf(msg, "message %d", i);
 	write(pd[1],msg, SIZE_MSG);
    }
  
    for (i = 0; i < 3; i++) { 
        read(pd[0], buf, SIZE_MSG); 
        printf("read %s\n", buf); 
    } 
    return 0; 
}

