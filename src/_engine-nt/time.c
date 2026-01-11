#include<wh/common.h>
#include<wh-posix/windows.h>

#include<_wh-nt/time.h>

void _wnt_get_system_time_precise_as_file_time(wnt_filetime_s* out) {
   FILETIME ft = { 0 };

   if (nullptr == out) {
      return;
   }
	
	GetSystemTimePreciseAsFileTime(&ft);

   out->low_date_time = ft.dwLowDateTime;
   out->high_date_time = ft.dwHighDateTime;
}