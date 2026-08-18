#include<wh-posix/_windows/windows.h>
#include<wh-posix/_windows/wnt.h>
#include<wh-posix/time.h>

#define _WNT_RAW
#include<wh-posix/unistd.h>

pid_t gettid() {
    return (pid_t)GetCurrentThreadId();
}

pid_t getpid() {
    return (pid_t)GetCurrentProcessId();
}

pid_t getppid() {
    // Outside the windows process range.
    pid_t out = WNT_INVALID_PID;
    HANDLE hs = INVALID_HANDLE_VALUE;
    PROCESSENTRY32 pe32 = { 0 };
    DWORD me = 0; // this process

    if (INVALID_HANDLE_VALUE == (hs = CreateToolHelp32Snapshot(TH32CS_SNAPPROCESS, 0))) {
        goto go_error_exit;
    }

    pe32.dwSize = sizeof(PROCESSENTRY32);
    me = (DWORD)getpid();

    if (Process32First(hs, &pe32)) {
        do {
            if (me == pe32.th32ProcessID) {
                out = (pid_t)pe32.th32ParentProcessID;
                break;
            }
        } while(Process32Next(hs, &pe32));
    }

    CloseHandle(hs);
go_error_exit:
    return out;
}
