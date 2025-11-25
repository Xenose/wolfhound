#define USE_NAMESPACE_WOLFHOUND
#include<wh/wrap/unistd.h>
#include<wh/network/socket.h>

int main(int arc, char* const* arv) {
	int rin = 0;
	char buffer[256] = { 0 };
	wh_socket_s client = { 0 };

	client = wh_socket_init(nullptr, "8080", WH_SOCKET_UDP);

	while (1) {
		rin = read(0, buffer, 255);
		sendto(client.fd, buffer, rin, 0, nullptr, 0);
	}

	return 0;
}
