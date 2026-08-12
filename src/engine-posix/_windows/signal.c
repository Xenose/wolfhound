#include<wh-core/os.h>
#include<wh-posix/signal.h>
#include<wh-posix/_windows/windows.h>


static struct sigaction _handler_sigsegv = { 0 };


static void NTAPI timer_callback(PVOID Context, BOOLEAN TimerOrWaitFired) {
}

static LONG _signal_handler_sigsegv(EXCEPTION_POINTERS* ptrs) {
   siginfo_t info = {
      .si_addr = ptrs->ExceptionRecord->ExceptionInformation[1],
   };

   if (nullptr != _handler_sigsegv.sa_sigaction) {
      _handler_sigsegv.sa_sigaction(SIGSEGV, &info, nullptr);
      return EXCEPTION_CONTINUE_SEARCH;
   }

   return EXCEPTION_CONTINUE_EXECUTION;
}

int sigaction(int sig, const struct sigaction* restrict act, struct sigaction* restrict oact) {
   NTSTATUS status =  0;
   HANDLE handle = nullptr; 
   LARGE_INTEGER li = { 0 };
   struct sigaction old_act = { 0 };

   switch (sig) {
      case SIGALRM:
         return -1;
      case SIGSEGV:
         old_act = _handler_sigsegv;
         AddVectoredExceptionHandler(1, _signal_handler_sigsegv);
         break;
   }
   
   if (nullptr != oact) {
      *oact = old_act;
   }

   return 0;
}

int singal(int sig, void (*handler)(int)) {
   struct sigaction act = {
      .sa_handler = handler
   };

   return sigaction(sig, &act, nullptr);
}
