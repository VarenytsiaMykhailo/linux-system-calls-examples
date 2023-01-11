#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

// /dev/sda1 - блок ориентированный (диск)
// /dev/tty0 - байт ориентированный
int main(int argc, char *argv[]) {
    struct stat st;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s file\n", argv[0]);
        exit(1);
    }
    if (stat(argv[1], &st) == -1) {
        perror("stat error");
        exit(1);
    }
    printf("Device=%lu Inode=%lu Mode=0%o\n", st.st_dev, st.st_ino, st.st_mode);
    printf("Links=%lu UID=%d GID=%d\n", st.st_nlink, st.st_uid, st.st_gid);
    printf("TypeDevice=0x%lx | %lu Size=%ld\n", st.st_rdev, st.st_rdev, st.st_size);
    printf("Size of block=%ld Count of blocks=%ld\n", st.st_blksize, st.st_blocks);
    printf("atime=%s", ctime(&st.st_atime));
    printf("mtime=%s", ctime(&st.st_mtime));
    printf("ctime=%s", ctime(&st.st_ctime));
}