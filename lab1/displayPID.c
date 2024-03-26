/* 
   Program to illustrate UNIX 
   system calls getpid and getppid
*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
   pid_t mypid, parentpid;

   mypid = getpid();
   parentpid = getppid();
   printf("Hi! I am a simple process.  In this birth,\n");
   printf("My pid is %d\n", mypid); 
   printf("My parent's pid is %d\n", parentpid); 
   printf("I will terminate when you press Enter key\n");
   getchar(); 
   return 0;
}
