#ifndef _wh_header_common_
#define _wh_header_common_

#include<wh-posix/limits.h>

#include<wh-core/types.h>
#include<wh-core/prefix.h>
#include<wh-core/bytes.h>
#include<wh-core/enum.h>
#include<wh-core/macros.h>

WH_C()

#include<wh-posix/stdint.h>
#include<wh-posix/stddef.h>
#include<wh-posix/stdbool.h>
#include<wh-posix/sys/types.h>


/* [MD_DOC]
 * ## wh_string_s
 * This is a safe string that doesn't really on nullptr termination
 * and instead uses length to keep track of its length.
 *
 * | Variable | Type     | Comment                                                                                      |
 * | -------- | -------- | -------------------------------------------------------------------------------------------  |
 * | data     | uint8_t* | This variable is for accessing the bytes directly its in the shared memory with str and ptr. |
 * | str      | char*    | This variable is for accessing the string directly, it shares memory with data and ptr.      |
 * | ptr      | void*    | This variable is for accessing the pointer directly, it shares memory with str and data.     |
 * | length   | uint64_t | The length of the stored data.                                                               |
 */
typedef struct {
    union {
        u8* data;
        char* str;
        void* ptr;
    };
    u64 length;
} wh_string_s;

typedef struct {
    u64 r : 8;
    u64 g : 8;
    u64 b : 8;
    u64 a : 8;
} wh_rgba_s;

typedef struct {
    void* ptr;
    u64 bytes;
} wh_buffer_s;

typedef struct {
    void* ptr;
    u64 size;
    u64 free;
} wh_sysmem_s;

typedef struct {
    struct_type stype;
} wh_struct;

WH_C_END()
#endif /* _wh_header_common_ */
