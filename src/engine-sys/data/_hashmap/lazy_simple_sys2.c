#include<wh-posix/string.h>
#include<wh-posix/unistd.h>
#include<wh-sys/memreq.h>
#include<wh-sys/data/hashmap.h>
#include<wh-sys/debug/logger.h>
#include<wh/maths/core.h>
#include<wh/maths/memory.h>

static u64 _struct_size(i64 type) {
    switch (type) {
        case WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_SYS:
            return sizeof(wh_hashmap_slot_string_s);
        case WH_STRUCT_TYPE_HASHMAP_LAZY_PTR_SYS:
            return sizeof(wh_hashmap_slot_ptr_s);
    }

    return 0;
}

static i64 _hash_simple(i64 type, void* key, i64 slot_count) {
    switch (type) {
        case WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_SYS:
            return wh_hash_simple(key, slot_count);
        case WH_STRUCT_TYPE_HASHMAP_LAZY_PTR_SYS:
            return wh_hash_simple((void*)&key, slot_count, sizeof(void*));
    }

    return -1;
}

static i8 _keycomp(void* key1, void* key2, i64 type) {
    wh_log_info(("src_key :: %u, dst_key :: %u"), key1, key2);

    if (nullptr != key1 || nullptr != key1) {
        goto go_exit;
    }

    switch (type) {
        case WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_SYS:
        case WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_STD:
            return !strcmp(key1, key2);
        case WH_STRUCT_TYPE_HASHMAP_LAZY_PTR_SYS:
            return key1 == key2;
        default:
            wh_log_error(("Failed to get key type!!!"));
    }

go_exit:
    return 0;

}

static void* _get_key(i64 type, void* ptr) {
    switch (type) {
        case WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_SYS:
        case WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_STD:
            return ((wh_hashmap_slot_string_s*)ptr)->key;
        case WH_STRUCT_TYPE_HASHMAP_LAZY_PTR_SYS:
            return ((wh_hashmap_slot_ptr_s*)ptr)->key;
    }

    wh_log_error(("Failed to get key type!!!"));
    return nullptr;
}

static void* _set_key(i64 type, void* dst, void* src) {
    switch (type) {
        case WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_SYS:
        case WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_STD:
            dst = &((wh_hashmap_slot_string_s*)dst)->key;
            src = &((wh_hashmap_slot_string_s*)src)->key;

            return memcpy(dst, src, sizeof(char*));
            
        case WH_STRUCT_TYPE_HASHMAP_LAZY_PTR_SYS:
            dst = &((wh_hashmap_slot_ptr_s*)dst)->key;
            src = &((wh_hashmap_slot_ptr_s*)src)->key;

            return memcpy(dst, src, sizeof(void*));
    }

    wh_log_error(("Failed to get key type!!!"));
    return nullptr;
}

static void* _get_value(wh_hashmap_s* map, u64 index) {
    void* out = nullptr;

    switch (map->stype) {
        case WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_SYS:
        case WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_STD:
        case WH_STRUCT_TYPE_HASHMAP_LAZY_PTR_SYS:
            out = wh_ptr_offset(map->slots, 
                    _struct_size(map->stype) * map->type_size * index);
    }

    return out;
}

static void* _set_value(i64 type, void* dst, void* src) {
    switch (type) {
        // TODO need to store the value after the metadata
        // and offset the pointer, do we need a dedicated pointer
        // why not do size of the struct + pointer would save data.
        case WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_SYS:
        case WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_STD:
            dst = &((wh_hashmap_slot_string_s*)dst)->key;
            src = &((wh_hashmap_slot_string_s*)src)->key;

            return memcpy(dst, src, sizeof(char*));
            
        case WH_STRUCT_TYPE_HASHMAP_LAZY_PTR_SYS:
            dst = &((wh_hashmap_slot_ptr_s*)dst)->key;
            src = &((wh_hashmap_slot_ptr_s*)src)->key;

            return memcpy(dst, src, sizeof(void*));
    }

    wh_log_error(("Failed to get key type!!!"));
    return nullptr;
}

static i8 _slot_set(wh_hashmap_s* map, u64 index, void* key, void* value) {
    void* dst = nullptr;

    dst = wh_ptr_offset(dst, index * (map->type_size + _struct_size(map->stype)));

    _set_key(map->stype, dst, key);
    _set_value(map->stype, dst, value);

    return 0;

}

