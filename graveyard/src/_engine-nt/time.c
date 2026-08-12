#include <wh-core/common.h>
#include <wh-posix/windows.h>

#include <wh-nt/time.h>

void _wnt_get_system_time_precise_as_file_time(wnt_filetime_s* out) {
   FILETIME ft = { 0 };

   if (nullptr == out) {
      return;
   }
	
	GetSystemTimePreciseAsFileTime(&ft);

   out->low_date_time = ft.dwLowDateTime;
   out->high_date_time = ft.dwHighDateTime;
}

i8 _wnt_query_performance_frequency(i64* quad) {
   LARGE_INTEGER out = { 0 };

   if (QueryPerformanceFrequency(&out)) {
      ((i32*)quad)[0] = out.LowPart;
      ((i32*)quad)[1] = out.HighPart;
      return 1;
   }

   ((i32*)quad)[0] = 0;
   ((i32*)quad)[1] = 0;
   return 0;
}

i8 _wnt_query_performance_counter(i64* quad) {
   LARGE_INTEGER out = { 0 };

   if (QueryPerformanceCounter(&out)) {
      ((i32*)quad)[0] = out.LowPart;
      ((i32*)quad)[1] = out.HighPart;
      return 1;
   }

   ((i32*)quad)[0] = 0;
   ((i32*)quad)[1] = 0;
   return 0;
}

i64 _wnt_get_tick_count() {
   return GetTickCount();
}

i64 _wnt_delay_execution(bool alertable, i64 delay_interval) {
   BOOLEAN a = alertable ? TRUE : FALSE;
   LARGE_INTEGER di = { .QuadPart = delay_interval };

   return NtDelayExecution(a, &di);
}
