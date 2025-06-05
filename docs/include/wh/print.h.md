[stdarg.h](stdarg.h)
[common.h](wh/common.h)

# wh_print [ Thread Safe ] and wh_print_va [ Thread Safe ]
```c
wh_print((const char* format, i64 fd : optional, char* buffer : optional, u64 buffer_length : optional, u64 offset : optional, u64 flags : optional), ...)
```

| Parameter | Type | Designation | Optional | Description |
| --------- | ---- | ----------- | -------- | ----------- |
| format | const char* | .format | NO | The formatted string used for printing. |
| fd | i64 | .fd | YES | The file descriptor for output(defaults yo 1). |
| buffer | char* | .buffer | YES | Optional output buffer. |
| buffer_length | u64 | .buffer_length | YES | Size of the output buffer. |
| offset | u64 | .offset | YES | Offset into buffer to start writing. |
| flags | u64 | .flags | YES | Print control flags (e.g. WH_PRINT_NO_FLUSH). |
## Formats
| Trigger | Standard from | Input            | Currently Implemented | Description                                                           |
| ------- | ------------- | ---------------- | --------------------- | --------------------------------------------------------------------- |
| $$      | Wolfhound     | None             | YES                   | Prints a single $.                                                    |
| %%      | C ANSI        | None             | YES                   | Prints a single %.                                                    |
| $[...]  | Wolfhound     | User Provided    | YES                   | Allows the user to call their own functions with there data.          |
| $b      | Wolfhound     | Memory, Length   | NO                    | Takes a pointer to memory and prints it out with the length provided. |
| $f      | Wolfhound     | Formatted String | YES                   | Allows recursive calling of formatted string.                         |
| $k      | Wolfhound     | Int to Bytes     | YES                   | Prints the integer into [ B, KB. MD. GB, TB, ...].                    |
| $n      | Wolfhound     | Errno            | YES                   |                                                                       |
| $m      | Wolfhound     | Memory, Length   | NO                    | Takes a pointer to memory and its length printing it in hex.          |
| $s      | Wolfhound     | String, Length   | NO                    | Prints a string using the provided length.                            |
| $t      | Wolfhound     | Format String    | NO                    | Reads the inputted string and print the formatted time.               |
| $v      | Wolfhound     | VK_Result        | YES                   | Takes the status code and prints in human readable format.            |
| %a      | C ANSI        | double           | NO                    |                                                                       |
| %A      | C ANSI        | double           | NO                    |                                                                       |
| %b      | C ANSI        | unsigned         | NO                    |                                                                       |
| %c      | C ANSI        | char             | YES                   | Prints a single char.                                                 |
| %C      | POSIX         | wchar_t*         | NO                    |                                                                       |
| %d      | C ANSI        | integer          | YES                   | Prints an integer to the output.                                      |
| %e      | C ANSI        | double           | NO                    |                                                                       |
| %E      | C ANSI        | double           | NO                    |                                                                       |
| %f      | C ANSI        | double           | NO                    |                                                                       |
| %F      | C ANSI        | double           | NO                    |                                                                       |
| %g      | C ANSI        | double           | NO                    |                                                                       |
| %G      | C ANSI        | double           | NO                    |                                                                       |
| %i      | C ANSI        | integer          | YES                   | Prints an integer to the output.                                      |
| %s      | C ANSI        | string           | YES                   | Takes a null terminated string and copies it to the output.           |
| %S      | POSIX         | const wchar_t*   | NO                    |                                                                       |
| %n      | C ANSI        |                  | NO                    |                                                                       |
| %m      | GNU           | NONE             | YES                   | Prints the errno string in place.                                     |

## Examples
```c
	i64 bytes = wh_print(("hello $f"), "world%s", "\n");
```

# wh_print_buffer_check
