// This process writes first, then reads
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

int main()
{
    int fd;

    // FIFO file path
    char * myfifo = "./myfifo";

    // Creating the named file(FIFO)
    // mkfifo(<pathname>, <permission>)
    mkfifo(myfifo, 0666);

char arr1[80], arr2[80]; 
    // Open FIFO for write only
    fd = open(myfifo, O_WRONLY);

    // Take an input arr2ing from user.
    // 80 is maximum length
    printf("your message: "); 
    fgets(arr2, 80, stdin);

    // Write the input arr2ing on FIFO
    // and close it
    write(fd, arr2, strlen(arr2)+1);

    // pid action
    char msg[32];
    pid_t my_pid = getpid();
    sprintf(msg, "p1 pid: %d\n", my_pid);
    printf(msg);
    write(fd, msg, 32);

    close(fd);

    // Open FIFO for Read only
    fd = open(myfifo, O_RDONLY);
    // Read from FIFO
    read(fd, arr1, sizeof(arr1));

    // Print the read message
    printf("Received: %s\n", arr1);
    
    // read pid message
    read(fd, msg, 32);
    printf(msg);

    close(fd);
return 0;
}
