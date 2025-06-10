#include<stdarg.h>
#include<wh/data/hashmap_lazy.h>
#include<wh/maths/core.h>
#include<wh/memory.h>
#include<wh/print.h>

#include<string.h>
#include<stdio.h>

wh_hashmap_lazy_s _wh_hashmap_lazy_create(wh_heap_header_s* heap, u64 count, u64 data_size) {
	wh_hashmap_lazy_s out = { 0 };

	out.entries = wh_alloc(
		heap, 
		(sizeof(wh_hashmap_lazy_entry_s) * count) + data_size,
		&out.entries,
		WH_MEM_ZERO
	); 

	if (nullptr == out.entries) {
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

	ne = wh_realloc(map->heap, map->entries, (sizeof(wh_hashmap_lazy_entry_s) * new_count) + map->data_size);

	if (nullptr == ne) {
		// TODO handle error
	}

	map->entries = ne;
}

void _wh_hashmap_lazy_insert(_wh_hashmap_lazy_insert_params params) {
	u64 hash = wh_hash_simple(params.key, params.map->count);
	wh_hashmap_lazy_entry_s* e = nullptr;
	void* data = nullptr;

	e = wh_ptr_add(params.map->entries, (sizeof(wh_hashmap_lazy_entry_s) + params.map->data_size) * hash);

	if (nullptr != e->key) {
		_wh_hashmap_lazy_resize(params.map);
	}

	data = wh_ptr_add(e, sizeof(wh_hashmap_lazy_entry_s));

	printf("---> [ %p ]\n", e);
	printf("---> [ %p ]\n", data);

	e->key = params.key;
	memcpy(data, params.data, params.map->data_size);
}

void* _wh_hashmap_lazy_get(_wh_hashmap_lazy_get_params params) {
	void* out = nullptr;
	u64 hash = wh_hash_simple(params.key, params.map->count);

	if (params.map->count > hash) {
		out = wh_ptr_add(params.map->entries, (sizeof(wh_hashmap_lazy_entry_s) + params.map->data_size) * hash);
		out = wh_ptr_add(out, sizeof(wh_hashmap_lazy_entry_s));
	}

	printf("---> [ %p ]\n", out);
	return out;
}
