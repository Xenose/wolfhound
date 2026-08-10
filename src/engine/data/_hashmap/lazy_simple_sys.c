#include<wh-posix/string.h>
#include<wh-posix/unistd.h>
#include<wh-sys/memreq.h>
#include<wh/data/hashmap.h>
#include<wh/debug/logger.h>
#include<wh/maths/core.h>
#include<wh/maths/memory.h>


static i64 _lazy_simple_hash(i64 type, void* key, i64 slot_count) {
    i64 hash = -1;

    switch (type) {
        case WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_SYS:
            hash = wh_hash_simple(key, slot_count);
            break;
        case WH_STRUCT_TYPE_HASHMAP_LAZY_PTR_SYS:
            hash = wh_hash_simple((void*)&key, slot_count, sizeof(void*));
            break;
    }

    return hash;
}

static void* _lazy_simple_key_set(void* slots, void* key, i64 type) {
    switch (type) {
        case WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_SYS:
            return ((wh_hashmap_slot_string_s*)slots)->key = key;
        case WH_STRUCT_TYPE_HASHMAP_LAZY_PTR_SYS:
            return ((wh_hashmap_slot_ptr_s*)slots)->key = key;
    }

    return nullptr;
}

static void* _lazy_simple_key_get(void* slots, i64 type) {
    switch (type) {
        case WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_SYS:
            return ((wh_hashmap_slot_string_s*)slots)->key;
        case WH_STRUCT_TYPE_HASHMAP_LAZY_PTR_SYS:
            return ((wh_hashmap_slot_ptr_s*)slots)->key;
    }

    return nullptr;
}

i8 _lazy_simple_keycomp(void* src_key, void* dst_key, i64 type) {
    wh_log_info(("src_key :: %u, dst_key :: %u"), src_key, dst_key);

    if (nullptr != src_key) {
        goto go_exit;
    }

    if (nullptr != dst_key) switch (type) {
        case WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_SYS:
            return !strcmp(src_key, dst_key);
        case WH_STRUCT_TYPE_HASHMAP_LAZY_PTR_SYS:
            return src_key == dst_key;
    }

go_exit:
    return 0;
}

static i8 _lazy_simple_hash_copy(wh_hashmap_s* map, void* slots, u64 bytes, i64 slot_count, u64 resize_size) {
    u64 index = 0;
    void* src = nullptr;
    void* dst = nullptr;
    void* src_key = nullptr;
    void* dst_key = nullptr;

    wh_for(u64, i, map->slot_count) {
        src = wh_ptr_offset(map->slots, i * bytes);
        src_key = _lazy_simple_key_get(src, map->stype);

        if (nullptr != src_key) {
            index = (u64)_lazy_simple_hash(map->stype, src_key, (i64)slot_count);

            dst = wh_ptr_offset(slots, index * bytes);
            dst_key = _lazy_simple_key_get(dst, map->stype);

            if (nullptr != dst_key) {
                wh_sys_memrel(slots, resize_size);
                return -1;
            }

            memcpy(dst, src, map->type_size);
            _lazy_simple_key_set(dst, src_key, map->stype);
        }
    }

    wh_log_info(("Key at [ %u ]"), index);
    return 0;
}

/*
 * Lazy hashmap is designed to be a collision free hashmap,
 * meaning on collision we resize this might not be the best
 * in all cases but very useful in some cases.
 *
 * Look up speed o(1), realloc speed o(n).
 */
static void* _reallocate_lazy_simple_sys(wh_hashmap_s* map) {
    void* data = nullptr;
    u64 bytes = sizeof(wh_hashmap_slot_string_s) + map->type_size;

    void* new_slots = nullptr;

    u64 hash_index = 0;
    u64 new_slot_count = 0;
    u64 resize_size = map->resize_size;

go_retry_resize:
    // Calculating the needed memory and aligning it to page size and the new slot count.
    resize_size = (u64)wh_align((i64)resize_size + 1, getpagesize());
    new_slot_count = resize_size / (map->type_size + sizeof(wh_hashmap_slot_string_s));

    // Requesting the OS for memory.
    new_slots = wh_sys_memreq(resize_size);

    if (nullptr == new_slots) {
        wh_log_critical(("Failed to allocated memory from the system!"));
        goto go_error_exit;
    }

    memset(new_slots, 0, resize_size);
    _lazy_simple_hash_copy(map, new_slots, bytes, (i64)new_slot_count, resize_size);

    if (nullptr != map->slots) {
        wh_sys_memrel(map->slots, map->resize_size);
    }

    map->resize_size = resize_size;
    map->slots = new_slots;
    map->slot_count = new_slot_count;

    return map->slots;
go_error_exit:
    return nullptr;
}

