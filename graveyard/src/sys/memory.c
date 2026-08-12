#include <wh-posix/stdlib.h>
#include <wh-posix/string.h>


// my stuff
#include <wh/maths/core.h>
#include <wh/maths/memory.h>
#include <wh-posix/stdatomic.h>
#include <wh-posix/unistd.h>
#include <wh-sys/atomic_lock.h>
#include <wh-sys/memory.h>
#include <wh-sys/memreq.h>
#include <wh/debug/logger.h>
#include <wh/memory/arena.h>
#include <wh/memory/freelist.h>

WH_DEPRECATED("DON'T USE THIS FUNCTION!")
void* _wh_mem(_wh_mem_params params) {
	void* ptr = nullptr;

	if (0 == params.bytes) {
		if (nullptr != params.ptr) {
			if (WH_MEM_ZERO == params.flags) {
				memset(params.ptr, 0, params.bytes);
			}

			//atomic_fetch_sub(&_heap_main->ptr_count, 1);
			free(params.ptr);
		}

		goto go_exit;
	}

	if (nullptr == params.ptr) {
		ptr = malloc(params.bytes);
	} else {
		ptr = realloc(params.ptr, params.bytes);
	}

	if (nullptr == ptr) {
		goto go_failure_exit;
	}

	if (nullptr == params.ptr) {
		//atomic_fetch_add(&_heap_main->ptr_count, 1);
	}

	if (WH_MEM_ZERO == params.flags) {
		memset(ptr, 0, params.bytes);
	}

go_failure_exit:
go_exit:
	return ptr;
}
