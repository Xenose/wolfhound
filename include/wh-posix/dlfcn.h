#ifndef _wh_header_posix_dlfcn_
#define _wh_header_posix_dlfcn_

#include<wh-core/os.h>

#if (WH_SYSTEM&WH_SYS_POSIX)
    #include<dlfcn.h>
#else
    // open flags
    #define RTLD_LAZY               0x0001
    #define RTLD_NOW                0x0002
    #define RTLD_GLOBAL             0x0004
    #define RTLD_LOCAL              0x0008

    #define RTLD_NODELETE           0x0010
    #define RTLD_NOLOAD             0x0020
    #define RTLD_DEEPBIND           0x0040

    // info flags
    #define RTLD_DI_LMID            0x0100
    #define RTLD_DI_LINKMAP         0X0200
    #define RTLD_DI_ORIGIN          0x0400
    #define RTLD_DI_SERINFO         0x0800
                                        
    #define RTLD_DI_SERINFOSIZE     0x1000
    #define RTLD_DI_TLS_MODID       0x2000
    #define RTLD_DI_TLS_DATA        0x4000
    #define RTLD_DI_PHDR            0x8000

    typedef struct {
        char*           dls_name;       // name of library search path.
        unsigned int    dls_flags;      // Flags of indication of where this came from.
    } Dl_serpath;

    typedef struct {
        size_t          dls_size;       // size of the entire buffer
        unsigned int    dls_cnt;        // number of elements in dls_serpath
        Dl_serpath*     dls_serpath;    // the pointer of elements
    } Dl_serinfo;

    typedef struct {
        const char* dli_fname;
        void*       dli_fbase;
        const char* dli_sname;
        void*       dli_saddr;
    } Dl_info;

    extern void* dlopen(const char*, int flags);
    extern void* dlsym(void* handle, const char* symbol);
    extern int dlinfo(void* handle, int request, void* info);
    extern int dladdr(const void* addr, Dl_info* info);
    extern int dlclose(void* handle);
#endif

#endif /* _wh_header_posix_dlfcn_ */
