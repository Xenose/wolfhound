#include<wh-posix/string.h>
#include<wh-posix/unistd.h>
#include<wh-sys/memreq.h>
#include<wh-sys/data/hashmap.h>
#include<wh/maths/core.h>
#include<wh/maths/memory.h>

#include<wh-core/debug/logger.h>

static u64 _struct_size(i64 type) {
    switch (type) {
        case WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_SYS:
        case WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_STD:
            return sizeof(wh_hashmap_slot_string_s);
        case WH_STRUCT_TYPE_HASHMAP_LAZY_PTR_SYS:
            return sizeof(wh_hashmap_slot_ptr_s);
    }

    return 0;
}

static i64 _hash_simple(i64 type, void* key, i64 slot_count) {
    switch (type) {
        case WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_SYS:
        case WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_STD:
            return wh_hash_simple(key, slot_count);
        case WH_STRUCT_TYPE_HASHMAP_LAZY_PTR_SYS:
            return wh_hash_simple((void*)&key, slot_count, sizeof(void*));
    }

    return -1;
}

static i8 _keycomp(void* key1, void* key2, i64 type) {
    if (nullptr == key1 || nullptr == key2) {
        goto go_exit;
    }

    switch (type) {
        case WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_SYS:
        case WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_STD:
            return !!strcmp(key1, key2);
        case WH_STRUCT_TYPE_HASHMAP_LAZY_PTR_SYS:
            return key1 == key2;
        default:
            wh_error(("Failed to get key type!!!"));
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

    wh_error(("Failed to get key type!!!"));
    return nullptr;
}

static void* _set_key(i64 type, void* dst, void* src) {
    switch (type) {
        case WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_SYS:
        case WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_STD:
            return ((wh_hashmap_slot_string_s*)dst)->key = src;
            
        case WH_STRUCT_TYPE_HASHMAP_LAZY_PTR_SYS:
            return((wh_hashmap_slot_ptr_s*)dst)->key = src;
    }

    wh_error(("Failed to get key type!!!"));
    return nullptr;
}

static void* _at_offset(wh_hashmap_s* map, u64 index, u64 offset) {
    return wh_ptr_offset(map->slots, (index * (map->type_size + _struct_size(map->stype))) + offset);
}

static void* _get_value(wh_hashmap_s* map, u64 index) {
    void* out = nullptr;

    switch (map->stype) {
        case WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_SYS:
        case WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_STD:
        case WH_STRUCT_TYPE_HASHMAP_LAZY_PTR_SYS:
            out = _at_offset(map, index, _struct_size(map->stype));
            // wh_ptr_offset(map->slots, (_struct_size(map->stype) + map->type_size) * index);
    }

    return out;
}

static i8 _slot_set(wh_hashmap_s* map, u64 index, void* key, void* value) {
    void* dst = nullptr;

    // Setting the pointer to the struct
    dst = _at_offset(map, index, 0);
    _set_key(map->stype, dst, key);

    // Setting the memory to after the struct
    dst = wh_ptr_offset(dst, _struct_size(map->stype));
    memcpy(dst, value, map->type_size);

    return 0;
}

static i8 _slot_copy(wh_hashmap_s* map, void* src, void* dst, u64 index, u64 count) {
    void* skey = nullptr;
    void* dkey = nullptr;
    u64 d_index = 0;

    if (nullptr == src) {
        goto go_exit;
    }

    src = _at_offset(src, index, 0); // wh_ptr_offset(src, index * (map->type_size + _struct_size(map->stype)));
    skey = _get_key(map->stype, src);

    if (nullptr == skey) {
        goto go_exit;
    }

    d_index = (u64)_hash_simple(map->stype, skey, (i64)count);
    dst = _at_offset(dst, d_index, 0); // wh_ptr_offset(dst, d_index * (map->type_size + _struct_size(map->stype)));
    dkey = _get_key(map->stype, dst);

    if (nullptr != dkey) {
        wh_info(("Slot has a value!"));
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
        wh_info(("map size is -> type : %lu"), i);

        if (0 > _slot_copy(map, map->slots, new_slots, i, new_count)) {
            goto go_error_exit;
        }
    }

    //wh_sys_memrel(map->slots, map->resize_size);
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

    if (nullptr != slots) {
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

    wh_info(("map size is -> %lu, type : %lu"), bytes, map->type_size);

    if ((map->type_size + _struct_size(map->stype)) >= map->resize_size) {
        bytes = map->resize_size = 8192;
    }
    
    wh_info(("map size is -> %lu, type : %lu"), bytes, map->type_size);

    for (u64 i = 0; 3 >= i; i++) {
        bytes *= 2;
        out = _alloc_lazy_simple_sys(map, &bytes, &slots);

        if (nullptr == out) {
            goto go_error_exit;
        }

        // making sure the memory is zero.
        memset(out, 0, bytes);

        // _map_copy will release the memory if successful.
        if (0 == _map_copy(map, out, slots)) {
            break;
        }
        
        //wh_sys_memrel(out, bytes);
    }

    map->slots = out;
    map->resize_size = bytes;
    return out;
go_error_exit:
    return nullptr;
}

static i8 _insert_lazy_simple_sys(_wh_hashmap_insert_params* params) {
    u64 index = 0;
    void* d_key = nullptr;
    wh_hashmap_s* const map = params->map;

    if (nullptr == map->slots) {
        if (nullptr == _realloc_lazy_simple_sys(params->map)) {
            goto go_error_exit;
        }
    }

    index = (u64)_hash_simple(map->stype, params->key, (i64)map->slot_count);
    d_key = _get_key(map->stype, _at_offset(map, index, 0));

    if (_keycomp(params->key, d_key, map->stype)) {
        // TODO free memory
        goto go_error_exit;
    }

    if (_slot_set(map, index, params->key, params->value)) {
        // TODO : check return value
    }

    return 0;
go_error_exit:
    return -1;
}

// Destroy frees all the memory
static i8 _destroy_lazy_simple_sys() {
    return 0;
}


static void* _get_lazy_simple_sys(wh_hashmap_s* map, void* key) {
    u64 hash = (u64)_hash_simple(map->stype, key, (i64)map->slot_count);
    return _get_value(map, hash);
}

static void* _get_key_lazy_simple_sys(wh_hashmap_s* map, void* key) {
    u64 hash = (u64)_hash_simple(map->stype, key, (i64)map->slot_count);
    return _get_key(map->stype, _at_offset(map, hash, 0));
}

// Delete removes a item
static i8 _delete_lazy_simple_sys(wh_hashmap_s* map, void* key) {
    u64 index = (u64)_hash_simple(map->stype, key, (i64)map->slot_count);
    void* slot = _get_key_lazy_simple_sys(map, key);

    wh_hashmap_destructor_s entry = {
        .data = wh_ptr_offset(slot, sizeof(wh_hashmap_slot_string_s)),
    };

    if (nullptr != map->destructor) {
        map->destructor(&entry);
    }

    _set_key(map->stype, slot, nullptr);
    memset(entry.data, 0, map->type_size);
    return 0;
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
