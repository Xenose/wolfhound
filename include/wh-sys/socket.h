#ifndef _wh_header_socket_
#define _wh_header_socket_

#include<wh-core/common.h>

#if (WH_SYSTEM&WH_SYS_POSIX)
    #include<netdb.h>
    #include<sys/socket.h>
#elif (WH_SYSTEM&WH_SYS_WINDOWS)
    #include<wh-posix/windows.h>
#endif


#define WH_SOCKET_UDP SOCK_DGRAM
#define WH_SOCKET_TCP SOCK_STREAM
#define WH_SOCKET_SERVER AI_PASSIVE
#define WH_SOCKET_CLIENT 0

typedef struct {
    struct_type stype;
    int fd;
} wh_socket_s;

typedef struct {
    char* ip;
    char* port;
    int socket_type;
    int flags;
} _wh_socket_init_params;

extern wh_socket_s _wh_socket_init(_wh_socket_init_params params);
 
#define wh_socket_init(...) WH_EPF(_wh_socket_init((_wh_socket_init_params) { __VA_ARGS__ }))

#endif /* _wh_header_socket_ */
