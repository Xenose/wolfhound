#include<wh-posix/windows.h>
#include<wh-posix/_windows/wnt.h>

#define _WNT_RAW
#include<wh-posix/netdb.h>
#include<wh-posix/stdio.h>

int wnt_getaddrinfo(const char* node, const char* service, const struct addrinfo* hints, struct addrinfo** res) {
   if (0 == getaddrinfo(node, select, hints, res)) {
      printf("Failed!\n");
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