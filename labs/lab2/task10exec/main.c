#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[], char * envp[]) {

    printf("___________________________ PROCESS NAME %s\n", argv[0]);

    /*
    printf("PARAMS:\n");
    for (char** it = argv; *it; it++) {
        printf("%s\n", *it);
    }

    printf("ENV:\n");
    for (char** it = envp; *it; it++) {
        printf("%s\n", *it);
    }
    */

    system(argv[1]);

    exit(0);
}