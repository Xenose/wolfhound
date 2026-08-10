#ifndef _wh_header_posix_windows_
#define _wh_header_posix_windows_

#include <wh-core/os.h>

#if (WH_SYSTEM&WH_SYS_WINDOWS)
    #ifdef _MSC_VER
        #pragma warning(push)
        #pragma warning(disable : 4005)
        #pragma warning(disable : 4028)
    #endif

    // MUST be defined before windows.h to stop it from loading legacy winsock.h
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif

    #ifndef NOMINMAX
        #define NOMINMAX
    #endif

    #define NTDDI_VERSION NTDDI_WIN10
    #define _WIN32_WINNT 0x0A00

    #pragma push_macro("_WINDOWS_POSIX")
        #ifndef _WNT_RAW
            // sys/socket.h
            #undef socket
            #undef listen
            #undef bind
            #undef send  
            #undef recv
            #undef sendto
            #undef recvfrom

            // netdb.h
            #undef getaddrinfo
            #undef freeaddrinfo
            #undef gai_strerror
        #endif
        // 1. Include Winsock 2 FIRST
        #include<winsock2.h>
        #include<ws2tcpip.h>

        // 2. Now include Windows.h safely (it will see winsock2 is loaded and skip winsock.h)
        #include<windows.h>

        // 3. Rest of system/Win32 headers

        #include<iphlpapi.h>
        #include<io.h>
        // Other Win32 headers

        #include<winternl.h>
    #pragma pop_macro("_WINDOWS_POSIX")

    #ifdef _MSC_VER
        #pragma warning(pop)
    #endif
#endif // end windows

#endif
