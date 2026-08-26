#include <wh-posix/string.h>
#include <wh/debug/logger.h>
#include <wh/maths/memory.h>

#include <wh-types/memory.h>
#include <wh-params/memory.h>

void* _wh_dummy_alloc(_wh_mem_alloc_params* params)  {
    return nullptr;
}

void _wh_dummy_free(_wh_mem_free_params* params) {
}

void* _wh_dummy_realloc(_wh_mem_realloc_params* params) {
    return nullptr;
}
