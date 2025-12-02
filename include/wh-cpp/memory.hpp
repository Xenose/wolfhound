#ifndef _wh_header_cpp_memory_
#define _wh_header_cpp_memory_

#include<string>
#include<stdint.h>
#include<wh/memory.h>

namespace wh {

class heap_c {
public:
private:
	wh_heap_header_s* m_heap;
public:
	heap_c();
	heap_c(std::string name);
	heap_c(wh_heap_header_s*);

	wh_heap_header_s* raw();
private:
};

class memory_c {
private:
	heap_c m_heap;
public:
	memory_c();
	memory_c(const char* heap);
	memory_c(wh_heap_header_s* heap);
	memory_c(heap_c* heap);

	heap_c& heap_get(std::string name);

	heap_c heap_create(std::string name, wh_heap_header_s header, i64 bytes);
	void heap_destory(std::string name, i64 bytes);

	void* realloc(void* ptr, u64 bytes);
	void* realloc(wh_heap_header_s* heap, void* ptr, u64 bytes);
	void* realloc(wh_heap_header_s* heap, void* ptr, u64 bytes, u64 flags);
	void* realloc(wh_heap_header_s* heap, void* ptr, u64 bytes, u64 flags, i64* error);

	void free(void* ptr);
	void free(wh_heap_header_s* heap, void* ptr);
	void free(wh_heap_header_s* heap, void* ptr, void* owner);
	void free(wh_heap_header_s* heap, void* ptr, void* owner, i64* error);

	void tracking();
	void scan();
	void print();
	i64 leak_count();

private:
	_wh_mem_alloc_params _params_alloc_init(
		wh_heap_header_s* heap = nullptr, 
		u64 bytes = 0, 
		void* owner = nullptr, 
		u64 flags = 0, 
		i64* error = nullptr, 
		u64 line = 0, 
		const char* file = "no file given"
	);

	void* _alloc_raw(_wh_mem_alloc_params* params);
public:
	template<typename T>
	T* alloc(u64 count, void* owner = nullptr) {
		auto params = _params_alloc_init(nullptr, count * sizeof(T), owner);
		return (T*)this->_alloc_raw(&params);
	}

	template<typename T>
	T* alloc_raw(u64 bytes) {
		auto params = _params_alloc_init(nullptr, bytes);
		return (T*)this->_alloc_raw(&params);
	}

	template<typename T>
	T* alloc_raw(heap_c& heap, u64 bytes, void* owner, u64 flags, i64* error, u64 line, const char* file) {
		auto params = _params_alloc_init(heap.raw(), bytes, owner, flags, error, line, file);
		return (T*)this->_alloc_raw(&params);
	}
};


} // namespace wh

#endif /* _wh_header_cpp_memory_ */
