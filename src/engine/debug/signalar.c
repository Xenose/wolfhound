#include<signal.h>
#include<string.h>
#include<errno.h>

#include<stdio.h>


// my code
#include<wh/debug/logger.h>
#include<wh/debug/signalar.h>

#define _pointer_count 20


#if (WH_SYSTEM&WH_SYS_POSIX)

#include<ucontext.h>
#include<execinfo.h>
#include<sys/reg.h>
#include<sys/ucontext.h>
#define UNW_LOCAL_ONLY

#ifdef WH_UNWIND_NOT_FOUND
#include<libunwind.h>
#endif

static void _wh_signal_handler(int sig, siginfo_t* info, ucontext_t* uc) {
	i64 count = 0;

	signal(sig, SIG_DFL);
#ifdef WH_UNWIND_NOT_FOUND
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
#else
	void* _ptrs[_pointer_count] = { 0 };

	switch(sig) {
		case SIGSEGV:
			signal(sig, SIG_DFL);
			count = backtrace(_ptrs, _pointer_count);
			backtrace_symbols_fd(_ptrs, (int)count, 2);
			raise(sig);
			break;
	}
#endif
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

#elif _WIN32

i8 _wh_signalar_init(_wh_signalar_init_params params) {
}

#else

wh_thread void* _ptrs[_pointer_count] = { 0 };

static void _wh_signal_handler(int sig, siginfo_t* info, void* ptr) {
	i64 count = 0;

	switch(sig) {
		case SIGSEGV:
			signal(sig, SIG_DFL);
			count = backtrace(_ptrs, _pointer_count);
			backtrace_symbols_fd(_ptrs, count, 2);
			raise(sig);
			break;
	}
}

i8 _wh_signalar_init(_wh_signalar_init_params params) {
	struct sigaction sa = {
		.sa_flags = SA_SIGINFO,
		.sa_sigaction = &_wh_signal_handler,
	};


	if (-1 == sigaction(SIGSEGV, &sa, nullptr)) {
		wh_log_warning(("Failed to set signal for [ %s ]\n"), "SIGSEGV");
		goto go_error_exit;
	}

	return 0;
go_error_exit:
	return -1;
}

#endif
