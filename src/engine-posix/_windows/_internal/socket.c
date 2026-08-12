#include<wh-posix/_windows/wnt.h>

i64 _wnt_init_socket_back_init(_wnt_s* wnt, va_list args);
i64 _wnt_init_socket_back_done(_wnt_s* wnt, va_list args);

i64 (*_wnt_init_socket_back)(_wnt_s* wnt, va_list args) = &_wnt_init_socket_back_init;

i64 _wnt_init_socket_back_init(_wnt_s* wnt, va_list args) {
   int error = 0;
   WSADATA wd = { 0 };

   error = WSAStartup(MAKEWORD(2,2), &wd);

   switch(error) {
      default:
         errno = EACCES;
         printf("ERRROR %i", error);
         return -1;
      case 0:
         printf("Windows socket layer started!\n");
         _wnt_init_socket_back = &_wnt_init_socket_back_done;
         return 0;
   }
}

i64 _wnt_init_socket_back_done(_wnt_s* wnt, va_list args) {
   return 0;
}
