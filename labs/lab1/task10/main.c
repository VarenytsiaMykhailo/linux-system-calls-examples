#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

extern int errno;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s filename\n", argv[0]);
        exit(1);
    }

    int file_descriptor = open(argv[1], O_RDONLY);
    long file_size = lseek(file_descriptor, 0, SEEK_END);
    if (file_size > 0) {
        do {
            char letter = '\0';
            read(file_descriptor, &letter, 1);
            printf("%c", letter);
        } while (lseek(file_descriptor, -2, SEEK_CUR) >= 0);
    }

    printf("\n");
    close(file_descriptor);

    return 0;
}
