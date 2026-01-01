#include<wh-posix/unistd.h>

#ifndef _GNU_SOURCE
#include<sys/syscall.h>

pid_t gettid(void) {
	return (pid_t)syscall(SYS_gettid);
}
#endif /* _GNU_SOURCE */
