#include <stdio.h> 
int main (int argc, char *argv[])
{
   void swap (int*, int*); 
   int a, b; 

   char str1[] ="Please enter two integers: ";    
   printf ("%s", str1); 
   scanf ("%d %d", &a, &b);

   swap (&a, &b);

   printf ("a = %d b = %d\n", a, b); 
   return 0;
}

void swap (int* x, int* y)
{
   int temp; 
   temp = *x; *x = *y; *y = temp;
   return;
}
