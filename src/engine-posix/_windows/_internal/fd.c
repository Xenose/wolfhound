#include<wh-posix/_windows/wnt.h>

/*
 * TODO:
 *
 * Note later optimize by using a u64 for 64 entires check
 * in one go, where a bit is a used block.
 */

i64 _wnt_fd_get(_wnt_s* wnt, va_list args) {
   // input
   int fd = va_arg(args, int);
   _wnt_entry_s* out = va_arg(args, _wnt_entry_s*);
   
   if (fd >= wnt->fds.capacity) {
      goto go_error_exit;
   }

   *out = wnt->fds.entries[fd];
   return 0;
go_error_exit:
   return -1;
}

i64 _wnt_fd_insert(_wnt_s* wnt, va_list args) {
   int* fd = va_arg(args, int*);
   _wnt_entry_s in = va_arg(args, _wnt_entry_s);

   if (wnt->fds.capacity <= wnt->fds.count) {
      i64 old_size      = sizeof(_wnt_entry_s) * wnt->fds.capacity;
      i64 new_size      = (sizeof(_wnt_entry_s) * wnt->fds.capacity) * 3;
      i64 new_capacity  = new_size / sizeof(_wnt_entry_s);

      if (wnt->fds.capacity >= new_capacity) {
         new_capacity = (new_capacity < 0) ?
            (4096 / sizeof(_wnt_entry_s)) : (new_capacity += 4096 / sizeof(_wnt_entry_s));
         new_size = new_capacity * sizeof(_wnt_entry_s);
      }

      void* tmp = VirtualAlloc(
         nullptr, 
         new_size, 
         MEM_RESERVE | MEM_COMMIT,
         PAGE_READWRITE
      );

      if (nullptr == tmp) {
         goto go_error_exit;
      }

      memset(tmp, 0, new_size);
      memcpy(tmp, wnt->fds.entries, old_size);
      VirtualFree(wnt->fds.entries, 0, MEM_RELEASE);

      wnt->fds.entries = tmp;
      wnt->fds.capacity = new_capacity;
   }

   for (i64 i = 3; i < wnt->fds.capacity; i++) {
      if (_WNT_ENTRY_FREE == wnt->fds.entries[i].type) {
         wnt->fds.entries[i] = in;
         ++wnt->fds.count;
         *fd = i;
         goto go_success;
      }
   }

go_error_exit:
   return -1;
go_success:
   return 0;
}

i64 _wnt_fd_delete(_wnt_s* wnt, va_list args) {
   int fd = va_arg(args, int);
   
   if (fd >= wnt->fds.capacity) {
      goto go_error_exit;
   }

   wnt->fds.entries[fd].type = _WNT_ENTRY_FREE;
   return 0;
go_error_exit:
   return -1;
}
