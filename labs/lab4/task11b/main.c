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


    struct flock read_lock;
    read_lock.l_type = F_RDLCK;
    read_lock.l_whence = SEEK_SET;
    read_lock.l_start = 0;
    read_lock.l_len = 0;

    struct flock write_lock;
    write_lock.l_type = F_WRLCK;
    write_lock.l_whence = SEEK_SET;
    write_lock.l_start = 0;
    write_lock.l_len = 0;

    struct flock current_lock;

    int fork_result = fork();
    if (fork_result) {
        while (1) {

            //write_lock.l_type = F_WRLCK;
            //fcntl(1, F_SETLKW, &write_lock);

            read_lock.l_type = F_RDLCK;
            fcntl(0, F_SETLKW, &read_lock);



            /*
            fcntl(0, F_GETLK, &current_lock);
            if (current_lock.l_type == F_RDLCK) {
                //write(1, "parent blocked by F_RDBLCK", 26);
                //continue;
            }
            fcntl(1, F_GETLK, &current_lock);
            if (current_lock.l_type == F_WRLCK) {
                //write(1, "parent blocked by F_WRLCK", 25);
                //continue;
            } else {
                //write(1, "parent not blocked by F_WRLCK", 29);
            }
             */

            //////////////


            read_bytes = read(0, buf, BUFFER_SIZE);
            if (read_bytes == -1) {
                perror("read");
            }
            read_lock.l_type = F_UNLCK;
            fcntl(0, F_SETLK, &read_lock);

            //=============

            //////////////


            write(1, "from parent: ", 13);
            write(1, buf, read_bytes);




            //write_lock.l_type = F_UNLCK;
            //fcntl(1, F_SETLK, &write_lock);
            //=============

        }
        wait(NULL);
        exit(0);
    } else {
        while (1) {
            read_lock.l_type = F_RDLCK;
            fcntl(0, F_SETLKW, &read_lock);

            //write_lock.l_type = F_WRLCK;
            //fcntl(1, F_SETLKW, &write_lock);







            /*
            fcntl(0, F_GETLK, &current_lock);
            if (current_lock.l_type == F_RDLCK) {
                //write(1, "child blocked by F_RDBLCK", 25);
                //continue;
            }
            fcntl(1, F_GETLK, &current_lock);
            if (current_lock.l_type == F_WRLCK) {
                //write(1, "child blocked by F_WRLCK", 24);
                //continue;
            } else {
                //write(1, "child not blocked by F_WRLCK", 28);
            }
             */

            //////////////


            read_bytes = read(0, buf, BUFFER_SIZE);
            if (read_bytes == -1) {
                perror("read");
            }

            read_lock.l_type = F_UNLCK;
            fcntl(0, F_SETLK, &read_lock);

            //=============

            //////////////


            write(1, "from child: ", 12);
            write(1, buf, read_bytes);


            //write_lock.l_type = F_UNLCK;
            //fcntl(1, F_SETLK, &write_lock);


            //=============
        }
        exit(0);

    }
}
