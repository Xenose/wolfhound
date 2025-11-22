#include<wh/cpp/memory.hpp>


wh::memory::memory() {
}

wh::memory::memory(const char* heap) {
}

wh::memory::memory(wh_heap_header_s* heap) {
}

wh::memory::memory(heap* heap) {
}

_wh_mem_alloc_params wh::memory::_params_alloc_init(
	wh_heap_header_s* heap, u64 bytes, void* owner, u64 flags, i64* error, u64 line, const char* file) {
	_wh_mem_alloc_params params = { heap, bytes, owner, flags, error, line, file };
	return params;
}

void* wh::memory::_alloc_raw(_wh_mem_alloc_params* params) {
	return _wh_alloc(*params);
}


void wh::memory::free(void* ptr) {
	_wh_mem_free_params params = {
		nullptr,
		ptr
	};

	_wh_free(params);
}
