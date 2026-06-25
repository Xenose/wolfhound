#include<wh-posix/sys/mman.h>

void* mmap(void* addr, size_t length, int prot, int flags, int fildes, off_t off) {
   if (0 == length) {
      return nullptr;
   }
}