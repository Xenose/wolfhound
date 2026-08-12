#include<wh-posix/_windows/wnt.h>

i64 _wnt_error_2_errno(_wnt_s* wnt, va_list args) {
   u64 type = va_arg(args, u64);
   i64 error = va_arg(args, i64);
   int* e = va_arg(args, int*); // errno

   switch(type) {
      case _WNT_ERROR_TYPE_NORMAL:
         switch (error) {
				case ERROR_ACCESS_DENIED:	*e = EACCES; 	break;
				case ERROR_DISK_FULL:		*e = ENOSPC; 	break;
				case ERROR_INVALID_HANDLE: *e = EBADF;		break;
			   case ERROR_PATH_NOT_FOUND: *e = ENOENT;   break;
            case ERROR_FILE_NOT_FOUND: *e = ENOENT;   break;
            case ERROR_INVALID_NAME:   *e = ENOENT;   break;
				default:							*e = EIO;		break;
			}
         return 0;

      case _WNT_ERROR_TYPE_SOCKET:
         switch (error) {
				default:							*e = EIO;		   break;
			}
         return 0;
   }

   return -1;
}
