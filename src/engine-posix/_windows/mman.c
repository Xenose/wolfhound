#include<wh-posix/sys/mman.h>
#include<wh-posix/_windows/fd_table.h>

void* mmap(void* addr, size_t length, int prot, int flags, int fildes, off_t off) {
   void* ptr = MAP_FAILED;
   _wnt_fd_entry entry = { 0 };

   if (0 == length) {
      goto go_error_exit;
   }

   if (-1 == fildes) {
      entry.data.ptr = VirtualAlloc(nullptr, length, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

      if (nullptr == entry.data.ptr) {
         goto go_error_exit;
      }

      if (-1 == _wnt_table(0, _WNT_FDOP_CREATE, &entry)) {
         if (0 == VirtualFree(entry.data.ptr, 0, MEM_RELEASE)) {
            // TODO very bad...
         }
         goto go_error_exit;
      }

      ptr = entry.data.ptr;
   } else if (-1 != _wnt_table(fildes, _WNT_FDOP_GET, &entry)) {
      HANDLE handle = CreateFileMapping(entry.data.handle, NULL, PAGE_READONLY, 0, 0, nullptr);

      if (!handle) {
         goto go_error_exit;
      }

      ptr = MapViewOfFile(handle, FILE_MAP_READ, 0, 0, length);
      CloseHandle(handle);

      if (nullptr == ptr) {
         goto go_error_exit;
      }
   } else {
      // TODO invalid fd
   }

go_error_exit:
   return ptr;
}

int munmap(void *addr, size_t len) {
   int rc = 0;
   int fd = 0;

   _wnt_fd_entry entry = {
      .data.ptr = addr,
   };

   fd = _wnt_table(0, _WNT_FDOP_SEARCH, &entry);

   if (-1 == fd) {
      // TODO go to error
   }

   switch (entry.type) {
      case _WNT_FD_TYPE_MEMORY:
         if (0 == VirtualFree(entry.data.ptr, 0, MEM_RELEASE)) {
            // TODO very bad...
         }
         break;
      case _WNT_FD_TYPE_HANDLE:
         if (0 == UnmapViewOfFile(entry.data.ptr)) {
            // TODO very bad...
         }
         break;
   }

   _wnt_table(fd, _WNT_FDOP_DELETE, nullptr);
   return rc;
}