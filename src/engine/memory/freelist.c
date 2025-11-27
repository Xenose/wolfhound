#include<wh/memory/freelist.h>
#include<wh/debug/logger.h>
#include<wh/maths/memory.h>

#include<string.h>

wh_heap_node_s* _wh_mem_alloc_freelist_head(_wh_mem_alloc_params* params, i64* error) {
	wh_heap_node_s* node = params->heap->freelist.nodes;

	while (node->flags & WH_MEM_IN_USE || node->bytes < params->bytes) {
		if (nullptr == node->next) {
			*error = WH_ERROR_HEAP_TOO_SMALL;
			wh_log_critical(("no node found!"));
			goto go_error_exit;
		}
		node = node->next;
	}

	wh_log_debug(("Node found!"));
	return node;
go_error_exit:
	wh_ptr_assign(params->error, *error);
	return nullptr;
}

wh_heap_node_s* _wh_mem_alloc_freelist_tail(_wh_mem_alloc_params* params, i64* error) {
	wh_heap_node_s* node = params->heap->freelist.tail;

	while (node->flags & WH_MEM_IN_USE || node->bytes < params->bytes) {
		if (nullptr == node->previous) {
			*error = WH_ERROR_HEAP_TOO_SMALL;
			wh_log_critical(("no node found!"));
			goto go_error_exit;
		}
		node = node->previous;
	}

	return node;
go_error_exit:
	wh_ptr_assign(params->error, *error);
	return nullptr;
}

void* _wh_mem_alloc_freelist(_wh_mem_alloc_params* params)  {
	i64 error = 0;
	void* out = nullptr;
	wh_heap_node_s* node = nullptr;

	if (nullptr == params->heap->freelist.nodes || nullptr == params->heap->freelist.tail) {
		error = WH_ERROR_NO_MEMORY;
		goto go_error_exit;
	}

	if (WH_ALLOC_TAIL & params->flags) {
		node = _wh_mem_alloc_freelist_tail(params, &error);
	} else {
		node = _wh_mem_alloc_freelist_head(params, &error);
	}

	if (nullptr == node) {
		goto go_error_exit;
	}

	// check if the nodes is big enough for a split
	if ((node->bytes - 64) > (params->bytes + sizeof(wh_heap_node_s))) {
		wh_heap_node_s* header = nullptr;
		u64 size = (u64)wh_align(params->bytes + sizeof(wh_heap_node_s), 64);
	
		wh_log_debug(("node is size [ $k ] currently and allocated size is [ $k ]"), node->bytes, size);

		if (WH_ALLOC_TAIL & params->flags) {
			header = wh_ptr_add(node, node->bytes - size);
			node->bytes = node->bytes - size;

			header->bytes = size; 
			header->data = wh_ptr_add(header, sizeof(wh_heap_node_s));
			header->flags = params->flags | WH_MEM_IN_USE;
			header->next = node->next;
			
			out = header->data;
		} else {
			header = wh_ptr_add(node, size);
			header->bytes = node->bytes - size; 

			node->bytes = size;
			node->data = wh_ptr_add(node, sizeof(wh_heap_node_s));
			node->flags = params->flags | WH_MEM_IN_USE;
			header->next = node->next;

			out = node->data;
		}

		params->heap->freelist.tail = header;
		header->previous = node;
		node->next = header;

		wh_log_debug(("Allocated [ $k ] new node created [ $k ] or [ %i : %i ]"), 
					node->bytes, header->bytes, node->bytes, header->bytes);
	}


	return out;
go_error_exit:
	wh_ptr_assign(params->error, error);
	wh_log_error(("Failed to allocate node!"));
	return nullptr;
}

wh_heap_node_s* _wh_mem_freelist_previous(_wh_mem_free_params* params, wh_heap_node_s* pn, wh_heap_node_s* cn) {
	if (nullptr != pn) {
		if (wh_not(WH_MEM_IN_USE & pn->flags)) {
			pn->next = cn->next;
			pn->bytes += cn->bytes;
			cn = _wh_mem_freelist_previous(params, pn->previous, pn);
		}
	}

	return cn;
}

void _wh_mem_freelist_next(_wh_mem_free_params* params, wh_heap_node_s* nn, wh_heap_node_s* cn) {
	if (nullptr != nn) {
		if (wh_not(WH_MEM_IN_USE & nn->flags)) {
			cn->bytes += nn->bytes;
			cn->next = nn->next;
			_wh_mem_freelist_next(params, nn->next, cn);
		}
	}
}

void _wh_mem_free_freelist(_wh_mem_free_params* params) {
	i64 error = 0;
	wh_heap_node_s* node = params->heap->freelist.nodes;

	if (nullptr == node) {
		error = WH_ERROR_NO_MEMORY;
		goto go_error_exit;
	}

	while (node->data != params->ptr) {
		if (nullptr == node->next) {
			wh_log_error(("Failed to find pointer next pointer is NULL"));
			goto go_error_exit;
		}

		node = node->next;
	}

	if (node->data == params->ptr) {
		wh_heap_node_s* pn = node->previous;
		wh_heap_node_s* nn = node->next;
		
		node->flags &= ~WH_MEM_IN_USE;
		node = _wh_mem_freelist_previous(params, pn, node);
		_wh_mem_freelist_next(params, nn, node);

		wh_log_info(("Found pointer! Freeing: heap size now is [ $k ]"), node->bytes);
	}

go_error_exit:
		return;
}

void* _wh_mem_realloc_freelist(_wh_mem_realloc_params* params) {
	u64 bytes = 0;
	void* ptr = nullptr;
	wh_heap_node_s* node = nullptr;

	_wh_mem_alloc_params p = {
		params->heap, 
		params->bytes,
		nullptr,
		params->flags, 
		params->error,
	};

	_wh_mem_free_params f = {
		params->heap,
		params->ptr,
		nullptr,
		params->error,
	};

	ptr = _wh_mem_alloc_freelist(&p);

	if (nullptr == ptr) {
		wh_log_error(("Failed to realloc block"));
		goto go_error_exit;
	}

	node = wh_ptr_add(params->ptr, -sizeof(wh_heap_node_s));
	bytes = params->bytes > node->bytes ? node->bytes : params->bytes;

	memcpy(ptr, params->ptr, bytes);
	wh_log_debug(("Freeing memory"));
	_wh_mem_free_freelist(&f);
go_error_exit:
	return ptr;
}
