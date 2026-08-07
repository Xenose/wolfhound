#include<wh-posix/stdarg.h>
#include<wh-posix/unistd.h>
#include<wh-posix/_windows/wnt.h>

// internal fucntions
#include"fd.c"

_wnt_s _wnt = { 0 };

// Pre-Decleration
i64 _wnt_call_init(i64 call_id, ...);
i64 _wnt_call_real(i64 call_id, ...);
i64 _wnt_call_real_va(i64 call_id, va_list args);

// Function pointer
i64 (*_wnt_call)(i64 call_id, ...) = &_wnt_call_init;

// Singelton
i64 _wnt_call_init(i64 call_id, ...) {
   i64 result = 0;
   va_list args;
   
   u64 ebytes = getpagesize() * sizeof(_wnt_entry_s);
   u64 ecount = ebytes / sizeof(_wnt_entry_s);

   _wnt.fds.entries = VirtualAlloc(nullptr, ebytes, MEM_RESERVE, PAGE_READWRITE); // file descriptor table

   if (nullptr == _wnt.fds.entries) {
   }

   _wnt.fds.capacity = ecount;
   _wnt.mmaps.entries = VirtualAlloc(nullptr, ebytes, MEM_RESERVE, PAGE_READWRITE); // mmap table

   if (nullptr == _wnt.mmaps.entries) {
   }

   _wnt.mmaps.capacity = ecount;
   // Setting the new function
   _wnt_call = &_wnt_call_real;

   // Producing the results needed
   va_start(args, call_id);
   result = _wnt_call_real_va(call_id, args);
   va_end(args);

   return result;
}

i64 _wnt_call_real(i64 call_id, ...) {
   i64 result = 0;
   va_list args;

   // Producing the results needed
   va_start(args, call_id);
   result = _wnt_call_real_va(call_id, args);
   va_end(args);

   return result;
}

i64 _wnt_call_real_va(i64 call_id, va_list args) {
   return 0;
}