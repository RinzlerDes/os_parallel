#include <stdio.h>
#include <stdlib.h>

struct fourChar
{
    char c[4];
};

int main()
{
    int n;
    struct fourChar myword;
    FILE *fptr;

    if ((fptr = fopen("myoutput1.txt","rb")) == NULL){
        printf("Error! opening file");

        // Program exits if the file pointer returns NULL.
        exit(1);
    }

    // Moves the cursor to the beginning of the file
    fseek(fptr, 0, SEEK_SET);

    for(n = 1; n < 5; ++n)
    {
        fread(&myword.c, sizeof(struct fourChar), 1, fptr);
        //fread(&myword.c, sizeof(struct fourChar) - 1, 1, fptr);
        printf("C:%s\n", myword.c);
    }
    fclose(fptr); 

    return 0;
}
