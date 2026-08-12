#include<wh/data/list.h>
#include<wh/maths/memory.h>
#include<wh-sys/memreq.h>
#include<wh/data/list.h>
#include<wh/debug/logger.h>
#include<wh-posix/unistd.h>

static i8 _wh_internal_sys_list_alloc_memreq(wh_list_s* out, u64 count) {
	void* new_data = nullptr;
	i64 pagesize = (i64)sysconf(_SC_PAGESIZE);
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
