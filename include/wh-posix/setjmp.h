#ifndef _wh_header_posix_setjmp_
#define _wh_header_posix_setjmp_

#include<setjmp.h>
#include<wh-core/os.h>

#if !(WH_SYSTEM&WH_SYS_POSIX)
   typedef struct {
      jmp_buf jbuf;
   } sigjmp_buf;

   extern int sigsetjmp(sigjmp_buf env, int savesigs);
   extern void siglongjmp(sigjmp_buf env, int val);
#endif

#endif /* _wh_header_posix_setjmp_ */
