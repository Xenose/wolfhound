#include<signal.h>
#include<unistd.h>
#include<stdio.h>
#include<wh/debug/exceptions.h>

#define JMP_MAX 256

wh_thread i64 _jmp_index = -1;

wh_thread i64 _jmp_error[JMP_MAX] = { 0 };
wh_thread struct sigaction _old_sigaction[JMP_MAX] = { 0 };
wh_thread sigjmp_buf _jmp_buffers[JMP_MAX] = { 0 };

static void _wh_handler(int signal, siginfo_t* action, void* data) {
	//sigaction(SIGSEGV, SIG_DFL, nullptr);

	if (_jmp_index > 0) {
		sigaction(SIGSEGV, &_old_sigaction[_jmp_index - 1], nullptr);
	}

	switch (signal) {
		case SIGSEGV:
			siglongjmp(_jmp_buffers[_jmp_index], WH_EXCEPTION_SIGSEGV);
			break;
	}
}

i8 _jmp_init() {
	struct sigaction new_action = {
		.sa_sigaction = &_wh_handler,
		.sa_flags = SA_SIGINFO,
	};

	sigemptyset(&new_action.sa_mask);

	if (JMP_MAX <= _jmp_index + 1) {
		goto ERROR_EXIT;
	}

	if (-1 == sigaction(SIGSEGV, &new_action, &_old_sigaction[_jmp_index + 1])) {
		goto ERROR_EXIT;
	}

	++_jmp_index;
	printf("Index is %li\n", _jmp_index);
	return 0;
ERROR_EXIT:
	// TODO :: return more errors
	return -1;
}
