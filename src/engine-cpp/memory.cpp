#include<wh-cpp/memory.hpp>


wh::heap_c::heap_c() {
}

wh::heap_c::heap_c(wh_heap_header_s* heap) {
    m_heap = heap;
}

wh::memory_c::memory_c() {
}

wh::memory_c::memory_c(const char* heap_name) : 
    m_heap(wh_heap_get(heap_name)) {
    }

wh::memory_c::memory_c(wh_heap_header_s* heap) {
}

wh::memory_c::memory_c(heap_c* heap) {
}

_wh_mem_alloc_params wh::memory_c::_params_alloc_init(
        wh_heap_header_s* heap, u64 bytes, void* owner, u64 flags, i64* error, u64 line, const char* file) {
    _wh_mem_alloc_params params = { heap, bytes, owner, flags, error, line, file };
    return params;
}

void* wh::memory_c::_alloc_raw(_wh_mem_alloc_params* params) {
    return _wh_alloc(*params);
}


void wh::memory_c::free(void* ptr) {
    _wh_mem_free_params params = {
        nullptr,
        ptr,
        nullptr,
        nullptr
    };

    _wh_free(params);
}
