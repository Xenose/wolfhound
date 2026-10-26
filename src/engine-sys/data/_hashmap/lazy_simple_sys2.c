#include<wh-posix/string.h>
#include<wh-posix/unistd.h>
#include<wh-sys/memreq.h>
#include<wh-sys/data/hashmap.h>
#include<wh-sys/debug/logger.h>
#include<wh/maths/core.h>
#include<wh/maths/memory.h>

static u64 _struct_size_lazy_simple_sys(i64 type) {
    switch (type) {
        case WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_SYS:
            return sizeof(wh_hashmap_slot_string_s);
        case WH_STRUCT_TYPE_HASHMAP_LAZY_PTR_SYS:
            return sizeof(wh_hashmap_slot_ptr_s);
    }

    return 0;
}

static void* _alloc_lazy_simple_sys(wh_hashmap_s* const map, u64 bytes, u64* slots) {
    void* out = nullptr;
    u64 b = wh_ualign(bytes, (u64)sysconf(_SC_PAGESIZE));

    out = wh_sys_memreq(b);

    if (nullptr == out) {
        wh_critical(("Failed to allocated memory from the system!"));
        goto go_error_exit;
    }

    if (nullptr == slots) {
        *slots = b / (map->type_size + _struct_size_lazy_simple_sys(map->stype));
    }

    return out;
go_error_exit:
    return nullptr;
}

static void* _realloc_lazy_simple_sys(wh_hashmap_s* const map) {
    u64 slots = 0;
    void* out = nullptr;

    map->resize_size *= 2;
    out = _alloc_lazy_simple_sys(map, map->resize_size, &slots);

    if (nullptr == out) {
        goto go_error_exit;
    }

    return out;
go_error_exit:
    return nullptr;
}

static i8 _insert_lazy_simple_sys(_wh_hashmap_insert_params* params) {
    if (nullptr == params->map->slots) {
    }

    return 0;
}
