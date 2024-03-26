#include <stdio.h>
#include <stdlib.h>

int main() {
    char read_file_name[] = "data_2D.txt";
    char write_file_name[] = "seekwrite.txt";
    char str[1024];
    FILE *read_file, *write_file;

    if((read_file = fopen(read_file_name, "r")) == NULL) {
        printf("Cant open file: %s\n", read_file_name);
        exit(1);
    }
    if((write_file = fopen(write_file_name, "w")) == NULL) {
        printf("Cant open file: %s\n", write_file_name);
        exit(1);
    }

    fseek(read_file, 4096, SEEK_SET);

    fread(str , sizeof(char), sizeof(str) - 1, read_file);

    fwrite(str, sizeof(char), sizeof(str), write_file);

    fclose(read_file);
    fclose(write_file);

    return 0;
}
