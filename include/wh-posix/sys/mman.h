#ifndef _wh_header_posix_sys_mman_
#define _wh_header_posix_sys_mman_

#include<wh-posix/sys/types.h>
#include<wh-core/common.h>

WH_C()

#if (WH_SYSTEM&WH_SYS_POSIX)
    #include<sys/mman.h>
#elif (WH_SYSTEM&WH_SYS_WINDOWS)
   #define MAP_FAILED ((void*)-1)

   #define PROT_EXEC    0x0001
   #define PROT_READ    0x0002
   #define PROT_WRITE   0x0004
   #define PROT_NONE    0x0010

   #define MAP_SHARED            0x000001
   #define MAP_SHARED_VALIDATE   0x000002
   #define MAP_PRIVATE           0x000004
   #define MAP_32BIT             0x000008
   #define MAP_ANON              0x000010
   #define MAP_ANONYMOUS         MAP_ANON
   #define MAP_DENYWRITE         0x000020
   #define MAP_EXECUTABLE        0x000040
   #define MAP_FILE              0x000080
   #define MAP_FIXED             0x000100
   #define MAP_FIXED_NOREPLACE   0x000200
   #define MAP_GROWSDOWN         0x000400
   #define MAP_HUGETLB           0x000800
   #define MAP_HUGE_2MB          0x001000
   #define MAP_HUGE_1GB          0x002000
   #define MAP_LOCKED            0x004000
   #define MAP_NONBLOCK          0x008000
   #define MAP_NORESERVE         0x010000
   #define MAP_POPULATE          0x020000
   #define MAP_STACK             0x040000
   #define MAP_SYNC              0x080000
   #define MAP_UNINITIALIZED     0x100000

   void* mmap(void* addr, size_t length, int prot, int flags, int fildes, off_t off);
   int munmap(void *addr, size_t len);
#endif

WH_C_END()
#endif /* _wh_header_posix_sys_mman_ */
