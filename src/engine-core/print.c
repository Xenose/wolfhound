#include<wh-core/common.h>
#include<wh-core/print.h>
#include<wh-posix/unistd.h>
#include<wh-posix/stdatomic.h>

#if !(WH_SYSTEM&WH_SYS_TCC)
    static wh_thread char _buffer[WH_CORE_PRINT_BUFFER_LENGTH];
#else
    typedef struct {
        int id;
        char* buffer;
    } _tcc_buffer_s;

    static atomic_flag _lock;
    static int _tcc_buffer_count = 0;
    static _tcc_buffer_s* _buffers;

    // To mimic thread local buffers for
    // TinyCC we need to have more then one buffer...
    char* get_thread_buffer(int id) {
        char* out = nullptr;
        _tcc_buffer_s* tmp = nullptr;

        while (atomic_flag_test_and_set(&_lock)) {
            usleep(1);
        } 

        wh_for(int, i, _tcc_buffer_count) {
            if (id == _buffers[i].id) {
                out = _buffers[i].buffer;
                goto go_break;
            }
        }

        tmp = reallocarray(_buffers, _tcc_buffer_count + 1, sizeof(_tcc_buffer_s));

        if (nullptr == tmp) {
            // TODO error;
        }

        _buffers = tmp;
        _buffers[_tcc_buffer_count].id = id;
        _buffers[_tcc_buffer_count].buffer = malloc(WH_CORE_PRINT_BUFFER_LENGTH);
        out = _buffers[_tcc_buffer_count].buffer;

        if (nullptr == _buffers[_tcc_buffer_count].buffer) {
            // TODO error;
        }

        ++_tcc_buffer_count;
go_break:
       atomic_flag_clear(&_lock);
       return out;
    }
#endif

char* wh_core_print_buffer(i64* length) {
    #if (WH_SYSTEM&WH_SYS_TCC)
        char* _buffer = nullptr;

        _buffer = get_thread_buffer(gettid());
    #endif

    if (nullptr != length) {
        *length = WH_CORE_PRINT_BUFFER_LENGTH;
    }

    return _buffer;
}
