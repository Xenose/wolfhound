#include<wh-common/common.h>
#include<wh-posix/windows.h>

enum {
   WNT_STATUS_UNKNOWN = -1,
   WNT_STATUS_SUCCESS = 0,
   WNT_STATUS_USER_APC,
   WNT_STATUS_ALERTED,
   WNT_STATUS_NO_YIELD_PERFORMED,
};

i64 _wnt_ntstatus(i64 status) {
   switch(status) {
      case STATUS_SUCCESS:
         return WNT_STATUS_SUCCESS;
      case STATUS_USER_APC:
         return WNT_STATUS_USER_APC;
      case STATUS_ALERTED:
         return WNT_STATUS_ALERTED;
      case STATUS_NO_YIELD_PERFORMED:
         return WNT_STATUS_NO_YIELD_PERFORMED;
   }

   return WNT_STATUS_UNKNOWN;
}