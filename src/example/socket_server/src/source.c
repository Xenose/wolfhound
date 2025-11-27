#define USE_NAMESPACE_WOLFHOUND
#include<string.h>
#include<wh/debug/logger.h>
#include<wh/network/socket.h>

int main(int arc, char* const* arv) {
	int rin = 0;
	char buffer[256] = { 0 };
	wh_socket_s server = wh_socket_init(nullptr, "8080", WH_SOCKET_UDP, WH_SOCKET_SERVER);

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
