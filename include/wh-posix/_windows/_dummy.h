// Dummy header for syntax highlight for non windows systems

#include <stdint.h>
#include <stddef.h>
#include <limits.h>

// Basic Windows types
typedef char CHAR;
typedef int SOCKET;
typedef int32_t LONG;
typedef uint32_t DWORD;
typedef void* HANDLE;
typedef void* ULONG_PTR;

typedef int BOOL;
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef char* LPSTR;
typedef const char* LPCSTR;

// Constants & Flags
#define MAX_PATH PATH_MAX
#define INVALID_HANDLE_VALUE ((HANDLE)-1)

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

// Toolhelp32 flags
#define TH32CS_SNAPPROCESS 0x00000002

typedef struct tagPROCESSENTRY32 {
    DWORD     dwSize;
    DWORD     cntUsage;
    DWORD     th32ProcessID;
    ULONG_PTR th32DefaultHeapID;
    DWORD     th32ModuleID;
    DWORD     cntThreads;
    DWORD     th32ParentProcessID;
    LONG      pcPriClassBase;
    DWORD     dwFlags;
    CHAR      szExeFile[MAX_PATH];
} PROCESSENTRY32;

// Function mocks / stubs
#define GetCurrentThreadId() 1
#define GetCurrentProcessId() 1
#define CreateToolHelp32Snapshot(...) ((HANDLE)1)
#define Process32First(...) FALSE
#define Process32Next(...) FALSE
#define CloseHandle(...) TRUE
