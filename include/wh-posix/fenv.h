#ifndef _wh_header_posix_fenv_
#define _wh_header_posix_fenv_

#include<wh-core/os.h>

#if (WH_SYSTEM&WH_SYS_POSIX)
    #include<fenv.h>
#endif

#endif /* _wh_header_posix_fenv_ */
