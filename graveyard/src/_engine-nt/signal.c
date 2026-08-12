#include <_wh-nt/signal.h>
#include <wh-posix/windows.h>

// BOOL WINAPI SetConsoleCtrlHandler(_In_opt_ PHANDLER_ROUTINE HandlerRoutine, _In_ BOOL Add);
int _wnt_set_console_ctrl_handler(int (*handler)(unsigned int), short add) {
   return SetConsoleCtrlHandler(handler, add);
}

void _wnt_create_event() {
}

void _wnt_event_for_single_object() {
}

void _wnt_queue_user_apc() {
}

void* _wnt_add_vectored_exception_handler(unsigned long first, long (*func)(_wnt_exception_pointers_s*)) {
   EXCEPTION_POINTERS ep = {
      .ContextRecord = (EXCEPTION_RECORD){
         .ExceptionAddress = 
      },
   };
   return AddVectoredContinueHandler(first, &ep)
}
