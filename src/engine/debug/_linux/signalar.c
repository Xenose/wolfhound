#include<signal.h>
#include<string.h>
#include<errno.h>

#include<stdio.h>

#define _pointer_count 20

// my code
#include<wh/debug/logger.h>
#include<wh/debug/signalar.h>
#include<ucontext.h>
#include<sys/reg.h>
#include<sys/ucontext.h>
#define UNW_LOCAL_ONLY

#ifdef _GNU_SOURCE
#include<execinfo.h>
#endif

static void _wh_signal_handler(int sig, siginfo_t* info, ucontext_t* uc) {
	i64 count = 0;
	void* _ptrs[_pointer_count] = { 0 };

	signal(sig, SIG_DFL);

	switch(sig) {
		case SIGSEGV:
			signal(sig, SIG_DFL);
#ifdef _GNU_SOURCE
			count = backtrace(_ptrs, _pointer_count);
			backtrace_symbols_fd(_ptrs, (int)count, 2);
#endif
			raise(sig);
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
