#include<wh-core/common.h>
#include<wh-core/print.h>

#if !(WH_SYSTEM&WH_SYS_TCC)
    static wh_thread char _buffer[WH_CORE_PRINT_BUFFER_LENGTH];
#endif

char* wh_core_print_buffer(i64* length) {
    if (nullptr != length) {
        *length = WH_CORE_PRINT_BUFFER_LENGTH;
    }

    return _buffer;
}
