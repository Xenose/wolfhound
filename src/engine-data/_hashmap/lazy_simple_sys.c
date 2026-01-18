#include<wh-data/hashmap.h>
#include<wh-maths/memory.h>
#include<wh-posix/string.h>
#include<wh-posix/unistd.h>
#include<wh-sys/memreq.h>
#include<wh/debug/logger.h>
#include<wh-maths/core.h>

static void* _reallocate_lazy_simple_sys(wh_hashmap_s* map) {
	wh_hashmap_slot_string_s* slots = 0; 

	u64 hash_index = 0;
	u64 mem_needed = 0;
	u64 new_alloc_size = 0;
	u64 new_slot_count = 0;
	wh_hashmap_slot_string_s* new_slots = nullptr;

go_retry_resize:
	// Calculating the needed memory and aligning it to page size and the new slot count.
	mem_needed = (map->resize_size + 1) * (map->type_size * sizeof(wh_hashmap_slot_string_s));
	new_alloc_size = (u64)wh_align((i64)mem_needed, getpagesize());
	new_slot_count = new_alloc_size / (map->type_size * sizeof(wh_hashmap_slot_string_s));

	// Requesting the OS for memory.
	new_slots = wh_sys_memreq(new_alloc_size);

	if (nullptr == new_slots) {
		wh_log_critical(("Failed to allocated memory from the system!"));
		goto go_error_exit;
	}

	slots = map->slots;
	memset(new_slots, 0, new_alloc_size);

	wh_for(u64, i, map->slot_count) {
		if (nullptr != slots[i].data) {
			hash_index = (u64)wh_hash_simple(slots[i].key, (i64)new_slot_count);

			if (nullptr == new_slots[hash_index].data) {
				wh_sys_memrel(new_slots, new_alloc_size);
				goto go_retry_resize;
			}

			new_slots[hash_index].data = slots[i].data;
			new_slots[hash_index].key = slots[i].key;
		}
	}

go_error_exit:
	return nullptr;
}

static i8 _insert_lazy_simple_sys(wh_hashmap_s* map, void* value) {
	return 0;
}
