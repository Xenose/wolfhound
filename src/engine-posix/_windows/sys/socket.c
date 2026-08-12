#include<wh-posix/_windows/windows.h>
#include<wh-posix/_windows/wnt.h>

#define _WNT_RAW
#include<wh-posix/sys/socket.h>

int wnt_socket(int domain, int type, int protocol) {
   int fd = -1;
   _wnt_entry_s entry;
   SOCKET sock = { 0 };

   if (-1 == _wnt_call(_WNT_CALL_INIT_SOCKET_BACK)) {
      goto go_error_exit;
   }

   sock = socket(domain, type, protocol);

   if (INVALID_SOCKET == sock) {
      _wnt_call(_WNT_CALL_ERROR_2_ERRNO, _WNT_ERROR_TYPE_SOCKET, WSAGetLastError(), &errno);
      return -1;
   }

   entry.sock = sock;
   entry.type = _WNT_ENTRY_SOCKET;

	if (-1 ==  _wnt_call(_WNT_CALL_FD_INSERT, &fd, entry)) {
      closesocket(sock);
      errno = ENFILE;
      return -1;
   }

   printf("Inserted socket fd == %i\n", fd);
   return fd;
go_error_exit:
   return -1;
}

// Normal functions

int wnt_listen(int sockfd, int backlog) {
   _wnt_entry_s entry;

   if (-1 == _wnt_call(_WNT_CALL_FD_GET, sockfd, &entry)) {
      errno = EBADF;
      return -1;
   }

   if (0 != listen(entry.sock, backlog)) {
      _wnt_call(_WNT_CALL_ERROR_2_ERRNO, _WNT_ERROR_TYPE_SOCKET, WSAGetLastError(), &errno);
      return -1;
   }

   return 0;
}

int wnt_connect(int sockfd, const struct sockaddr* addr, socklen_t addrlen) {
   _wnt_entry_s entry;

   if (-1 == _wnt_call(_WNT_CALL_FD_GET, sockfd, &entry)) {
      errno = EBADF;
      return -1;
   }

   if (SOCKET_ERROR == connect(entry.sock, addr, addrlen)) {
      _wnt_call(_WNT_CALL_ERROR_2_ERRNO, _WNT_ERROR_TYPE_SOCKET, WSAGetLastError(), &errno);
      return -1;
   }

   return 0;
}

int wnt_bind(int sockfd, const struct sockaddr* addr, socklen_t addrlen) {
   _wnt_entry_s entry;

   if (-1 == _wnt_call(_WNT_CALL_FD_GET, sockfd, &entry)) {
      errno = EBADF;
      return -1;
   }

   if (0 != bind(entry.sock, addr, addrlen)) {
      _wnt_call(_WNT_CALL_ERROR_2_ERRNO, _WNT_ERROR_TYPE_SOCKET, WSAGetLastError(), &errno);
      return -1;
   }

   return 0;
}

int wnt_setsockopt(int sockfd, int level, int option_name, const void* option_value, socklen_t option_len) {
   _wnt_entry_s entry;

   if (0 != _wnt_call(_WNT_CALL_FD_GET, sockfd, &entry)) {
      errno = EBADF;
      return -1;
   }

   if (SOCKET_ERROR == setsockopt(entry.sock, level, option_name, option_value, option_len)) {
      switch(WSAGetLastError()) {
         case WSANOTINITIALISED: errno = EINVAL;      break;
         case WSAENETDOWN:       errno = EINVAL;      break;
         case WSAEFAULT:         errno = ENOMEM;      break;
         case WSAEINPROGRESS:    errno = ENOBUFS;     break;
         case WSAEINVAL:         errno = ENOPROTOOPT; break;
         case WSAENETRESET:      errno = ENOTSOCK;    break;
         case WSAENOPROTOOPT:    errno = ENOPROTOOPT; break;
         case WSAENOTCONN:       errno = ENOTSOCK;    break;
         case WSAENOTSOCK:       errno = ENOTSOCK;    break;
         default:                errno = EIO;         break;
      }
      return -1;
   }

   return 0;
}

ssize_t wnt_send(int sockfd, const void* buffer, size_t size, int flags) {
   ssize_t sent = 0;
   _wnt_entry_s entry;

   if (-1 == _wnt_call(_WNT_CALL_FD_GET, sockfd, &entry)) {
      errno = EBADF;
      return -1;
   }
   
   sent = send(entry.sock, buffer, size, flags);

   if (0 > sent) {
      _wnt_call(_WNT_CALL_ERROR_2_ERRNO, _WNT_ERROR_TYPE_SOCKET, WSAGetLastError(), &errno);
      return -1;
   }

   return sent;
}

ssize_t wnt_recv(int sockfd, const void* buffer, size_t size, int flags) {
   ssize_t r = 0;
   _wnt_entry_s entry;

   if (0 != _wnt_call(_WNT_CALL_FD_GET, sockfd, &entry)) {
      errno = EBADF;
      return -1;
   }
   
   r = recv(entry.sock, buffer, size, flags);

   if (0 > r) {
      _wnt_call(_WNT_CALL_ERROR_2_ERRNO, _WNT_ERROR_TYPE_SOCKET, WSAGetLastError(), &errno);
      return -1;
   }

   return r;
}

ssize_t wnt_sendto(int sockfd, const void* buffer, size_t size, int flags, struct sockaddr* dest_addr, socklen_t addrlen) {
   ssize_t sent = 0;
   _wnt_entry_s entry;

   if (0 != _wnt_call(_WNT_CALL_FD_GET, sockfd, &entry)) {
      errno = EBADF;
      return -1;
   }

   sent = sendto(entry.sock, buffer, size, flags, dest_addr, addrlen);

   if (0 > sent) {
      _wnt_call(_WNT_CALL_ERROR_2_ERRNO, _WNT_ERROR_TYPE_SOCKET, WSAGetLastError(), &errno);
      return -1;
   }

   return sent;
}

ssize_t wnt_recvfrom(int sockfd, const void* buffer, size_t size, int flags, struct sockaddr* src_addr, socklen_t* addrlen) {
   ssize_t r = 0;
   _wnt_entry_s entry;

   if (0 != _wnt_call(_WNT_CALL_FD_GET, sockfd, &entry)) {
      errno = EBADF;
      return -1;
   }

   r = recvfrom(entry.sock, buffer, size, flags, src_addr, addrlen);

   if (SOCKET_ERROR == r) {
      _wnt_call(_WNT_CALL_ERROR_2_ERRNO, _WNT_ERROR_TYPE_SOCKET, WSAGetLastError(), &errno);
      return -1;
   }

   return r;
}
