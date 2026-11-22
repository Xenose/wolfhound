#include<wh-posix/dirent.h>

#include<wh-posix/_windows/windows.h>
#include<wh-posix/_windows/wnt.h>
#include<wh-posix/_windows/fd_table.h>

int alphasort(const struct dirent** src, const struct dirent** dst) {

}

int closedir(DIR* dir) {

}

int dirfd(DIR* dir) {
    _wnt_entry_s entry = { 0 };

   if (nullptr == dir) {
        errno = EBADF;
        return -1;
   }

   if (-1 == _wnt_call(_WNT_CALL_FD_GET, dir->fd, &entry)) {
      return -1;
   }

   if (_WNT_FD_TYPE_DIR_HANDLE != entry.type) {
      return -1;
   }

    return dir->fd;
}

DIR* fdopendir(int fd) {
}

DIR* opendir(const char* path) {
   DIR* d = nullptr;
   char tmp[MAX_PATH] = { 0 };
   _wnt_entry_s entry = {0};
   _wnt_dir_handle dir = {
      .find_data = { 0 },
      .handle = INVALID_HANDLE_VALUE,
   };

   FindFirstFile(tmp, &dir.find_data);

   if (INVALID_HANDLE_VALUE == dir.handle) {
   }

   entry.type = _WNT_FD_TYPE_DIR_HANDLE;
   entry.dir = dir;

   if (-1 == _wnt_call(_WNT_CALL_FD_INSERT, &d->fd, &entry)) {
   }

   return d;
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
