#include<wh-posix/setjmp.h>

#if (WH_SYSTEM&WH_SYS_WINDOWS)
   #include"_windows/setjmp.c"
#endif