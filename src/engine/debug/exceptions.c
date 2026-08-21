#include<wh-posix/signal.h>
#include<wh-posix/stdio.h>
#include<wh-posix/unistd.h>
#include<wh/debug/exceptions.h>

#if !(WH_SYSTEM&WH_SYS_TCC)
    wh_thread _wh_try_info_s* _jmp_info = nullptr;
#else
    _wh_try_info_s* _jmp_info;
#endif

static void _wh_handler(int sig, siginfo_t* action, void* data) {
    _wh_try_info_s* info = _jmp_info;

    signal(sig, SIG_DFL);
    _jmp_info = info->old_info;
    sigaction(SIGSEGV, &info->old_action, nullptr);


    switch (sig) {
        case SIGSEGV:
            siglongjmp(info->buffer, WH_EXCEPTION_SIGSEGV);
            break;
    }
}

i8 _jmp_init(_wh_try_info_s* info) {
    #if (WH_SYSTEM&WH_SYS_TCC)
        return -1;
    #endif

    struct sigaction new_action = {
        .sa_sigaction = &_wh_handler,
        .sa_flags = SA_SIGINFO,
    };

    if (0 != info->count) {
        goto go_skip;
    }


    sigemptyset(&new_action.sa_mask);

    if (-1 == sigaction(SIGSEGV, &new_action, &info->old_action)) {
        goto ERROR_EXIT;
    }

    info->old_info = _jmp_info;
    _jmp_info = info;
go_skip:
    return info->count;
ERROR_EXIT:
    // TODO :: return more errors
    return -1;
}

i8 _jmp_last_exception(wh_exception_s* exp) {
    switch (exp->error) {
        case 0:
            _jmp_info = _jmp_info->old_info;
            exp->error = 1;
            return 1;
        default:
            return 0;
    }
}
