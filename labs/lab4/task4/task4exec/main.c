#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    char buf[80] = {};

    while (1) {
        int n = read(STDIN_FILENO, buf, 80);
        write(STDOUT_FILENO, buf, n);
    }
}