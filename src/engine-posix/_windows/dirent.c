#include<wh-posix/dirent.h>

int alphasort(const struct dirent** src, const struct dirent** dst) {

}

int closedir(DIR* dir) {

}

int dirfd(DIR* dir) {
}

DIR* fdopendir(int fd) {
}

DIR* opendir(const char* path) {
}

struct dirent* readdir(DIR* dir) {
}

int readdir_r(DIR* dir, struct dirent* dst) {
}

void rewinddir(DIR* dir) {
}

int scandir(const char* path, struct dirent*** d, int(*df1)(const struct dirent*), int(*fd2)(const struct dirent**), const struct dirent** dd) {

}

void seekdir(DIR* dir, long fd) {

}

long telldir(DIR* dir) {

}
