#include<wh-posix/windows.h>
#include<wh-posix/_windows/wnt.h>

#define _WNT_RAW
#include<wh-posix/netdb.h>
#include<wh-posix/stdio.h>

int wnt_getaddrinfo(const char* node, const char* service, const struct addrinfo* hints, struct addrinfo** res) {
   if (-1 == _wnt_call(_WNT_CALL_INIT_SOCKET_BACK)) {
      goto go_error_exit;
   }

   if (0 != getaddrinfo(node, service, hints, res)) {
      DWORD error = WSAGetLastError();
      _wnt_call(_WNT_CALL_ERROR_2_ERRNO, _WNT_ERROR_TYPE_SOCKET, error, &errno);
      printf("Error %i\n", error);
      goto go_error_exit;
   }

   return 0;
go_error_exit:
   return -1;
}

void wnt_freeaddrinfo(struct addrinfo *res) {
   freeaddrinfo(res);
}

const char* wnt_gai_strerror(int errcode) {
   return nullptr;
}