static i8 _insert_lazy_simple_sys(_wh_hashmap_insert_params* params) {
    i64 hash = 0;
    u64 bytes = sizeof(wh_hashmap_slot_string_s) + params->map->type_size;
    void* src_key = nullptr;
    wh_hashmap_slot_string_s* slots = params->map->slots;
    wh_hashmap_slot_string_s* dst = nullptr;

    if (nullptr == slots) {
        slots = _reallocate_lazy_simple_sys(params->map);
    }

    hash = _lazy_simple_hash(params->map->stype, params->key, (i64)params->map->slot_count);

    if (-1 == hash) {
        wh_log_error(("Hash is negative! stype [ %i ]"), params->map->stype);
        goto go_error_exit;
    }

    dst = wh_ptr_offset(slots, (u64)hash * bytes);
    src_key = ((wh_hashmap_slot_string_s*)wh_ptr_offset(slots, (u64)hash * bytes))->key;

    if (_lazy_simple_keycomp(src_key, dst->key, params->map->stype)) {
        wh_log_error(("Inputed key and existing key is the same [ %s -> %s ]"),
                params->key, dst->key);
        goto go_error_exit;
    }

    for (u32 i = 0; i < 3 && nullptr != dst->key; i++) {
        wh_log_debug(("Hashmap size to small resizing!"));

        if (nullptr != _reallocate_lazy_simple_sys(params->map)) {
            slots = params->map->slots;
            hash = _lazy_simple_hash(params->map->stype, params->key, (i64)params->map->slot_count);
            dst = wh_ptr_offset(slots, (u64)hash * bytes);
            break;
        }
    }

    if (nullptr != dst->key) {
        goto go_error_exit;
    }

    dst->key = params->key;

    wh_log_debug(("New allocation assigned! [ %u ] [ hash : %i ] [ count : %i ]"), dst, hash, params->map->slot_count);
    memcpy(wh_ptr_add(dst, sizeof(wh_hashmap_slot_string_s)), params->value, params->map->type_size);

    return 0;
go_error_exit:
    return -1;
}

static i8 _insert_lazy_simple_sys_strig(_wh_hashmap_insert_params params) {
    //return _insert_lazy_simple_sys(&params, hash);
}

static i8 _delete_lazy_simple_sys(wh_hashmap_s* map, void* key) {
    u64 index = (u64)_lazy_simple_hash(map->stype, key, (i64)map->slot_count);
    wh_hashmap_slot_string_s* slot = wh_ptr_offset(map->slots, index * (sizeof(wh_hashmap_slot_string_s) + map->type_size));

    wh_hashmap_destructor_s entry = {
        .data = wh_ptr_offset(slot, sizeof(wh_hashmap_slot_string_s)),
    };

    if (nullptr != map->destructor) {
        map->destructor(&entry);
    }

    slot->key = nullptr;
    return 0;
}

static void* _get_lazy_simple_sys(wh_hashmap_s* map, void* key) {
    i64 hash = _lazy_simple_hash(map->stype, key, (i64)map->slot_count);
    u64 bytes = sizeof(wh_hashmap_slot_string_s) + map->type_size;
    wh_hashmap_slot_string_s* src = wh_ptr_offset(map->slots, (u64)hash * bytes);

    return wh_ptr_add(src, sizeof(wh_hashmap_slot_string_s));
}

i8 _wh_lazy_simple_foreach(wh_hashmap_s* map, void (*func)(void* value)) {
    u64 bytes = sizeof(wh_hashmap_slot_string_s) + map->type_size;
    wh_hashmap_slot_string_s* src = nullptr;

    for (u64 i = 0; i < map->slot_count; i++) {
        src = wh_ptr_offset(map->slots, (u64)i * bytes);

        if (nullptr != src->key) {
            func(wh_ptr_offset(src, sizeof(wh_hashmap_slot_string_s)));
        }
    }

    return 0;
}
