#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int fin, fout, l;
    char buf[4096];
    if (argc > 3) {
        fprintf(stderr, "Usage: %s filein fileout\n", argv[0]);
        exit(1);
    }
    fin = 0;
    fout = 1;
    if (argc > 2)
        if ((fout = creat(argv[2], 0777)) == -1) {
            perror(argv[2]);
            exit(1);
        }
    if (argc > 1)
        if ((fin = open(argv[1], O_RDONLY)) == -1) {
            perror(argv[1]);
            exit(1);
        }
    while ((l = read(fin, buf, 4096)) > 0)
        write(fout, buf, l);
    close(fin);
    close(fout);
    exit(0);
}