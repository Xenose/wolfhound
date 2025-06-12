#include<stdarg.h>
#include<string.h>
#include<wh/cpp/print.hpp>

#include<string>

using namespace wh;

print::print(std::string format) {
	memset(&_params, 0, sizeof(_params));

	_format = std::move(format);
	_params.format = _format.c_str();

}

print& print::fd(int fd) {
	_params.fd = fd;
	return *this;
}
