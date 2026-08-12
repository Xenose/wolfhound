#ifndef _wh_header_posix_windows_fd_table_
#define _wh_header_posix_windows_fd_table_

#include<wh-posix/_windows/windows.h>

typedef enum {
   _WNT_FD_TYPE_EMPTY,
   _WNT_FD_TYPE_HANDLE,
   _WNT_FD_TYPE_MEMORY,
   _WNT_FD_TYPE_SOCKET,
   _WNT_FD_TYPE_STD,
} _wnt_fd_type;

typedef enum {
   _WNT_FDOP_GET,
   _WNT_FDOP_CREATE,
   _WNT_FDOP_DELETE,
   _WNT_FDOP_SEARCH,
} _wnt_fdop;

typedef struct {
   _wnt_fd_type type;

   union {
      HANDLE      handle;
      void*       ptr;
   } data;
} _wnt_fd_entry;

extern int _wnt_table(int fd, _wnt_fdop op, _wnt_fd_entry* entry);


#endif /* _wh_header_posix_windows_fd_table_ */
