#include<wh-posix/_windows/wnt.h>

i64 _wnt_fd_read(_wnt_s* wnt, va_list args) {
   // input
   int fd = va_arg(args, int);
   _wnt_entry_s* out = va_arg(args, int*);

   if (fd >= wnt->fds.capacity) {
      goto go_error_exit;
   }

   *out = wnt->fds.entries[fd];
   return 0;
go_error_exit:
   return -1;
}

i64 _wnt_fd_write(_wnt_s* wnt, va_list args) {
   int* fd = va_arg(args, int*);
   _wnt_entry_s in = va_arg(args, _wnt_entry_s);

   return 0;
}