#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int read_file_descriptor, write_file_descriptor, num_of_bytes;
    char c;
    char *name;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s file\n", argv[0]);
        exit(1);
    }
    if ((read_file_descriptor = open(argv[1], O_RDONLY)) == -1) {
        perror(argv[1]);
        exit(1);
    }
    int fork_result = fork();
    if (fork_result) {
        name = "father";
    } else {
        name = "son";
    }
    if ((write_file_descriptor = creat(name, 0600)) == -1) {
        perror(name);
        exit(1);
    }
    while ((num_of_bytes = read(read_file_descriptor, &c, 1)) > 0) {
        write(write_file_descriptor, &c, num_of_bytes);
        //printf("%c", c);
    }
    close(read_file_descriptor);
    close(write_file_descriptor);

    printf("\n\n\n\n\n");
    system("cat father");
    printf("\n\n\n\n\n");
    system("cat son");

    exit(0);
}