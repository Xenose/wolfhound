#include<wh/cpp/wolfhound.hpp>
#include<wh/cpp/print.hpp>

int main(int arc, char* const* arv) {
	wh::instance_c engine = wh::instance_c("cpp", arc, arv);

	wh::print("Hello %s!\n").fd(2).out("world");

	return 0;
}
