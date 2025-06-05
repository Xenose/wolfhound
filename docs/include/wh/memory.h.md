[common.h](wh/common.h)
[memory.h](wh/sys/memory.h)
[memory.h](wh/types/memory.h)
[memory.h](wh/params/memory.h)

## wh_heap_init

```c
wh_heap_header_s* wh_heap_init(u64 bytes, u64* error: optional)
```

wh_heap_init is designed create new heaps from either the
global heap or from a sub-heap.

| Name  | Type               | Status        | Comment                                                 |
| ----- | ------------------ | ------------- | ------------------------------------------------------- |
| bytes | uint64_t           | Implemented   | The number of bytes that will be allocated to the heap. |
| heap  | wh_heap_header_s*  | Unimplemented | The heap from where the new heap will be created.       |
| error | uint64_t           | Implemented   | Upon a error this variable is set if not nullptr.       |

### Return Value
Upon success a heap pointer is returned and on error a nullptr is returned.

### See also
[common.h](include/wh/common.h)

| Parameter | Type | Designation | Optional | Description |
| --------- | ---- | ----------- | -------- | ----------- |
| heap | wh_heap_s* | .heap | NO | The heap that will be printed. |

## wh_mem_free(void* owner, void* ptr, wh_heap_header_s* heap : optional, u64* error : optional)

## wh_mem_alloc()




