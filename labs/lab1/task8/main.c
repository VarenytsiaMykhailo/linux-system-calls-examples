#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc > 3) {
        fprintf(stderr, "Usage: %s filein fileout\n", argv[0]);
        exit(1);
    }

    int fin_descriptor = 0;
    int fout_descriptor = 1;
    if (argc > 2) {
        if ((fout_descriptor = creat(argv[2], 0777)) == -1) {
            perror(argv[2]);
            exit(1);
        }
    }

    if (argc > 1) {
        if ((fin_descriptor = open(argv[1], O_RDONLY)) == -1) {
            perror(argv[1]);
            exit(1);
        }
    }

    int buf_size = 4096;
    char buf[buf_size];
    int read_bytes_num;
    while ((read_bytes_num = read(fin_descriptor, buf, buf_size)) > 0) {
        write(fout_descriptor, buf, read_bytes_num);
    }

    close(fin_descriptor);
    close(fout_descriptor);
    exit(0);
}