#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[]) {
    struct stat st;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s file\n", argv[0]);
        exit(1);
    }
    if (stat(argv[1], &st) == -1) { // Системный вызов stat позволяет получить характеристики (атрибуты) файла, которые хранятся в индексном дескрипторе (inode)
        perror(argv[1]);
        printf("error");
        exit(1);
    }
    printf("Device=%lld Inode=%d Mode=0%o\n", st.st_dev, st.st_ino, st.st_mode);
    printf("Links=%d UID=%d GID=%d\n", st.st_nlink, st.st_uid, st.st_gid);
    printf("TypeDevice=0x%llx | %lld Size=%d\n", st.st_rdev, st.st_rdev, st.st_size);
    printf("Size of block=%d Count of blocks=%d\n", st.st_blksize, st.st_blocks);
    printf("atime=%s", ctime(&st.st_atime));
    printf("mtime=%s", ctime(&st.st_mtime));
    printf("ctime=%s", ctime(&st.st_ctime));
    exit(0);
}
