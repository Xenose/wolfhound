#include<wh/debug/logger.h>
#include<wh/data/list.h>
#include<wh/maths/memory.h>

#include<wh/debug/logger.h>
#include<wh-sys/memreq.h>
#include<wh-posix/unistd.h>

// Functions using the memory allocator
int8_t _wh_sys_list_single_init(wh_list_s* out, i64 list_type);
int8_t _wh_sys_list_double_init(wh_list_s* out, i64 list_type);

// Functions not using the memory allocator, but the system memory directly.
int8_t _wh_sys_list_single_memreq_init(wh_list_s* out, i64 list_type);
int8_t _wh_sys_list_double_memreq_init(wh_list_s* out, i64 list_type);

// Functions using stdlib malloc instead of the provided allocator.
int8_t _wh_sys_list_single_stdlib_init(wh_list_s* out, i64 list_type);
int8_t _wh_sys_list_double_stdlib_init(wh_list_s* out, i64 list_type);

void _wh_internal_sys_list_get_index_sll (wh_list_s* list, u64 index, void** current, void** previous);
void _wh_internal_sys_list_get_index_dll (wh_list_s* list, u64 index, void** current, void** previous);

// Functions for allocations
i8 _wh_internal_sys_list_alloc_wolfhound(wh_list_s* out, u64 count);
i8 _wh_internal_sys_list_alloc_memreq(wh_list_s* out, u64 count);
i8 _wh_internal_sys_list_alloc_stdlib(wh_list_s* out, u64 count);

int8_t (*_wh_internal_sys_list_init[])(wh_list_s* out, i64 list_type) = {
	&_wh_sys_list_single_init,
	&_wh_sys_list_double_init,

	&_wh_sys_list_single_memreq_init,
	&_wh_sys_list_double_memreq_init,

	&_wh_sys_list_single_stdlib_init,
	&_wh_sys_list_double_stdlib_init,
	nullptr,
};

void (*_wh_internal_sys_list_get_index[]) (wh_list_s* list, u64 index, void** current, void** previous) = {
	&_wh_internal_sys_list_get_index_sll,
	&_wh_internal_sys_list_get_index_dll,

	&_wh_internal_sys_list_get_index_sll,
	&_wh_internal_sys_list_get_index_dll,

	&_wh_internal_sys_list_get_index_sll,
	&_wh_internal_sys_list_get_index_dll,
	nullptr,
};

void (*_wh_internal_sys_list_insert[]) (wh_list_s* list, void* current, void* previous) = {
	nullptr,
};

i8 (*_wh_internal_sys_list_alloc[])(wh_list_s* out, u64 count) = {
	&_wh_internal_sys_list_alloc_wolfhound,
	&_wh_internal_sys_list_alloc_wolfhound,

	&_wh_internal_sys_list_alloc_memreq,
	&_wh_internal_sys_list_alloc_memreq,

	&_wh_internal_sys_list_alloc_stdlib,
	&_wh_internal_sys_list_alloc_stdlib,
	nullptr,
};

i8 _wh_internal_sys_list_alloc_wolfhound(wh_list_s* out, u64 count) {
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

i8 _wh_internal_sys_list_alloc_memreq(wh_list_s* out, u64 count) {
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

void _wh_internal_sys_list_get_index_sll (wh_list_s* list, u64 index, void** current, void** previous) {
	wh_sllist_item_s* c = *current;

	for (c = list->head; c != nullptr && 0 < index; *c = *c->p_next, index--);
}

void _wh_internal_sys_list_get_index_dll (wh_list_s* list, u64 index, void** current, void** previous) {
	wh_dllist_item_s* c = *current;
	u64 midpoint = list->node_count / 2;
	if (index > midpoint) {
		_wh_internal_sys_list_get_index_sll(list, index, current, previous);
	} else {
		index = index - midpoint;
		for (c = list->tail; c != nullptr && 0 < index; *c = *c->p_previous, index--);
	}

	*current = c;
	*previous = c->p_previous;
}

void _wh_internal_sys_list_insert_dll(wh_list_s* list, void* current, void* previous, void* node) {
	wh_dllist_item_s* c = current;
	wh_dllist_item_s* p = previous;
	wh_dllist_item_s* n = node;

	c->p_previous = node;
	p->p_next = node;

	n->p_next = c;
	n->p_previous = p;
}

i8 _wh_sys_list_add(wh_list_s* list, void* item, u64 index) {
	void* current = nullptr;
	void* previous = nullptr;

	u64 func_index = 0;
	u64 alloc_size = 0;

	if (nullptr == item) {
		wh_log_notice(("Provided a pointer pointing to [ nullptr ], ingoring addition."));
		goto go_error_exit;
	}

	if (nullptr == list->head) {
		wh_log_critical(("Broken list provided! Head [ %u ] Tail [ %u ]"), list->head, list->tail);
		goto go_error_exit;
	}

	func_index = ((u64)list->stype) - WH_STRUCT_TYPE_LLIST_SINGLE;
	alloc_size = list->type_size + sizeof(wh_dllist_item_s);

	if (alloc_size > list->sysmem.free) {
		if (0 != _wh_internal_sys_list_alloc[func_index](list, alloc_size)) {
			wh_log_critical(("Failed to relloac the list!"));
			goto go_error_exit;
		}
	}

	_wh_internal_sys_list_get_index[func_index](list, index, &current, &previous);
	_wh_internal_sys_list_insert[func_index](item, &current, &previous);
	
	list->sysmem.free -= alloc_size;
	//last = list->tail;

	return 0;
go_error_exit:
	return -1;
}

void* _wh_sys_list_get(wh_list_s* list, u64 index) {
	return nullptr;
}

/// Init blocks

int8_t _wh_sys_list_single_init(wh_list_s* out, i64 list_type) {
	return 0;
}


int8_t _wh_sys_list_double_init(wh_list_s* out, i64 list_type) {
	return 0;
}

int8_t _wh_sys_list_single_memreq_init(wh_list_s* out, i64 list_type) {
	return 0;
}

int8_t _wh_sys_list_double_memreq_init(wh_list_s* out, i64 list_type) {
	return 0;
}

int8_t _wh_sys_list_single_stdlib_init(wh_list_s* out, i64 list_type) {
	return 0;
}


int8_t _wh_sys_list_double_stdlib_init(wh_list_s* out, i64 list_type) {
	return 0;
}

wh_list_s _wh_sys_list_init(i64 list_type, u64 type_size) {
	wh_list_s out = { 0 };

	out.stype = list_type;
	out.type_size = type_size;

	_wh_internal_sys_list_init[list_type - WH_STRUCT_TYPE_LLIST_SINGLE](&out, list_type);

	return out;
}
