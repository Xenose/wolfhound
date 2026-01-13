#include<thread.h>
#include<wh-posix/unistd.h>

pid_t gettid(void) {
	return (pid_t)thr_self();
}
