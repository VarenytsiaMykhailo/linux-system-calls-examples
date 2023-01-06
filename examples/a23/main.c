#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int f, fw, l;
    char c;
    char *name;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s file\n", argv[0]);
        exit(1);
    }
    if ((f = open(argv[1], O_RDONLY)) == -1) {
        perror(argv[1]);
        exit(1);
    }
    if (fork())
        name = "father";
    else
        name = "son";
    if ((fw = creat(name, 0600)) == -1) {
        perror(name);
        exit(1);
    }
    while ((l = read(f, &c, 1)) > 0)
        write(fw, &c, l);
    close(f);
    close(fw);
    exit(0);
}