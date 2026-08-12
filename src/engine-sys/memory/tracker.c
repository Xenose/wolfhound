#include<wh-posix/stdlib.h>

#include<wh-sys/memory.h>
#include<wh/data/hashmap.h>
#include<wh/data/list.h>
#include<wh/debug/exceptions.h>
#include<wh/debug/logger.h>

void* _wh_tracker_destructor(wh_hashmap_destructor_s* entry);

// Linked list tracking

typedef struct {
    void* ptr;
    void** owners;
    u64 owner_count;
    u64 line;
    const char* file;
} _wh_heap_ptr_pair_s;

// need pointer version
static wh_hashmap_s _map = {
    .stype = WH_STRUCT_TYPE_HASHMAP_LAZY_PTR_SYS,
    .slots = nullptr,

    .destructor = _wh_tracker_destructor,

    .type_size = sizeof(_wh_heap_ptr_pair_s),
    .resize_size = 8096,
};

void* _wh_tracker_destructor(wh_hashmap_destructor_s* entry) {
    _wh_heap_ptr_pair_s* e = entry->data;

    if (!!e->owner_count) {
        free(e->owners);
    }

    return nullptr;
}

bool _wh_track_search(void* entry_in, void* ptr_in) {
    _wh_heap_ptr_pair_s* entry = entry_in;

    if (entry->ptr == ptr_in) {
        return true;
    }

    return false;
}

/*
 * Tracking functions
 *
 */
void _wh_tracker_insert(void* owner, void* ptr, wh_heap_header_s* heap, u64 line, const char* file) {
    _wh_heap_ptr_pair_s* entry = nullptr;

    if (nullptr == ptr) {
        return;
    }

    if (nullptr == owner) {
        wh_log_critical(("Untracked pointer at [ %s:%u ]!"), file, line);
    }

    wh_log_info(("Inserting node for %u owner %u"), ptr, owner);

    if (nullptr != _map.slots) {
        entry = wh_hashmap_get(&_map, ptr);
        goto go_skip;
    }

    if (nullptr == entry) {
go_skip:
        wh_log_debug(("New pointer entry added! ptr : %u"), ptr);

        _wh_heap_ptr_pair_s tmp = {
            .ptr = ptr,
            .owners = malloc(sizeof(void*)),
            .owner_count = 1,
            .line = line,
            .file = file,
        };

        if (nullptr == tmp.owners) {
            wh_log_critical(("Failed to allocate owner ptr memory"));
        } else {
            tmp.owners[0] = owner;
        }

        wh_hashmap_insert(&_map, ptr, &tmp);
        entry = wh_hashmap_get(&_map, ptr);
    } else {
        entry = wh_hashmap_get(&_map, ptr);

        void** tmp = realloc(entry->owners, sizeof(void*) * (entry->owner_count + 1));
        wh_log_debug(("The owner count is %u"), entry->owner_count);

        if (nullptr == tmp) {
            wh_log_critical(("Failed to allocate owner ptr memory"));
        } else {
            entry->owners = tmp;
            entry->owners[entry->owner_count] = owner;
        }

        ++entry->owner_count;
    }

    wh_log_debug(("inserted new node!"));
}

void _wh_tracker_remove(void* owner, void* ptr) {
    u64 index = 0;
    _wh_heap_ptr_pair_s* entry = nullptr;

    if (nullptr == ptr) {
        return;
    }

    if (nullptr == owner) {
        wh_log_critical(("Freeing untracked pointer!"));
    }

    wh_log_info(("Removing node for %u owner %u"), ptr, owner);
    entry = wh_hashmap_get(&_map, ptr);

    wh_log_info(("Node memory is $m"), entry, sizeof(_wh_heap_ptr_pair_s));

    if (nullptr != entry) {
        wh_log_debug(("The owner count is %u"), entry->owner_count);

        wh_for(u64, i, entry->owner_count) {
            if (owner == entry->owners[i]) {
                --entry->owner_count;
                entry->owners[i] = entry->owners[entry->owner_count];
                break;
            }
        }

        if (0 == entry->owner_count) {
            wh_log_info(("Owner count reached zero!"));
            //wh_list_delete(&_list, index);
        }
    }
}

void _wh_mem_scan_for_each(void* node) {
    bool clean_up = false;
    _wh_heap_ptr_pair_s* entry = node;

    wh_for(u64, i, entry->owner_count) {
        wh_try {
            if (entry->owners[i] != entry->ptr) {
                //wh_log_warning(("Owner change! ptr [ %u ] != owner [ %u ] in file:line [ %s:%u ]"), current->owners[i].owner, current->ptr, current->owners[i].file, current->owners[i].line);
                clean_up = true;
            }
        } wh_catch(ex) {
            //wh_log_critical(("SEGFAULT :: Owner change! ptr [ %u ] != owner [ %u ] in file:line [ %s:%u ]"), current->owners[i].owner, current->ptr, current->owners[i].file, current->owners[i].line);
            clean_up = true;
        }

        if (clean_up) {
            wh_log_error(("Found a loss end pointer, clean up your mess!"));
            --entry->owner_count;
            entry->owners[i] = entry->owners[entry->owner_count];
        }
    }

    if (0 == entry->owner_count) {
        wh_log_error(("LEAK FOUND! freeing... ptr : [ %p ]"), entry->ptr);
        wh_hashmap_delete(&_map, entry->ptr);
        //wh_free(->heap, current->ptr, nullptr);
    }
}

i64 _wh_mem_scan(void) {
    i64 count = 0;
    _wh_hashmap_foreach(&_map, &_wh_mem_scan_for_each);
    return count;
}
