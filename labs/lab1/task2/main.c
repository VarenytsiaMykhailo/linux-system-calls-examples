#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

// Delete 'file' before running
// argv[1] - filename, argv[2] - permissions
int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s file filemode\n", argv[0]);
        //exit(1);
    }

    char *ptr_for_error_check;
    long permissions = strtol(argv[2], &ptr_for_error_check, 8);
    if (strlen(argv[2]) != ptr_for_error_check - argv[2]) {
        fprintf(stderr, "%s: incorrect filemode\n", argv[2]);
        //exit(1);
    }

    int file_descriptor;
    if ((file_descriptor = creat(argv[1], permissions)) == -1) {
        perror("creat error");
        //exit(1);
    }
    printf("file_descriptor = %d\n", file_descriptor);

    const ssize_t num_of_chars = 18;
    ssize_t write_result;
    if ((write_result = write(file_descriptor, "test1\ntest2\ntest3\n", num_of_chars)) == -1) {
        perror("write error");
        //exit(1);
    }
    printf("write_result = %zd\n", write_result);

    int close_result;
    if ((close_result = close(file_descriptor)) == -1) {
        perror("close error");
        //exit(1);
    }
    printf("close_result = %d\n", close_result);


    if ((file_descriptor = open(argv[1], O_RDONLY)) == -1) {
        perror("open error");
        //exit(1);
    }
    printf("file_descriptor = %d\n", file_descriptor);

    char read_buffer[1024];
    // read_result returns -1 if error, 0 if read all file, real read num of bytes otherwise
    ssize_t read_result;
    if ((read_result = read(file_descriptor, read_buffer, num_of_chars)) == -1) {
        perror("read error");
        //exit(1);
    }
    printf("read_result = %zd\n", read_result);
    printf("read data:\n%s\n", read_buffer);

    if ((close_result = close(file_descriptor)) == -1) {
        perror("close error");
        //exit(1);
    }
    printf("close_result = %d\n", close_result);;

    if ((file_descriptor = open(argv[1], O_RDWR)) == -1) {
        perror("open error");
        //exit(1);
    }
    printf("file_descriptor = %d\n", file_descriptor);

    return 0;
}