#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int l;
    char buf[4096];
    if (argc > 3) {
        fprintf(stderr, "Usage: %s filein fileout\n", argv[0]);
        exit(1);
    }
    if (argc > 1) {
        close(0);
        if (open(argv[1], O_RDONLY) == -1) {
            perror(argv[1]);
            exit(1);
        }
    }
    if (argc == 3) {
        close(1);
        if (creat(argv[2], 0777) == -1) {
            perror(argv[2]);
            exit(1);
        }
    }
    while ((l = read(0, buf, 4096)) > 0)
        write(1, buf, l);
    exit(0);
}
