#ifndef _wh_header_posix_sys_socket_
#define _wh_header_posix_sys_socket_

#include<wh-core/os.h>
#include<wh-posix/sys/types.h>

#if (WH_SYSTEM&WH_SYS_POSIX)
   #include<wh-posix/sys/socket.h>
#else
   #include <wh-posix/winsock2.h>
   #include <wh-posix/ws2tcpip.h>

   #if !(WH_SYSTEM&WH_SYS_WINDOWS)
      #define AF_UNIX         0xF000
      #define AF_INET         0xF001
      #define AF_IPX          0xF003
      #define AF_APPLETALK    0xF004
      #define AF_INET6        0xF006
      #define AF_DECnet       0xF007

      #define SOCK_STREAM     0x0F01
      #define SOCK_DGRAM      0x0F02
      #define SOCK_SEQPACKET  0x0F03
      #define SOCK_RAW        0x0F04
   #endif

   #define AF_LOCAL        AF_UNIX
   #define AF_AX25         0xF002
   #define AF_X25          0xF005
   #define AF_KEY          0xF008
   #define AF_NETLINK      0xF009
   #define AF_PACKET       0xF00A
   #define AF_RDS          0xF00B
   #define AF_PPPOX        0xF00C
   #define AF_LLC          0xF00D
   #define AF_IB           0xF00E
   #define AF_MPLS         0xF00F
   #define AF_CAN          0xF010
   #define AF_TIPC         0xF011
   #define AF_BLUETOOTH    0xF012
   #define AF_ALG          0xF013
   #define AF_VSOCK        0xF014
   #define AF_KCM          0xF015
   #define AF_XDP          0xF016

   #define SOCK_DRM        0x0F05
   #define SOCK_PACKET     0x0F06
   
   extern int wnt_socket(int domain, int type, int protocol);
   extern int wnt_listen(int sockfd, int backlog);
   extern int wnt_connect(int sockfd, const struct sockaddr* addr, socklen_t addrlen);
   extern int wnt_bind(int sockfd, const struct sockaddr* addr, socklen_t addrlen);
   extern int wnt_setsockopt(int sockfd, int level, int option_name, const void* option_value, socklen_t option_len);

   // TCP
   extern ssize_t wnt_send(int sockfd, const void* buffer, size_t size, int flags);
   extern ssize_t wnt_recv(int sockfd, const void* buffer, size_t size, int flags);

   // UDP
   extern ssize_t wnt_sendto(int sockfd, const void* buffer, size_t size, int flags, struct sockaddr* dest_addr, socklen_t addrlen);
   extern ssize_t wnt_recvfrom(int sockfd, const void* buffer, size_t size, int flags, struct sockaddr* src_addr, socklen_t* addrlen);


   #ifndef _WNT_RAW
      #define socket       wnt_socket
      #define listen       wnt_listen
      #define connect      wnt_connect
      #define bind         wnt_bind
      #define setsockopt   wnt_setsockopt

      // TCP
      #define send      wnt_send
      #define recv      wnt_recv

      // UDP
      #define sendto    wnt_sendto
      #define recvfrom  wnt_recvfrom
   #endif
#endif

#endif /* _wh_header_posix_sys_socket_ */
