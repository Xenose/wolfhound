#include<string>
#include<wh/maths/core.h>
#include<wh/cpp/maths/core.hpp>


i64 wh::maths::intpos(i64 value, i64 base) {
	_wh_intpos_params params = {
		value, base
	};

	return _wh_intpos(params);
}

i64 wh::maths::hash_simple(std::string str, i64 slots) {
	_wh_hash_simple_params params = {
		str.c_str(), slots, str.length()
	};

	return _wh_hash_simple(params);
}

i64 wh::maths::hash_simple(const char* str, i64 slots, u64 length) {
	_wh_hash_simple_params params = {
		str, slots, length
	};

	return _wh_hash_simple(params);
}
