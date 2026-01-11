#include<wh-posix/signal.h>
#include<string.h>
#include<errno.h>

#include<stdio.h>


// my code
#include<wh/debug/logger.h>
#include<wh/debug/signalar.h>

#define _pointer_count 20

wh_thread void* _ptrs[_pointer_count] = { 0 };

static void _wh_signal_handler(int sig, siginfo_t* info, void* ptr) {
	/*i64 count = 0;

	switch(sig) {
		case SIGSEGV:
			signal(sig, SIG_DFL);
			count = backtrace(_ptrs, _pointer_count);
			backtrace_symbols_fd(_ptrs, count, 2);
			raise(sig);
			break;
	}*/
}

i8 _wh_signalar_init(_wh_signalar_init_params params) {
	/*struct sigaction sa = {
		.sa_flags = SA_SIGINFO,
		.sa_sigaction = &_wh_signal_handler,
	};


	if (-1 == sigaction(SIGSEGV, &sa, nullptr)) {
		wh_log_warning(("Failed to set signal for [ %s ]\n"), "SIGSEGV");
		goto go_error_exit;
	}*/

	return 0;
/*go_error_exit:
	return -1;*/
}
