#include<wh/debug/logger.h>
#include<wh/data/list.h>
#include<wh/maths/memory.h>

#include<wh/debug/logger.h>
#include<wh-sys/memreq.h>
#include<wh-posix/unistd.h>
#include<wh-sys/list.h>

#include<string.h>
#include<stdlib.h>

// Functions using the memory allocator
static int8_t _wh_sys_list_single_init(wh_list_s* out, _wh_sys_list_init_params* params);
static int8_t _wh_sys_list_double_init(wh_list_s* out, _wh_sys_list_init_params* params);

// Functions not using the memory allocator, but the system memory directly.
static int8_t _wh_sys_list_single_memreq_init(wh_list_s* out, _wh_sys_list_init_params* params);
static int8_t _wh_sys_list_double_memreq_init(wh_list_s* out, _wh_sys_list_init_params* params);

// Functions using stdlib malloc instead of the provided allocator.
static int8_t _wh_sys_list_single_stdlib_init(wh_list_s* out, _wh_sys_list_init_params* params);
static int8_t _wh_sys_list_double_stdlib_init(wh_list_s* out, _wh_sys_list_init_params* params);

static i8 _wh_get_index_sll (wh_list_s* list, u64 index, void** current, void** previous);
static i8 _wh_get_index_dll (wh_list_s* list, u64 index, void** current, void** previous);

static void* _wh_data_sll(void* node);
static void* _wh_data_dll(void* node);

static void _wh_insert_sll_stdlib (_wh_sys_list_insert* params, void* current, void* previous);
static void _wh_insert_dll_stdlib(_wh_sys_list_insert* params, void* current, void* previous);

// Functions for allocations
static i8 _wh_internal_sys_list_alloc_wolfhound(wh_list_s* out, u64 count);
static i8 _wh_internal_sys_list_alloc_memreq(wh_list_s* out, u64 count);
static i8 _wh_alloc_stdlib(wh_list_s* out, u64 count);

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

static i8 (*_wh_list_alloc[])(wh_list_s* out, u64 count) = {
	&_wh_internal_sys_list_alloc_wolfhound,
	&_wh_internal_sys_list_alloc_wolfhound,

	&_wh_internal_sys_list_alloc_memreq,
	&_wh_internal_sys_list_alloc_memreq,

	&_wh_alloc_stdlib,
	&_wh_alloc_stdlib,
	nullptr,
};

static i8 _wh_internal_sys_list_alloc_wolfhound(wh_list_s* out, u64 count) {
	void* new_data = nullptr;
	union {
		void* ptr;
		wh_sllist_item_s* sl;
		wh_dllist_item_s* dl;
	} node;

	switch(out->stype) {
		case WH_STRUCT_TYPE_LLIST_SYS_SINGLE:
			node.sl->p_next = new_data;
			break;
		case WH_STRUCT_TYPE_LLIST_SYS_DOUBLE:
			node.dl->p_next = new_data;
			break;
	}

	return 0;
}

