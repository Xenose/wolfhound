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
| Trigger | Input            | Implemented | Description                                                           |
| ------- | ---------------- | ----------- | --------------------------------------------------------------------- |
| $$      | None             | YES         | Prints a single $.                                                    |
| %%      | None             | YES         | Prints a single %.                                                    |
| $[...]  | User Provided    | YES         | Allows the user to call their own functions with there data.          |
| $b      | Memory, Length   | NO          | Takes a pointer to memory and prints it out with the length provided. |
| $f      | Formatted String | YES         | Allows recursive calling of formatted string.                         |
| $n      | errno            | YES         | Prints the errno string in place.                                     |
| $m      | Memory, Length   | NO          | Takes a pointer to memory and its length printing it in hex.          |
| $s      | String, Length   | NO          | Prints a string using the provided length.                            |
| $t      | Format String    | NO          | Reads the inputted string and print the formatted time.               |
| $v      | VK_Result        | YES         | Takes the status code and prints in human readable format.            |
| %c      | char             | YES         | Prints a single char.                                                 |
| %d      | integer          | YES         | Prints an integer to the output.                                      |
| %i      | integer          | YES         | Prints an integer to the output.                                      |
| %s      | string           | YES         | Takes a null terminated string and copies it to the output.           |

## Examples
```c
	i64 bytes = wh_print(("hello $f"), "world%s", "\n");
```

# wh_print_buffer_check
