#include<wh-core/c23-comp.h>
#include<wh-posix/dlfcn.h>

void* dlopen(const char* path, int flags) {
   return nullptr;
}
   
void* dlsym(void* handle, const char* symbol) {
   return nullptr;
}
    
int dlinfo(void* handle, int request, void* info) {
   return 0;
}
    
int dladdr(const void* addr, Dl_info* info) {
   return 0;
}
    
int dlclose(void* handle) {
   return 0;
}
    
char* dlerror(void) {
   return nullptr;
}