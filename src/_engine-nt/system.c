#include<_wh-nt/system.h>
#include<wh-posix/windows.h>

void _wnt_get_system_info(_wnt_system_info* si) {
   SYSTEM_INFO i;
   GetSystemInfo(&i);
   
   *si = (_wnt_system_info){
      .page_size = i.dwPageSize,
   };
}