#include<wh/debug/logger.h>
#include<wh/data/list.h>
#include<wh/maths/memory.h>

#include<wh/debug/logger.h>
#include<wh-sys/memreq.h>
#include<wh-posix/unistd.h>
#include<wh-data/list.h>

#include<string.h>
#include<stdlib.h>
#include<stdio.h>

// Functions using the memory allocator
static int8_t _wh_sys_list_single_init(wh_list_s* out, _wh_sys_list_init_params* params);
static int8_t _wh_sys_list_double_init(wh_list_s* out, _wh_sys_list_init_params* params);

// Functions not using the memory allocator, but the system memory directly.
static int8_t _wh_sys_list_single_memreq_init(wh_list_s* out, _wh_sys_list_init_params* params);
static int8_t _wh_sys_list_double_memreq_init(wh_list_s* out, _wh_sys_list_init_params* params);

static i8 _wh_get_index_sll (wh_list_s* list, u64 index, void** current, void** previous);
static i8 _wh_get_index_dll (wh_list_s* list, u64 index, void** current, void** previous);

static void* _wh_data_sll(void* node);
static void* _wh_data_dll(void* node);

static void* _wh_list_search_sll(_wh_list_search_params* params);
static void* _wh_list_search_dll(_wh_list_search_params* params);

int8_t _wh_sys_list_single_stdlib_init(wh_list_s* out, _wh_sys_list_init_params* params);

// Including private C files
#include"_list/wolfhound.c"
#include"_list/mmap.c"

#include"_list/dll_stdlib.c"
#include"_list/sll_stdlib.c"

int8_t (*_wh_internal_sys_list_init[])(wh_list_s* out, _wh_sys_list_init_params* params) = {
	&_wh_sys_list_single_init,
	&_wh_sys_list_double_init,

	&_wh_sys_list_single_memreq_init,
	&_wh_sys_list_double_memreq_init,

	&_wh_sys_list_single_stdlib_init,
	&_wh_sys_list_double_stdlib_init,
	nullptr,
};

static i8 (*_wh_get_index[]) (wh_list_s* list, u64 index, void** current, void** previous) = {
	&_wh_get_index_sll,
	&_wh_get_index_dll,

	&_wh_get_index_sll,
	&_wh_get_index_dll,

	&_wh_get_index_sll,
	&_wh_get_index_dll,
	nullptr,
};

static void* (*_wh_data[]) (void* node) = {
	&_wh_data_sll,
	&_wh_data_dll,

	&_wh_data_sll,
	&_wh_data_dll,

	&_wh_data_sll,
	&_wh_data_dll,
};

static void (*_wh_insert[]) (_wh_sys_list_insert* params, void* current, void* previous) = {
	nullptr,
	nullptr,

	nullptr,
	nullptr,

	&_wh_insert_sll_stdlib,
	&_wh_insert_dll_stdlib,
};

static void* (*_wh_search[])(_wh_list_search_params* params) = {
	&_wh_list_search_sll,
	&_wh_list_search_dll,

	&_wh_list_search_sll,
	&_wh_list_search_dll,

	&_wh_list_search_sll,
	&_wh_list_search_dll,
};

static i8 (*_wh_list_alloc[])(wh_list_s* out, u64 count) = {
	&_wh_internal_sys_list_alloc_wolfhound,
	&_wh_internal_sys_list_alloc_wolfhound,

	&_wh_internal_sys_list_alloc_memreq,
	&_wh_internal_sys_list_alloc_memreq,

	//&_wh_alloc_stdlib,
	//&_wh_alloc_stdlib,
	nullptr,
	nullptr,
};

void* _wh_list_search(_wh_list_search_params params) {
	u64 func_index = 0;

	if (nullptr == params.ptr) {
		wh_log_warning(("No search item provided!"));
		return nullptr;
	}

	func_index = ((u64)params.list->stype) - WH_STRUCT_TYPE_LLIST_SINGLE;

	return _wh_search[func_index](&params);
}

i8 _wh_s2_list_insert(_wh_sys_list_insert params) {
	void* current = nullptr;
	void* previous = nullptr;
	u64 func_index = 0;

	if (nullptr == params.data) {
		wh_log_warning(("Provided data is a Nullptr"));
		goto go_error_exit;
	}

	func_index = ((u64)params.list->stype) - WH_STRUCT_TYPE_LLIST_SINGLE;

	if (0 == _wh_get_index[func_index](params.list, params.index, &current, &previous)) {
		_wh_insert[func_index](&params, current, previous);
		++params.list->node_count;
	} else {
		wh_log_error(("Failed to get list index!"));
		goto go_error_exit;
	}

	return 0;
go_error_exit:
	return -1;
}

void* _wh_s2_list_get(_wh_s2_list_get_params params) {
	void* current = nullptr;
	void* previous = nullptr;
	u64 func_index = 0;

	func_index = ((u64)params.list->stype) - WH_STRUCT_TYPE_LLIST_SINGLE;

	if (0 == _wh_get_index[func_index](params.list, params.index, &current, &previous)) {
		if (nullptr == current) {
			current = params.list->tail;
		}

		return _wh_data[func_index](current);
	}

	return nullptr;
}


int8_t _wh_sys_list_single_init(wh_list_s* out, _wh_sys_list_init_params* params) {
	return 0;
}


int8_t _wh_sys_list_double_init(wh_list_s* out, _wh_sys_list_init_params* params) {
	return 0;
}

int8_t _wh_sys_list_single_memreq_init(wh_list_s* out, _wh_sys_list_init_params* params) {
	return 0;
}

int8_t _wh_sys_list_double_memreq_init(wh_list_s* out, _wh_sys_list_init_params* params) {
	return 0;
}

int8_t _wh_sys_list_single_stdlib_init(wh_list_s* out, _wh_sys_list_init_params* params) {
	return 0;
}

static i8 _wh_alloc_stdlib(wh_list_s* out, u64 count) {
	return 0;
}

wh_list_s _wh_sys_list_init(i64 list_type, _wh_sys_list_init_params params) {
	wh_list_s out = { 0 };

	if (WH_STRUCT_TYPE_LLIST_SINGLE > list_type || WH_STRUCT_TYPE_LLIST_STD_DOUBLE < list_type) {
		wh_log_critical(("Provided list type are not supported by wh_list_s"));
		goto go_error_exit;
	}

	out.stype = list_type;
	out.type_size = params.type_size;
	out.node_count = 0;
	_wh_internal_sys_list_init[list_type - WH_STRUCT_TYPE_LLIST_SINGLE](&out, &params);

go_error_exit:
	return out;
}
