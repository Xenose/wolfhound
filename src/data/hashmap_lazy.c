#include<stdarg.h>
#include<wh/data/hashmap_lazy.h>
#include<wh/maths/core.h>
#include<wh/memory.h>


wh_hashmap_lazy_s _wh_hashmap_lazy_create(wh_heap_header_s* heap, u64 count, u64 data_size) {
	wh_hashmap_lazy_s out = { 0 };

	out.entries = wh_alloc(heap, sizeof(wh_hashmap_lazy_entry_s) * count, &out.entries); 

	if (nullptr != out.entries) {
		goto go_error_exit;
	}

	out.count = count;
	out.data_size = data_size;

go_error_exit:
	return out;
}

void _wh_hashmap_lazy_resize(wh_hashmap_lazy_s* map) {
	wh_hashmap_lazy_entry_s* ne = nullptr;
	u64 new_count = (map->count * 1.5);

	ne = wh_realloc(map->heap, map->entries, sizeof(wh_hashmap_lazy_entry_s) * new_count);

	if (nullptr == ne) {
	}

	map->entries = ne;
}

void _wh_hashmap_lazy_insert(_wh_hashmap_lazy_insert_params params, ...) {
	u64 hash = wh_hash_simple(params.key);

	if (nullptr != params.map->entries[hash].data) {
		_wh_hashmap_lazy_resize(params.map);
	}
}

void* _wh_hashmap_lazy_get(wh_hashmap_lazy_s* map, const char* key) {
	u64 hash = wh_hash_simple(key);

	if (map->count > hash) {
		return map->entries[hash].data;
	}

	return nullptr;
}
