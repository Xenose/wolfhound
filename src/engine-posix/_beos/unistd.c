#include<wh-posix/kernel/OS.h>
#include<wh-posix/unistd.h>

pid_t gettid(void) {
    return find_thread(NULL);
}
