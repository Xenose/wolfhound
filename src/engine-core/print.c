#include<wh-core/common.h>
#include<wh-core/print.h>

#if !(WH_SYSTEM&WH_SYS_TCC)
    static wh_thread char _buffer[WH_CORE_PRINT_BUFFER_LENGTH];
#endif

extern char* wh_core_print_buffer() {
    return _buffer;
}
