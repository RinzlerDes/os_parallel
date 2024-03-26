#include <stdio.h>
#include <string.h>

int main( )
{ 
    // Declare the file pointer
    FILE *filePointer ;
    char fname[] =  "myoutput1.txt";
     
    // Get the data to be written in file
    char dataToBeWritten[] = "I love NY. I love ROC. I love BPORT, too.";
 
    // in write mode using "w" attribute
    filePointer = fopen(fname, "w");
     
    // Check if this filePointer is null
    // which maybe if the file does not exist
    if ( filePointer == NULL )
    {
        printf( "%s failed to open.\n", fname);
    }
    else
    {         
        printf("The file is now opened.\n") ;
         
        // Write the dataToBeWritten into the file
        if ( strlen ( dataToBeWritten ) > 0 )
        {
            // writing in the file using fputs()
            fputs(dataToBeWritten, filePointer) ;
            fputs("\n", filePointer) ;
        }
         
        // Closing the file using fclose()
        fclose(filePointer) ;
         
        printf("Writing is successful!\n");
        printf("The file is now closed.\n") ;
    }
    return 0;       
}
