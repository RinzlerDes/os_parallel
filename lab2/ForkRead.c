#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t childpid = fork();

    if(childpid == 0) {
        FILE* file_ptr;
        char input_file[] = "regressor_data.txt";
        char string[100];

        printf("I am child with pid: %d. My parent is: %d\n", getpid(), getppid());
        printf("I will print out first 5 lines of the %s.\n", input_file);

        if((file_ptr = fopen(input_file, "r")) == NULL) {
            printf("cant open file %s", input_file);
            exit(1);
        }

        int count = 0;
        while(count < 5) {
            fgets(string, sizeof(string), file_ptr);
            printf("%s", string);
            count++;
        }

        fclose(file_ptr);
    } 
    else {
        printf("I am the parent with pid: %d. My childs pid is: %d\n", getpid(), childpid);
        wait(NULL);
        printf("child has terminated\n");
    }

    printf("ByeBye from: %d\n", getpid());
    
    return 0;
}
