#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {
    int file;
    if ((file = open("test", O_RDONLY)) == -1) {
        // errno
        printf("errno value = %d, message = %s\n", errno, strerror(errno));

        // sys_errlist
        printf("sys_errlist message = %s\n", sys_errlist[errno]);

        // perror
        perror("perror");
    } else {
        close(file);
    }

    return 0;
}