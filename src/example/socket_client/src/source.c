#define USE_NAMESPACE_WOLFHOUND
#include<wh-posix/unistd.h>
#include<wh-posix/stdio.h>
#include<wh/debug/logger.h>
#include<wh-sys/socket.h>

int main(int arc, char* const* arv) {
    int rin = 0;
    char buffer[256] = { 0 };
    wh_socket_s client = { 0 };

    wh_log_debug(("Starting client..."));
    client = wh_socket_init(nullptr, "8080", WH_SOCKET_UDP);
    wh_log_debug(("Clientr started!"));

    if (-1 != client.fd) while (1) {
        printf("Type your message [ %i ]: ", rin);
        rin = read(0, buffer, 255);
        sendto(client.fd, buffer, rin, 0, nullptr, 0);
    }

    return 0;
}
