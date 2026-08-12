#ifndef _wh_header_posix_netdb_
#define _wh_header_posix_netdb_

#include<wh-core/os.h>

// For libc-testing
#ifndef NI_NUMERICSCOPE
    #define NI_NUMERICSCOPE 0x0040
#endif

#if (WH_SYSTEM&WH_SYS_POSIX)
    #include <netdb.h>
#else
    #include <wh-posix/winsock2.h>
    #include <wh-posix/ws2tcpip.h>

    extern int wnt_getaddrinfo(const char* node, const char* service, const struct addrinfo* hints, struct addrinfo** res);
    extern void wnt_freeaddrinfo(struct addrinfo *res);
    extern const char* wnt_gai_strerror(int errcode);
    
    #ifndef _WNT_RAW
        #undef gai_strerror

        #define getaddrinfo     wnt_getaddrinfo
        #define freeaddrinfo    wnt_freeaddrinfo
        #define gai_strerror    wnt_gai_strerror
   #endif
#endif

#endif /* _wh_header_posix_netdb_ */
