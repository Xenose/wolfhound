#include<stdarg.h>
#include<string.h>
#include<wh-cpp/print.hpp>

#include<string>

using namespace wh;

print::print() {
}

print::print(std::string format) {
	memset(&_params, 0, sizeof(_params));

	_format = std::move(format);
	_params.format = _format.c_str();

}

print& print::format(const std::string& format) {
	memset(&_params, 0, sizeof(_params));

	_format = std::move(format);
	_params.format = _format.c_str();

	return *this;
}

print& print::fd(int fd) {
	_params.fd = fd;
	return *this;
}

print& print::buffer(char* buffer, i64 length) {
	_params.buffer = buffer;
	_params.buffer_length = length;
	return *this;
}

print& print::flags(u64 flags) {
	_params.flags = flags;
	return *this;
}

print& print::offset(i64 offset) {
	_params.offset = offset;
	return *this;
}