static i8 _wh_internal_sys_list_alloc_memreq(wh_list_s* out, u64 count) {
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

static i8 _wh_alloc_stdlib(wh_list_s* out, u64 count) {
	return 0;
}

static void* _wh_data_sll(void* node) {
	wh_sllist_item_s* n = node;
	return n->data;
}

static void* _wh_data_dll(void* node) {
	wh_dllist_item_s* n = node;
	return n->data;
}

static i8 _wh_get_index_sll(wh_list_s* list, u64 index, void** current, void** previous) {
	wh_sllist_item_s* p = nullptr;
	wh_sllist_item_s* c = list->head;

	if (index >= list->node_count) {
		goto go_error_exit;
	}

	while (0 < index--) {
		p = c;
		c = c->p_next;
	}

	*current = c;
	*previous = p;
	return 0;

go_error_exit:
	*current = nullptr;
	*previous = nullptr;
	return -1;
}

static i8 _wh_get_index_dll (wh_list_s* list, u64 index, void** current, void** previous) {
	wh_dllist_item_s* c = nullptr; 
	u64 midpoint = (list->node_count + 2) / 2;

	if (index > list->node_count) {
		wh_log_error(("Index outside list range"));
		goto go_error_exit;
	}

	if (index < midpoint) {
		wh_log_debug(("Mid point less then index!"));
		c = list->head;

		while (0 < index--) {
			c = c->p_next;
		}

	} else {
		wh_log_debug(("Mid point more then index!"));
		c = list->tail;
		index = list->node_count - (index);

		while (0 < index--) {
			c = c->p_previous;
		}
	}

	if (nullptr != c) {
		*previous = c->p_previous;
	}

	*current = c;
	wh_log_debug(("Node location found!"));
	return 0;

go_error_exit:
	*current = nullptr;
	*previous = nullptr;
	return -1;
}

static void _wh_insert_sll(_wh_sys_list_insert* params, void* current, void* previous, void* node) {
	wh_sllist_item_s* c = current;
	wh_sllist_item_s* p = previous;
	wh_sllist_item_s* n = node;

	if (nullptr != p) {
		p->p_next = node;
	}
	n->p_next = c;
}

static void _wh_insert_dll(_wh_sys_list_insert* params, void* current, void* previous, void* node) {
	wh_dllist_item_s* c = current;
	wh_dllist_item_s* p = previous;
	wh_dllist_item_s* n = node;

	n->p_next = c;
	n->p_previous = p;

	if (nullptr != c) {
		c->p_previous = node;
	} else {
		params->list->tail = node;
	}

	if (nullptr != p) {
		p->p_next = node;
	} else {
		params->list->head = node;
	}
}

static void _wh_insert_sll_stdlib(_wh_sys_list_insert* params, void* current, void* previous) {
	wh_sllist_item_s* node = calloc(1, sizeof(wh_sllist_item_s));

	if (nullptr == node) {
		wh_log_error(("Failed to allocated node!"));
	}

	node->data = calloc(1, params->list->type_size);

	if (nullptr == node->data) {
		wh_log_error(("Failed to allocated node data!"));
	}

	memcpy(node->data, params->data, params->list->type_size);
	_wh_insert_sll(params, current, previous, node);
	wh_log_debug(("Inserted item into single std linked list!"));
}

static void _wh_insert_dll_stdlib(_wh_sys_list_insert* params, void* current, void* previous) {
	wh_dllist_item_s* node = calloc(1, sizeof(wh_dllist_item_s));

	wh_log_debug(("Function entered!"));

	if (nullptr == node) {
		wh_log_error(("Failed to allocated node!"));
	}

	node->data = calloc(1, params->list->type_size);

	if (nullptr == node->data) {
		wh_log_error(("Failed to allocated node data!"));
	}

	memcpy(node->data, params->data, params->list->type_size);
	_wh_insert_dll(params, current, previous, node);
	wh_log_debug(("Inserted item into double std linked list!"));
}

i8 _wh_s2_list_insert(_wh_sys_list_insert params) {
	void* current = nullptr;
	void* previous = nullptr;
	u64 func_index = 0;

	if (nullptr == params.data) {
		wh_log_warning(("Provided data is a Nullptr"));
		goto go_error_exit;
	}

	wh_log_debug(("Generating function index..."));
	func_index = ((u64)params.list->stype) - WH_STRUCT_TYPE_LLIST_SINGLE;

	if (0 == _wh_get_index[func_index](params.list, params.index, &current, &previous)) {
		_wh_insert[func_index](&params, current, previous);
		++params.list->node_count;
	} else {
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
		return _wh_data[func_index](current);
	}

	return nullptr;
}

/// Init blocks

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


int8_t _wh_sys_list_double_stdlib_init(wh_list_s* out, _wh_sys_list_init_params* params) {
	wh_log_debug(("Hello!"));
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
	_wh_internal_sys_list_init[list_type - WH_STRUCT_TYPE_LLIST_SINGLE](&out, &params);

go_error_exit:
	return out;
}
