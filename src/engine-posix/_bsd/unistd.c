#include<pthread_np.h>
#include<wh-posix/unistd.h>


pid_t gettid(void) {
	return (pid_t)pthread_getthreadid_np();
}
