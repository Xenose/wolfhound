#include <wh/debug/logger.h>
#include <wh-sys/socket.h>

#include <wh-posix/arpa/inet.h>
#include <wh-posix/errno.h>
#include <wh-posix/netdb.h>
#include <wh-posix/netinet/in.h>
#include <wh-posix/netinet/ip6.h> // if available
#include <wh-posix/sys/socket.h>
#include <wh-posix/sys/types.h>
#include <wh-posix/unistd.h>

wh_socket_s _wh_socket_init(_wh_socket_init_params params) {
    int s = -1;
    int opt = 0;
    wh_socket_s out = { 0 };
    struct addrinfo hints = { 0 };
    struct addrinfo* results = nullptr;
    
    int (*conbind)(int socket, const struct sockaddr* address, socklen_t address_len) = &connect;

    hints = (struct addrinfo){
        .ai_flags = params.flags,
        .ai_family = AF_INET6,
        .ai_socktype = params.socket_type,
    };

    out = (wh_socket_s) {
        -1
    };

    if (WH_SOCKET_SERVER & params.flags) {
        wh_log_debug(("Entrering server mode for socket!"));
        params.ip = "::";
        conbind = &bind;
    }

    if (0 != (s = getaddrinfo(params.ip, params.port, &hints, &results))) {
        wh_log_error(("Failed [ getaddrinfo ]!"));
        goto go_error_exit;
    }

    wh_log_debug(("Testing to create socket..."));
    for (struct addrinfo* pres = results; pres != nullptr; pres = pres->ai_next) {
        out.fd = socket(pres->ai_family, pres->ai_socktype, pres->ai_protocol);

        if (-1 == out.fd) {
            wh_log_debug(("Socket invalid [ %i ] $n"), out.fd, errno);
            continue;
        }

        if (-1 == setsockopt(out.fd, IPPROTO_IPV6, IPV6_V6ONLY, &opt, sizeof(opt))) {
            wh_log_critical(("Failed to bind socket to IPv4 [ errno : $n ] [ socket value : %i ]"), errno, out.fd);
        }

        if (0 != conbind(out.fd, pres->ai_addr, pres->ai_addrlen)) {
            wh_log_error(("Failed to bind/connect socket [ %i ] $n"), out.fd, errno);
            close(out.fd);
            out.fd = -1;
            continue;
        }

        break;
    }

    wh_log_debug(("Socket created [ %i ]\n"), out.fd);
    freeaddrinfo(results);

    if (-1 == out.fd) {
        wh_log_error(("Failed to create socket [ $n ]"), errno);
        goto go_error_exit;
    }


go_error_exit:
    return out;
}
