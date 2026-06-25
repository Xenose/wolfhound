#ifndef _wh_header_posix_sys_mman_
#define _wh_header_posix_sys_mman_

#include<wh-posix/sys/types.h>
#include<wh-common/common.h>

WH_C()

void* mmap(void* addr, size_t length, int prot, int flags, int fildes, off_t off);

WH_C_END()
#endif /* _wh_header_posix_sys_mman_ */