#include <stdio.h>
#include <unistd.h>
int main (int argc, char *argv[])
{
   fork(); 
   fork(); 
   fork(); 
   printf ("Hello World! My pid = %d and My parent pid = %d\n", getpid(), getppid()); 
   int wait();
   return 0; 
}
