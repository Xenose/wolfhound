#include<wh-common/os.h>
#if (WH_SYSTEM&WH_SYS_WINDOWS)

#include<wh-posix/_windows/fd_table.h>

#define FD_MAX 1024

/*
#include<stdio.h>

void _wnt_log_last_error(const char* context, DWORD err) {
    LPSTR msg = NULL;

    // Ask Windows to format the message string for this error code
    FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, 
        err, 
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
        (LPSTR)&msg, 
        0, 
        NULL
    );

    // Print to your engine log or console
    printf("[KERNEL ERROR] Context: %s | Code: %lu | Message: %s\n", context, err, msg ? msg : "Unknown Error");

    // CRITICAL: FormatMessage allocates this buffer, you MUST free it
    if (msg) {
        LocalFree(msg);
    }
}
*/

static _wnt_fd_entry _fds[FD_MAX] = {
   {
      .type          = _WNT_FD_TYPE_STD,
   },
   {
      .type          = _WNT_FD_TYPE_STD,
   },
   {
      .type          = _WNT_FD_TYPE_STD,
   },
};

void (*_wnt_table_init)();

void _wnt_table_init_dummy() {

}

void _wnt_table_init_real() {
   _fds[0].data.handle = GetStdHandle(STD_INPUT_HANDLE);
   _fds[1].data.handle = GetStdHandle(STD_OUTPUT_HANDLE);
   _fds[2].data.handle = GetStdHandle(STD_ERROR_HANDLE);

   _wnt_table_init = _wnt_table_init_dummy;
}


void (*_wnt_table_init)() = _wnt_table_init_real;


int _wnt_table_create(_wnt_fd_entry* entry) {
   for (int i = 3; i < FD_MAX; i++) {
      if (_WNT_FD_TYPE_EMPTY == _fds[i].type) {
         _fds[i] = *entry;
         return i;
      }
   }
   return -1;
}

int _wnt_table_delete(int fd) {
    if (fd >= 3 && fd < FD_MAX) {
        _fds[fd].type = _WNT_FD_TYPE_EMPTY;
        return 0;
    }
    return -1;
}

int _wnt_table_get(int fd, _wnt_fd_entry* entry) {
   if (fd < 0 || fd >= FD_MAX || _fds[fd].type == _WNT_FD_TYPE_EMPTY) {
      return -1;
   }

   *entry = _fds[fd];

   return fd;
go_error_exit:
   return -1;
}

int _wnt_table_search(_wnt_fd_entry* entry) {
   for (int i = 3; i < FD_MAX; i++) {
      if (_WNT_FD_TYPE_EMPTY == _fds[i].type) {
         continue;
      }

      if (memcmp(&entry->data, &_fds[i].data, sizeof(entry->data))) {
         *entry = _fds[i];
         return i;
      }
   }

   return -1;
}

int _wnt_table(int fd, _wnt_fdop op, _wnt_fd_entry* entry) {
   _wnt_table_init();

   switch(op) {
      case _WNT_FDOP_CREATE:
         return _wnt_table_create(entry);
      case _WNT_FDOP_DELETE:
         return _wnt_table_delete(fd);
      case _WNT_FDOP_GET:
         return _wnt_table_get(fd, entry);
      case _WNT_FDOP_SEARCH:
         return _wnt_table_search(entry);
   }
}

#endif