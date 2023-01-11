#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

const int BUFFER_SIZE = 64;

int main() {
    int read_bytes;
    char buf[BUFFER_SIZE];

    int fork_result = fork();
    if (fork_result) {
        while (1) {
            //sleep(1);
            read_bytes = read(0, buf, BUFFER_SIZE);
            if (read_bytes == -1) {
                perror("read");
            }

            write(1, "from parent: ", 13);
            write(1, buf, read_bytes);
        }
        wait(NULL);
        exit(0);
    } else {
        while (1) {
            //sleep(1);
            read_bytes = read(0, buf, BUFFER_SIZE);
            if (read_bytes == -1) {
                perror("read");
            }
            write(1, "from child: ", 12);
            write(1, buf, read_bytes);
        }
        exit(0);
    }
}
