#include<wh-posix/fcntl.h>

#include<wh-posix/_windows/wnt.h>
#include<wh-posix/_windows/windows.h>


int fcntl(int fd, int op, ...) {

}

int open(const char* path, int flags, mode_t mode) {
   int fd = -1;
	_wnt_entry_s entry = { 0 };
   HANDLE handle = 0;

   // Windows stuff...
   DWORD dw_desired_access = 0;;
   DWORD dw_share_mode = 0;
   LPSECURITY_ATTRIBUTES ls_security_attributes = 0;
   DWORD dw_create_disposition = 0;
   DWORD dw_flag_and_attributes = 0;
   HANDLE h_template_file = 0;

   handle = CreateFileA(
      path,
      dw_desired_access,
      dw_share_mode,
      ls_security_attributes,
      dw_create_disposition,
      dw_flag_and_attributes,
      h_template_file 
   );

   if (INVALID_HANDLE_VALUE == handle) {
		goto go_error_exit;
   }

   entry.type = _WNT_ENTRY_HANDLE;
   entry.handle = handle;
  
   if (-1 == _wnt_call(_WNT_CALL_FD_INSERT, &fd, entry)) {
      CloseHandle(handle);
      fd = -1;
		goto go_error_exit;
   }

go_error_exit:
   return fd;
}
