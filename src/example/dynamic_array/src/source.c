#include<wh/data/dynamic_array.h>

#include<wh/debug/logger.h>
#include<wh/debug/signalar.h>
#include<wh/debug/benchmark.h>

void hash_foreach(void* value) {
    wh_log_debug(("--> %i"), *((int*)value));
}

int main(int arc, char* const* arv) {
    int* value = nullptr;
    wh_darray_s array = { 0 };
    
    wh_darray_init(WH_STRUCT_TYPE_DYNAMIC_ARRAY_STD, &array, sizeof(int), 100);
    
    value = wh_darray_set(&array, 10, WH_INT(10));
    wh_log_info(("Value is [ %i ]"), *value);
    
    value = wh_darray_get(&array, 10);
    wh_log_info(("Value is [ %i ]"), *value);
    
    return 0;
}
