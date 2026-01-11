#ifndef _wh_cpp_header_maths_core_
#define _wh_cpp_header_maths_core_

#include<string>
#include<wh-common/common.h>

namespace wh::maths {

extern i64 intpos(i64 value, i64 base);
extern i64 hash_simple(std::string str, i64 slots);
extern i64 hash_simple(const char* str, i64 slots, u64 length);

template<typename T>
T abs(T value) {
	return fabs(value);
}

} // namespace wh::maths

#endif /* _wh_cpp_header_maths_core_ */
