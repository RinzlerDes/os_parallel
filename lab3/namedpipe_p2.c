// This program reads first, then writes
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int fd1;

    // FIFO file path
    char * myfifo = "./myfifo";

    // Creating the named file(FIFO)
    // mkfifo(<pathname>,<permission>)
    mkfifo(myfifo, 0666);

    char str1[80], str2[80];
    // First open in read only and read
    fd1 = open(myfifo,O_RDONLY);
    read(fd1, str1, 80);

    // Print the read string and close
    printf("Received: %s\n", str1);

    // read pid
    char pid_str[100];
    read(fd1, pid_str, 100);
    printf("%s\n", pid_str);

    close(fd1);

    // Now open in write mode and write
    // string taken from user.
    fd1 = open(myfifo,O_WRONLY);
    printf("your message: ");
    fgets(str2, 80, stdin);
    write(fd1, str2, strlen(str2)+1);

    // send my pid
    pid_t pid = getpid();
    char msg[32];
    sprintf(msg, "p2 pid: %d\n", pid);
    printf(msg);
    write(fd1, msg, 32);

    close(fd1);
    return 0;
}
