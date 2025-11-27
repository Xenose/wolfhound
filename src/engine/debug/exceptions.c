#include<signal.h>
#include<stdio.h>
#include<wh/wrap/unistd.h>
#include<wh/debug/exceptions.h>

#define JMP_MAX 256

wh_thread i64 _jmp_index = 0;
wh_thread i64 _jmp_error[JMP_MAX] = { 0 };
wh_thread sigjmp_buf _jmp_buffers[JMP_MAX] = { 0 };

#if WH_SYSTEM&WH_SYS_POSIX
wh_thread struct sigaction _old_sigaction[JMP_MAX] = { 0 };

static void _wh_handler(int sig, siginfo_t* action, void* data) {
	signal(sig, SIG_DFL);
	
	i64 index = _jmp_index;
	--_jmp_index;

	if (index > 0) {
		sigaction(SIGSEGV, &_old_sigaction[_jmp_index], nullptr);
	}
		

	switch (sig) {
		case SIGSEGV:
			siglongjmp(_jmp_buffers[index], WH_EXCEPTION_SIGSEGV);
			break;
	}
}
#endif

i8 _jmp_init() {
#if WH_SYSTEM&WH_SYS_POSIX
	struct sigaction new_action = {
		.sa_sigaction = &_wh_handler,
		.sa_flags = SA_SIGINFO,
	};

	sigemptyset(&new_action.sa_mask);
#endif

	if (JMP_MAX <= _jmp_index + 1) {
		goto ERROR_EXIT;
	}

#if WH_SYSTEM&WH_SYS_POSIX
	if (-1 == sigaction(SIGSEGV, &new_action, &_old_sigaction[_jmp_index])) {
		goto ERROR_EXIT;
	}
#endif

	printf("Index is %lli\n", _jmp_index);
	return 0;
ERROR_EXIT:
	// TODO :: return more errors
	return -1;
}
