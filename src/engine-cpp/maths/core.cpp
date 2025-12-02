#include<string>
#include<wh/maths/core.h>
#include<wh-cpp/maths/core.hpp>


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

template<>
i8 wh::maths::abs<i8>(i8 value) {
	return WH_ABS_I8(value);
}

template<>
i16 wh::maths::abs<i16>(i16 value) {
	return WH_ABS_I16(value);
}

template<>
i32 wh::maths::abs<i32>(i32 value) {
	return WH_ABS_I32(value);
}

template<>
i64 wh::maths::abs<i64>(i64 value) {
	return WH_ABS_I64(value);
}

#if !(WH_SYSTEM&WH_SYS_MSVC)

template<>
i128 wh::maths::abs<i128>(i128 value) {
	return WH_ABS_I128(value);
}

#endif
