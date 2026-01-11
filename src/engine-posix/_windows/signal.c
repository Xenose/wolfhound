#include<wh-common/os.h>
#include<wh-posix/signal.h>
#include<wh-posix/windows.h>

static void NTAPI timer_callback(PVOID Context, BOOLEAN TimerOrWaitFired) {
}


int sigaction(int sig, const struct sigaction* restrict act, struct sigaction* restrict oact) {
   NTSTATUS status =  0;
   HANDLE handle = nullptr; 
   LARGE_INTEGER li = { 0 };

   /*switch (sig) {
      case SIGALRM:
         // TODO move to alarm in unistd.h
         status = NtCreateTimer(&handle, TIMER_ALL_ACCESS, nullptr, NotificationEvent);

         if (!NT_SUCCESS(status)) {
         }
         
         li.QuadPart = -10000000LL;
         NtSetTimer(handle, &li, &timer_callback, nullptr, false, 0, nullptr);
   }*/
}