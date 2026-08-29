#include<wh-posix/setjmp.h>

int sigsetjmp(sigjmp_buf env, int savesigs) {
   return setjmp(env.jbuf);
}

void siglongjmp(sigjmp_buf env, int val) {
   longjmp(env.jbuf, val);
}