static i8 _slot_copy(wh_hashmap_s* map, void* src, void* dst, u64 index, u64 count) {
    void* skey = nullptr;
    void* dkey = nullptr;
    u64 d_index = 0;

    src = wh_ptr_offset(src, index * (map->type_size + _struct_size(map->stype)));
    skey = _get_key(map->stype, src);

    if (nullptr == skey) {
        goto go_exit;
    }

    d_index = (u64)_hash_simple(map->stype, _get_key(map->stype, src), (i64)count);
    dst = wh_ptr_offset(dst, d_index * (map->type_size + _struct_size(map->stype)));
    dkey = _get_key(map->stype, src);

    if (nullptr != dkey) {
        goto go_error_exit;
    }

    memcpy(dst, src, (map->type_size + _struct_size(map->stype)));

    if (nullptr == _set_key(map->stype, dst, src)) {
        goto go_error_exit;
    }

go_exit:
    return 0;
go_error_exit:
    return -1;
}

static i8 _map_copy(wh_hashmap_s* map, void* new_slots, u64 new_count) {
    wh_for(u64, i, map->slot_count) {
        if (0 > _slot_copy(map, map->slots, new_slots, i, new_count)) {
            goto go_error_exit;
        }
    }

    wh_sys_memrel(map->slots, map->resize_size);
    map->slots = new_slots;
    map->slot_count = new_count;

    return 0;
go_error_exit:
    return -1;
}

static void* _alloc_lazy_simple_sys(wh_hashmap_s* const map, u64* bytes, u64* slots) {
    void* out = nullptr;
    u64 b = (u64)wh_align((i64)*bytes, sysconf(_SC_PAGESIZE));

    if (nullptr == (out = wh_sys_memreq(b))) {
        wh_critical(("[ %i ] Failed to allocated memory from the system!"), b);
        goto go_error_exit;
    }

    if (nullptr == slots) {
        *slots = b / (map->type_size + _struct_size(map->stype));
    }

    *bytes = b;
    return out;
go_error_exit:
    return nullptr;
}

static void* _realloc_lazy_simple_sys(wh_hashmap_s* map) {
    u64 slots = 0;
    u64 bytes = map->resize_size;
    void* out = nullptr;

    if (0 >= map->resize_size) {
        bytes = map->resize_size = 8192;
    }

    for (u64 i = 0; 3 >= i; i++) {
        bytes *= 2;
        out = _alloc_lazy_simple_sys(map, &bytes, &slots);

        if (nullptr == out) {
            goto go_error_exit;
        }

        // making sure the memory is zero.
        memset(out, 0, bytes);

        // _map_copy will release the memory if successful.
        if (0 != _map_copy(map, out, slots)) {
            wh_sys_memrel(out, bytes);
            continue;
        }
    }

    map->slots = out;
    map->resize_size = bytes;
    return out;
go_error_exit:
    return nullptr;
}

static i8 _insert_lazy_simple_sys(_wh_hashmap_insert_params* params) {
    u64 index = 0;
    wh_hashmap_s* const map = params->map;

    if (nullptr == map->slots) {
        if (nullptr == _realloc_lazy_simple_sys(params->map)) {
            goto go_error_exit;
        }
    }

    index = (u64)_hash_simple(map->stype, params->key, (i64)map->slot_count);

    if (_slot_set(map, index, params->key, params->value)) {
        // TODO : check return value
    }

    return 0;
go_error_exit:
    return -1;
}

static i8 _delete_lazy_simple_sys(wh_hashmap_s* map, void* key) {
    return 0;
}

static void* _get_lazy_simple_sys(wh_hashmap_s* map, void* key) {
    u64 hash = (u64)_hash_simple(map->stype, key, (i64)map->slot_count);
    return _get_value(map, hash);
}

static i8 _wh_lazy_simple_foreach(wh_hashmap_s* map, void (*func)(void* value)) {
    void* value = nullptr;

    for (u64 i = 0; i < map->slot_count; i++) {
        // TODO : implement function bellow i is index
        // value = _get_value(map, i);

        if (nullptr != value) {
            func(value);
        }
    }

    return 0;
}
