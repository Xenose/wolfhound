#include<wh-cpp/string.hpp>

extern "C" {
	#include<wh/string.h>
}

namespace wh {

const char* strstr(string key, string str, uint64_t* error = nullptr) {
	return wh_strstr(key.c_str(), str.c_str(), str.length(), key.length(), error);
}

} // namespace
