#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    struct stat st;
    int i, size = -1, isize;
    if (argc < 2) {
        fprintf(stderr, "Usage: %s file ...\n", argv[0]);
        exit(1);
    }
    for (i = 1; i < argc; i++)
        if (stat(argv[i], &st) == 0) {
            if (S_IFREG & st.st_mode && st.st_size > size)
                size = st.st_size, isize = i;
        } else
            perror(argv[i]);
    if (size != -1)
        printf("File %s has max length %d\n", argv[isize], size);
    exit(0);
}
