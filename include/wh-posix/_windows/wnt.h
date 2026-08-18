#ifndef _wnt_header_posix_windows_
#define _wnt_header_posix_windows_

// DO NOT INCLUDE THIS OUTSIDE WH-POSIX C SOURCE FILE!
// WINDOWS.H INCLUDED!
#include <wh-posix/_windows/windows.h>
#include <wh-core/common.h>

// Dummy values for lsp server
#if !(WH_SYSTEM&WH_SYS_WINDOWS)
    #include"_dummy.h"
#endif

#define WNT_INVALID_PID ((pid_t)LLONG_MAX)

enum {
   _WNT_ENTRY_FREE,
   _WNT_ENTRY_HANDLE,
   _WNT_ENTRY_MEMORY,
   _WNT_ENTRY_SOCKET,
   _WNT_ENTRY_STD,
};

enum {
   _WNT_CALL_FD_GET,
   _WNT_CALL_FD_INSERT,
   _WNT_CALL_FD_DELETE,
   _WNT_CALL_MMAP_GET,
   _WNT_CALL_MMAP_INSERT,
   _WNT_CALL_MMAP_DELETE,
   _WNT_CALL_ERROR_2_ERRNO,
   _WNT_CALL_INIT_SOCKET_BACK,
};

enum {
   _WNT_ERROR_TYPE_NORMAL,
   _WNT_ERROR_TYPE_SOCKET,
};

typedef struct {
   u64 type;
   union {
      // Windows types
      HANDLE handle;
      SOCKET sock;
      // Generic memory address
      void* memory;
   };
} _wnt_entry_s;

typedef struct {
   u64 capacity;     // total capacity
   u64 count;        // current used
   _wnt_entry_s* entries;
} _wnt_table_s;

typedef struct {
   _wnt_table_s fds;
   _wnt_table_s mmaps;
} _wnt_s;

extern i64 (*_wnt_call)(i64 call_id, ...);

#endif /* _wh_header_posix_windows_wnt_ */
