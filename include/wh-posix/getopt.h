#ifndef _wh_header_posix_getopt_
#define _wh_header_posix_getopt_

#include<wh-core/prefix.h>
#include<wh-core/os.h>

WH_C()

#if (WH_SYSTEM&WH_SYS_POSIX)
    #include<getopt.h>
#else
    extern char* optarg;
    extern int optind;
    extern int opterr;
    extern int optopt;

    extern int getopt(int argc, char* argv[], const char* optstring);
#endif

WH_C_END()

#endif /* _wh_header_posix_getopt_ */
