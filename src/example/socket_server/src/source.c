#define USE_NAMESPACE_WOLFHOUND
#include<wh-posix/string.h>
#include<wh/debug/logger.h>
#include<wh-sys/socket.h>

int main(int arc, char* const* arv) {
    int rin = 0;
    char buffer[256] = { 0 };
    wh_socket_s server = { 0 };

    wh_log_debug(("Starting server..."));
    server = wh_socket_init(nullptr, "8080", WH_SOCKET_UDP, WH_SOCKET_SERVER);
    wh_log_debug(("Server started"));

    if (-1 == server.fd) {
        wh_log_error(("Failed to allocate FD!\n"));
    }

    while (1) {
        if (-1 != (rin = recvfrom(server.fd, buffer, 255, 0, nullptr, 0))) {
            for (i64 i = 0; 0 != buffer[i]; i++) {
                if ('\n' == buffer[i]) {
                    buffer[i] = ' ';
                }
            }

            wh_log_info(("RECIVED -> %s"), buffer);
        }

        memset(buffer, 0, 256);
    }

    return 0;
}
