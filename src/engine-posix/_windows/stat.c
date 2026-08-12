#include<wh-posix/sys/stat.h>

int stat(const char* path, struct stat* statbuf) {
}

int fstat(int fd, struct stat* statbuf) {
}

int lstat(const char* path, struct stat* statbuf) {
}

int fstatat(int dirfd, const char* path, struct stat* statbuf) {
}
