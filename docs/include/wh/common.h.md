[limits.h](limits.h)
[prefix.h](wh/common/prefix.h)
[bytes.h](wh/common/bytes.h)
[enum.h](wh/common/enum.h)
[macros.h](wh/common/macros.h)
[atomic.h](wh/wrap/atomic.h)
[stdint.h](stdint.h)
[stddef.h](stddef.h)
[stdbool.h](stdbool.h)
[types.h](sys/types.h)

# Integer Types

| Name     | Type       | Comment                              |
| -------- | ---------- | ------------------------------------ |
| int128_t | __int128_t | Using the compiler in built integer. |
| i8       | int8_t     |                                      |
| i16      | int16_t    |                                      |
| i32      | int32_t    |                                      |
| i64      | int64_t    |                                      |
| i128     | int128_t   |                                      |

## wh_string_s
This is a safe string that doesn't really on nullptr termination
and instead uses length to keep track of its length.

| Variable | Type     | Comment                                                                                      |
| -------- | -------- | -------------------------------------------------------------------------------------------  |
| data     | uint8_t* | This variable is for accessing the bytes directly its in the shared memory with str and ptr. |
| str      | char*    | This variable is for accessing the string directly, it shares memory with data and ptr.      |
| ptr      | void*    | This variable is for accessing the pointer directly, it shares memory with str and data.     |
| length   | uint64_t | The length of the stored data.                                                               |
