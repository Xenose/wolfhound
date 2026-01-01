#include<signal.h>
#include<string.h>
#include<errno.h>

#include<stdio.h>

#include<wh/debug/exceptions.h>
#include<wh/debug/logger.h>
#include<ucontext.h>
#include<execinfo.h>
#include<sys/reg.h>
#include<sys/ucontext.h>
#define UNW_LOCAL_ONLY

static void _wh_signal_handler(int sig, siginfo_t* info, ucontext_t* uc) {
	i64 count = 0;
	signal(sig, SIG_DFL);
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
