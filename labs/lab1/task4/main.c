#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char **argv) {

    if (argc != 3) {
        fprintf(stderr, "Usage: %s file filemode\n", argv[0]);
        exit(1);
    }

    char *ptr_for_error_check;
    long permissions = strtol(argv[2], &ptr_for_error_check, 8);
    if (strlen(argv[2]) != ptr_for_error_check - argv[2]) {
        fprintf(stderr, "%s: incorrect filemode\n", argv[2]);
        exit(1);
    }

    int file_descriptor;
    if ((file_descriptor = creat(argv[1], permissions)) == -1) {
        perror("creat error");
        exit(1);
    }
    printf("file_descriptor = %d\n", file_descriptor);

    ssize_t write_result;
    if ((write_result = write(file_descriptor, "aaaaaa", 6)) == -1) {
        perror("write error");
        //exit(1);
    }
    printf("write_result = %zd\n", write_result);

    __off_t lseek_result_current_pointer;
    if ((lseek_result_current_pointer = lseek(file_descriptor, 0, SEEK_END)) == -1) {
        perror("lseek error");
        //exit(1);
    }
    printf("lseek_result_current_pointer = %zd\n", lseek_result_current_pointer);

    if ((write_result = write(file_descriptor, "b", 1)) == -1) {
        perror("write error");
        //exit(1);
    }
    printf("write_result = %zd\n", write_result);

    if ((lseek_result_current_pointer = lseek(file_descriptor, 0, SEEK_CUR)) == -1) {
        perror("lseek error");
        //exit(1);
    }
    printf("lseek_result_current_pointer = %zd\n", lseek_result_current_pointer);

    if ((write_result = write(file_descriptor, "c", 1)) == -1) {
        perror("write error");
        //exit(1);
    }
    printf("write_result = %zd\n", write_result);

    if ((lseek_result_current_pointer = lseek(file_descriptor, 0, SEEK_SET)) == -1) {
        perror("lseek error");
        //exit(1);
    }
    printf("lseek_result_current_pointer = %zd\n", lseek_result_current_pointer);

    if ((write_result = write(file_descriptor, "d", 1)) == -1) {
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

    return 0;
}