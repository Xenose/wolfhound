#include<wh-data/hashmap.h>
#include<wh-maths/memory.h>
#include<wh-posix/string.h>
#include<wh-posix/unistd.h>
#include<wh-sys/memreq.h>
#include<wh/debug/logger.h>
#include<wh-maths/core.h>

/*
 * Lazy hashmap is designed to be a collision free hashmap,
 * meaning on collision we resize this might not be the best
 * in all cases but very useful in some cases.
 *
 * Look up speed o(1), realloc speed o(n).
 */
static void* _reallocate_lazy_simple_sys(wh_hashmap_s* map) {
	void* data = nullptr;
	u64 bytes = sizeof(wh_hashmap_slot_string_s) + map->type_size;

	wh_hashmap_slot_string_s* slots = nullptr; 
	wh_hashmap_slot_string_s* new_slots = nullptr;

	u64 hash_index = 0;
	u64 new_slot_count = 0;

go_retry_resize:
	// Calculating the needed memory and aligning it to page size and the new slot count.
	map->resize_size = (u64)wh_align((i64)map->resize_size + 1, getpagesize());
	new_slot_count = map->resize_size / (map->type_size + sizeof(wh_hashmap_slot_string_s));

	wh_log_debug(("Slot count %i [ %i -> %i ]"), new_slot_count, map->slot_count, new_slot_count);
	// Requesting the OS for memory.
	new_slots = wh_sys_memreq(map->resize_size);

	if (nullptr == new_slots) {
		wh_log_critical(("Failed to allocated memory from the system!"));
		goto go_error_exit;
	}

	memset(new_slots, 0, map->resize_size);

	wh_for(u64, i, map->slot_count) {
		wh_hashmap_slot_string_s* src = wh_ptr_offset(slots, i * bytes);

		if (nullptr != src->key) {
			hash_index = (u64)wh_hash_simple(src->key, (i64)new_slot_count);

			if (nullptr != new_slots[hash_index].key) {
				wh_sys_memrel(new_slots, map->resize_size);
				goto go_retry_resize;
			}
			
			wh_hashmap_slot_string_s* dst = wh_ptr_offset(new_slots, hash_index * bytes);

			memcpy(dst, src, map->type_size);
			dst->key = src->key;
			wh_log_debug(("--> Rehased postions [ %u ] [ %i ]"), hash_index, dst);
		}
	}

	map->slots = new_slots;
	map->slot_count = new_slot_count;
	wh_log_debug(("New allocation assigned! [ %u ] [ %i ]"), map->slots, map->slot_count);
	
	return map->slots;
go_error_exit:
	return nullptr;
}

static i8 _insert_lazy_simple_sys(_wh_hashmap_insert_params* params) {
	i64 hash = 0;
	u64 bytes = sizeof(wh_hashmap_slot_string_s) + params->map->type_size;
	wh_hashmap_slot_string_s* slots = params->map->slots;
	wh_hashmap_slot_string_s* dst = nullptr;

	if (nullptr == slots) {
		slots = _reallocate_lazy_simple_sys(params->map);
	}

	hash = wh_hash_simple(params->key, (i64)params->map->slot_count);
	dst = wh_ptr_offset(slots, (u64)hash * bytes);

	if (nullptr == dst->key ? 0 : !strcmp(params->key, dst->key)) {
		wh_log_error(("Inputed key and existing key is the same [ %s -> %s ]"),
			params->key, dst->key);
		goto go_error_exit;
	}

	for (u32 i = 0; i < 3 && nullptr != dst->key; i++) {
		wh_log_debug(("Hashmap size to small resizing!"));

		if (nullptr != _reallocate_lazy_simple_sys(params->map)) {
			slots = params->map->slots;
			hash = wh_hash_simple(params->key, (i64)params->map->slot_count);
			dst = wh_ptr_offset(slots, (u64)hash * bytes);
			break;
		}
	}

	if (nullptr != dst->key) {
		goto go_error_exit;
	}

	dst->key = params->key;
	wh_log_debug(("New allocation assigned! [ %u ] [ hash : %i ] [ count : %i ]"), dst, hash, params->map->slot_count);
	memcpy(wh_ptr_add(dst, sizeof(wh_hashmap_slot_string_s)), params->value, params->map->type_size);

	return 0;
go_error_exit:
	return -1;
}

static i8 _insert_lazy_simple_sys_strig(_wh_hashmap_insert_params params) {
	//return _insert_lazy_simple_sys(&params, hash);
}

static i8 _delete_lazy_simple_sys(wh_hashmap_s* map, void* key) {
	i64 hash = wh_hash_simple(key, (i64)map->slot_count);
	wh_hashmap_slot_string_s* slots = map->slots;
	
	slots[hash].key = nullptr;
	return 0;
}

static void* _get_lazy_simple_sys(wh_hashmap_s* map, void* key) {
	i64 hash = wh_hash_simple(key, (i64)map->slot_count);
	u64 bytes = sizeof(wh_hashmap_slot_string_s) + map->type_size;
	wh_hashmap_slot_string_s* src = wh_ptr_offset(map->slots, (u64)hash * bytes);

	return wh_ptr_add(src, sizeof(wh_hashmap_slot_string_s));
}

i8 _wh_lazy_simple_foreach(wh_hashmap_s* map, void (*func)(void* value)) {
	u64 bytes = sizeof(wh_hashmap_slot_string_s) + map->type_size;
	wh_hashmap_slot_string_s* src = nullptr;

	for (u64 i = 0; i < map->slot_count; i++) {
		src = wh_ptr_offset(map->slots, (u64)i * bytes);

		if (nullptr != src->key) {
			func(wh_ptr_offset(src, sizeof(wh_hashmap_slot_string_s)));
		}
	}

	return 0;
}
