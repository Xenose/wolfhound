#include<wh-maths/hash.h>
#include<wh-cpp/maths/hash.hpp>

u32 wh::maths::hash::xx32(const wh_buffer_s& buffer, u32 seed=0) {
	_wh_hash_xx32_params params;

	params.buffer = buffer;
	params.seed = seed;

	return _wh_hash_xx32(params);
}
