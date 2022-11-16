#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

extern int errno;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage %s filename [filename ...]\n", argv[0]);
        exit(1);
    }

    char *filename = NULL;
    long max_size = 0;
    struct stat st = {0};
    for (int i = 1; i < argc; i++) {
        stat(argv[i], &st);
        long curr_size = st.st_size;
        printf("current checking filename %s size %ld bytes\n", argv[i], curr_size);
        if (curr_size > max_size) {
            max_size = curr_size;
            filename = argv[i];
        }
    }

    printf("%s size %ld bytes\n", filename, max_size);

    return 0;
}