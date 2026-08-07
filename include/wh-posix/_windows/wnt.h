#ifndef _wnt_header_posix_windows_
#define _wnt_header_posix_windows_

// DO NOT INCLUDE THIS OUTSIDE WH-POSIX C SOURCE FILE!
// WINDOWS.H INCLUDED!
#include<windows.h>
#include<wh-common/common.h>

enum {
   _WNT_ENTRY_UNKNOWN,
   _WNT_ENTRY_HANDLE,
   _WNT_ENTRY_MEMORY,
   _WNT_ENTRY_SOCKET,
};

enum {
   _WNT_CALL_FD_READ,
   _WNT_CALL_FD_WRITE,
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