#include<wh-posix/signal.h>
#include<wh-posix/string.h>
#include<wh-posix/errno.h>

#include<wh-posix/stdio.h>

#define _pointer_count 20

// my code
#include<wh-sys/debug/logger.h>
#include<wh/debug/signalar.h>
#include<wh-posix/ucontext.h>
#include<wh-posix/execinfo.h>
#include<wh-posix/sys/reg.h>
#include<wh-posix/sys/ucontext.h>
#define UNW_LOCAL_ONLY
#include <wh-posix/libunwind.h>

static void _wh_signal_handler(int sig, siginfo_t* info, ucontext_t* uc) {
	i64 count = 0;
	unw_cursor_t cursor;

	signal(sig, SIG_DFL);
	unw_cursor_t cursor;

	switch(sig) {
		case SIGSEGV:
			if (0 > unw_init_local2(&cursor, uc, UNW_INIT_SIGNAL_FRAME)) {
				wh_log_critical(("unw_init_local2 [ $n ]"), errno);
				return;
			}

			while (0 < unw_step(&cursor)) {
				unw_word_t ip, sp;
				char func_name[256];
				unw_word_t offset = 0;

				// Get instruction pointer (IP) and stack pointer (SP)
				unw_get_reg(&cursor, UNW_REG_IP, &ip);
				unw_get_reg(&cursor, UNW_REG_SP, &sp);

				// Get function name
				if (unw_get_proc_name(&cursor, func_name, sizeof(func_name), &offset) == 0) {
					printf("%p : [sp=%p] %s (offset: %ld)\n", (void*)ip, (void*)sp, func_name, (long)offset);

				} else {
					printf("%p : [sp=%p]\n", (void*)ip, (void*)sp);
				}
			}

			break;
	}
	raise(sig);
}

i8 _wh_signalar_init(_wh_signalar_init_params params) {
	struct sigaction sa = {
		.sa_flags = SA_SIGINFO,
		.sa_sigaction = (void (*)(int sig, siginfo_t* info, void* uc))&_wh_signal_handler,
	};

	if (-1 == sigaction(SIGSEGV, &sa, nullptr)) {
		wh_log_warning(("Failed to set signal for [ %s ]\n"), "SIGSEGV");
		goto go_error_exit;
	}

	return 0;
go_error_exit:
	return -1;
}
