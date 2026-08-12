#include<wh-posix/stdarg.h>
#include<wh/data/hashmap_lazy.h>
#include<wh/maths/core.h>
#include<wh-sys/memory.h>
#include<wh/print.h>
#include<wh/debug/logger.h>

#include<wh-posix/string.h>

wh_hashmap_lazy_entry_s* _wh_hashmap_entry(void* entry, u64  data_size, u64 index) {
	return wh_ptr_add(entry, (sizeof(wh_hashmap_lazy_entry_s) + data_size) * index);
}

void _wh_hashmap_lazy_delete(wh_hashmap_lazy_s* map) {
	wh_free(map->heap, map->entries);
	map->count = 0;
}

wh_hashmap_lazy_s _wh_hashmap_lazy_create(wh_heap_header_s* heap, u64 count, u64 data_size) {
	wh_hashmap_lazy_s out = { 0 };

	out.entries = wh_alloc(
		heap, 
		(sizeof(wh_hashmap_lazy_entry_s) + data_size) * count,
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

i8 _wh_hashmap_lazy_resize(wh_hashmap_lazy_s* map) {
	wh_hashmap_lazy_entry_s* ne = nullptr;
	u64 retries = 0;
	u64 new_count = map->count;
	void* data = nullptr;

go_retry:
	new_count = (u64)(((long double)new_count) * 1.5);
	wh_log_debug(("New size is [ %u ]"), new_count);
	ne = wh_alloc(
		map->heap, 
		(sizeof(wh_hashmap_lazy_entry_s) + map->data_size) * new_count, 
		&ne,
		WH_MEM_ZERO
	);

	if (nullptr == ne) {
		wh_log_error(("Failed to resize hashmap!"));
		goto go_error_exit;
	}

	wh_for (u64, i, map->count) {
		u64 hash = 0;
		wh_hashmap_lazy_entry_s* entry = nullptr;
		wh_hashmap_lazy_entry_s* ce = nullptr;

		ce = _wh_hashmap_entry(map->entries, map->data_size, i);

		if (nullptr == ce->key) {
			continue;
		}

		hash = wh_hash_simple(ce->key, new_count);
		entry = _wh_hashmap_entry(ne, map->data_size, hash);
		
		if (nullptr != entry->key) {
			if (!strcmp(entry->key, ce->key)) {
				wh_log_error(("Failed resize of hashmap, same key given twice [ %s ] skipping..."), ce->key);
				continue;
			}

			if (5 > retries++) {
				goto go_retry;
			} else {
				wh_log_error(("Too many resize retries, exiting..."));
				_wh_hashmap_lazy_delete(map);
				goto go_error_exit;
			}
		}
		
		entry->key = ce->key;
		memcpy(wh_ptr_add(entry, sizeof(wh_hashmap_lazy_entry_s)), wh_ptr_add(ce, sizeof(wh_hashmap_lazy_entry_s)), map->data_size);
	}

	_wh_hashmap_lazy_delete(map);
	map->entries = ne;
	map->count = new_count;
	return 0;

go_error_exit:
	return -1;
}

void _wh_hashmap_lazy_insert(_wh_hashmap_lazy_insert_params params) {
	u64 hash = wh_hash_simple(params.key, params.map->count);
	wh_hashmap_lazy_entry_s* e = nullptr;
	void* data = nullptr;

	e = _wh_hashmap_entry(params.map->entries, params.map->data_size, hash);

	if (nullptr != e->key) {
		if (!strcmp(e->key, params.key)) {
				wh_log_error(("Failed resize of hashmap, same key given twice [ %s ] skipping..."), e->key);
				return;
			}

		if (0 != _wh_hashmap_lazy_resize(params.map)) {
			return;
		}
	
		hash = wh_hash_simple(params.key, params.map->count);
		e = _wh_hashmap_entry(params.map->entries, params.map->data_size, hash);
	}

	data = wh_ptr_add(e, sizeof(wh_hashmap_lazy_entry_s));

	e->key = params.key;
	memcpy(data, params.data, params.map->data_size);
}

void* _wh_hashmap_lazy_get(_wh_hashmap_lazy_get_params params) {
	void* out = nullptr;
	u64 hash = wh_hash_simple(params.key, params.map->count);
	out = _wh_hashmap_entry(params.map->entries, params.map->data_size, hash);
	out = wh_ptr_add(out, sizeof(wh_hashmap_lazy_entry_s));
	return out;
}
