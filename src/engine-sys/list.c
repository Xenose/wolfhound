#include<wh/debug/logger.h>
#include<wh/data/list.h>
#include<wh/maths/memory.h>

#include<wh-sys/memreq.h>
#include<wh-posix/unistd.h>

// Functions using the memory allocator
int8_t _wh_sys_llist_single_init(wh_list_s* out, i64 list_type);
int8_t _wh_sys_llist_double_init(wh_list_s* out, i64 list_type);

// Functions not using the memory allocator, but the system memory directly.
int8_t _wh_sys_llist_single_memreq_init(wh_list_s* out, i64 list_type);
int8_t _wh_sys_llist_double_memreq_init(wh_list_s* out, i64 list_type);

// Functions using stdlib malloc instead of the provided allocator.
int8_t _wh_sys_llist_single_stdlib_init(wh_list_s* out, i64 list_type);
int8_t _wh_sys_llist_double_stdlib_init(wh_list_s* out, i64 list_type);

int8_t (*_wh_internal_sys_llist_init[])(wh_list_s* out, i64 list_type) = {
	&_wh_sys_llist_single_init,
	&_wh_sys_llist_double_init,
	&_wh_sys_llist_single_memreq_init,
	&_wh_sys_llist_double_memreq_init,
	&_wh_sys_llist_single_stdlib_init,
	&_wh_sys_llist_single_stdlib_init,
};

i8 (*_wh_internal_sys_llist_realloc[])(wh_list_s* out) = {
	nullptr,
};

i8 _wh_internal_sys_list_realloc_mmap(wh_list_s* out) {
	void* new_data = nullptr;
	i64 pagesize = (i64)getpagesize();
	u64 new_size = (u64)wh_align((i64)out->sysmem.size + pagesize, pagesize); 

	union {
		void* ptr;
		wh_sllist_item_s* sl;
		wh_dllist_item_s* dl;
	} node;

	node.ptr = out->tail;
	new_data = wh_sys_memreq(new_size);

	if (nullptr == new_data) {
		wh_log_error(("Failed to relloacte list memory! of size [ %u ]"), new_size);
		goto go_error_exit;
	}

	switch(out->stype) {
		case WH_STRUCT_TYPE_LLIST_SYS_SINGLE:
			node.sl->p_next = new_data;
			break;
		case WH_STRUCT_TYPE_LLIST_SYS_DOUBLE:
			node.dl->p_next = new_data;
			break;
		default:
			goto go_error_exit_free;
	}

	out->tail = new_data;

	return 0;
go_error_exit_free:
	wh_sys_memrel(new_data, new_size);
go_error_exit:
	return -1;
}

i8 _wh_sys_list_add(wh_list_s* list, void* item) {
	wh_dllist_item_s* last = nullptr;

	if (nullptr == item) {
		wh_log_notice(("Provided a pointer pointing to [ nullptr ], ingoring addition."));
		goto go_error_exit;
	}

	if ((list->type_size + sizeof(wh_dllist_item_s)) > list->sysmem.free) {
		if (0 != _wh_internal_sys_llist_realloc[list->stype - WH_STRUCT_TYPE_LLIST_SINGLE](list)) {
			wh_log_error(("Failed to relloac the llist!"));
			goto go_error_exit;
		}
	}

	list->sysmem.free -= (list->type_size + sizeof(wh_dllist_item_s));
	last = list->tail;

	return 0;
go_error_exit:
	return -1;
}

void* _wh_sys_list_get(wh_list_s* list, u64 index) {
	return nullptr;
}

/// Init blocks

int8_t _wh_sys_llist_single_init(wh_list_s* out, i64 list_type) {
	return 0;
}

int8_t _wh_sys_llist_double_init(wh_list_s* out, i64 list_type) {
	return 0;
}

wh_list_s _wh_sys_llist_init(i64 list_type, u64 type_size) {
	wh_list_s out = { 0 };

	out.stype = list_type;
	out.type_size = type_size;

	_wh_internal_sys_llist_init[list_type - WH_STRUCT_TYPE_LLIST_SINGLE](&out, list_type);

	return out;
}
