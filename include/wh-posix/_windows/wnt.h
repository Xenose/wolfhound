#ifndef _wh_header_posix_windows_wnt_
#define _wh_header_posix_windows_wnt_

// DO NOT INCLUDE THIS OUTSIDE WH-POSIX C SOURCE FILE!
// WINDOWS.H INCLUDED!
#include<windows.h>
#include<wh-common/common.h>

enum {
   _WH_ENTRY_HANDLE,
   _WH_ENTRY_MEMORY,
   _WH_ENTRY_SOCKET,
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
} _wh_wnt_entry_s;

typedef struct {
   u64 capacity;     // total capacity
   u64 count;        // current used
   _wh_wnt_entry_s* entries;
} _wh_wnt_table_s;

typedef struct {
   _wh_wnt_table_s fds;
   _wh_wnt_table_s mmaps;
} _wh_wnt_t;

#endif /* _wh_header_posix_windows_wnt_ */