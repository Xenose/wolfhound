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
	wh_hashmap_slot_string_s* slots = nullptr; 
	wh_hashmap_slot_string_s* new_slots = nullptr;

	u64 hash_index = 0;
	u64 new_slot_count = 0;

go_retry_resize:
	// Calculating the needed memory and aligning it to page size and the new slot count.
	map->resize_size = (u64)wh_align((i64)map->resize_size + 1, getpagesize());
	new_slot_count = map->resize_size / (map->type_size * sizeof(wh_hashmap_slot_string_s));

	wh_log_debug(("Slot count %i [ %i -> %i ]"), new_slot_count, map->slot_count, new_slot_count);
	// Requesting the OS for memory.
	new_slots = wh_sys_memreq(map->resize_size);

	if (nullptr == new_slots) {
		wh_log_critical(("Failed to allocated memory from the system!"));
		goto go_error_exit;
	}

	slots = map->slots;
	memset(new_slots, 0, map->resize_size);

	wh_for(u64, i, map->slot_count) {
		if (nullptr != slots[i].key) {
			hash_index = (u64)wh_hash_simple(slots[i].key, (i64)new_slot_count);

			if (nullptr != new_slots[hash_index].key) {
				wh_sys_memrel(new_slots, map->resize_size);
				goto go_retry_resize;
			}

			memcpy(&new_slots[hash_index].data, &slots[i].data, map->type_size);
			new_slots[hash_index].key = slots[i].key;
			wh_log_debug(("--> Rehased postions [ %u ] [ %i ]"), hash_index, new_slots[hash_index].data);
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
	wh_hashmap_slot_string_s* slots = params->map->slots;

	if (nullptr == slots) {
		_reallocate_lazy_simple_sys(params->map);
		slots = params->map->slots;
	}

	hash = wh_hash_simple(params->key, (i64)params->map->slot_count);

	if (nullptr == slots[hash].key ? 0 : !strcmp(params->key, slots[hash].key)) {
		wh_log_error(("Inputed key and existing key is the same [ %s -> %s ]"),
			params->key, slots[hash].key);
		goto go_error_exit;
	}

	for (u32 i = 0; i < 3 && nullptr != slots[hash].key; i++) {
		wh_log_debug(("Hashmap size to small resizing!"));

		if (nullptr != _reallocate_lazy_simple_sys(params->map)) {
			slots = params->map->slots;
			hash = wh_hash_simple(params->key, (i64)params->map->slot_count);
			break;
		}
	}

	if (nullptr != slots[hash].key) {
		goto go_error_exit;
	}

	slots[hash].key = params->key;
	wh_log_debug(("New allocation assigned! [ %u ] [ hash : %i ] [ count : %i ]"), &slots[hash], hash, params->map->slot_count);
	memcpy(&slots[hash], params->value, params->map->type_size);

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
	wh_hashmap_slot_string_s* slots = map->slots;

	return &slots[hash].data;
}

i8 _wh_lazy_simple_foreach(wh_hashmap_s* map, void (*func)(void* value)) {
	wh_hashmap_slot_string_s* slots = map->slots;

	for (u64 i = 0; i < map->slot_count; i++) {
		if (nullptr != slots[i].key) {
			func(&slots[i].data);
		}
	}

	return 0;
}
