#ifndef _wh_header_posix_ucontext_
#define _wh_header_posix_ucontext_

#include<wh-core/os.h>
#include<wh-posix/signal.h>

#if (WH_SYSTEM&WH_SYS_POSIX)
   #include <wh-posix/sys/ucontext.h>
#else(WH_SYSTEM&WH_SYS_WINDOWS)
   typedef void* mcontext_t;

   typedef struct ucontext_t {
      struct ucontext_t*   uc_link;
      sigset_t             uc_sigmask;
      stack_t              uc_stack;
      mcontext_t           uc_mcontext;
   } ucontext_t;
#endif

#endif
