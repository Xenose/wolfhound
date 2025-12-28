#ifndef _wh_header_posix_windows_
#define _wh_header_posix_windows_

#ifndef _WINSOCKAPI_
   #define _WINSOCKAPI_
#endif

#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN
#endif

#ifndef NOMINMAX
   #define NOMINMAX
#endif

#define NTDDI_VERSION NTDDI_WIN10
#define _WIN32_WINNT 0x0A00

#include <io.h>

// Winsock 2 ONLY
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>

// Other Win32 headers
#include <libloaderapi.h>
#include <wingdi.h>

// ALWAYS LAST
// Always include last or windows will explode!
#include <windows.h>
#include <winternl.h>

#endif