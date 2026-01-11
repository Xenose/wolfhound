#include<wh/memory/garbage.h>

typedef struct {
	void* owner;
	char* file_name;
} _wh_track_owner;

typedef struct {
	void* ptr;

	u64 owner_count;
	_wh_track_owner* owners;
} _wh_track_entry;

typedef struct {
	atomic_bool locked;
	u64 _count;
	_wh_track_entry* _entires;
} _wh_tracker;

static _wh_tracker _tracker;

void _wh_mem_track_add(void* ptr, void* owner) {
}

void _wh_mem_track_remove_owners(void* ptr, ...) {
}

void _wh_mem_track_remove(void* ptr) {
}


void* _wh_mem_alloc_garbage(_wh_mem_alloc_params params) {
	void* ptr = nullptr;

	if (nullptr != (ptr = _wh_mem_alloc(params))) {
		_wh_mem_track_add(ptr, params.owner);
	}

	return ptr;
}

i8 _wh_mem_init_grabage() {
	return 0;
}
