#ifndef _wh_header_print_
#define _wh_header_print_

#include<stdarg.h>
#include<wh-common/common.h>

WH_C()

#define WH_PRINT_NO_FLUSH			0x0001
#define WH_PRINT_ADD_NEW_LINE		0x0002

typedef struct {
	u64 left;		// %XX
	u64 right;		// %.XX

	struct {
		u8 length_set		: 1;	// .XX
		u8 alt_form			: 1;	// #
		u8 left_align		: 1;	// -
		u8 zero_pad			: 1;	// 0
		u8 space_pad		: 1;	// ' '
		u8 force_sign		: 1;	// +
		u8 thousnad_group : 1;	// '
		u8 long_value		: 1;  // l
		u8 llong_value		: 1;  // l
	} flags;
} wh_print_format_s;

typedef struct {
	char* start;
	char* format;
	char* buffer;
	i64 length;		// length of buffer
	i64 written;	// number of charters written
	i64 fd;

	wh_print_format_s print_format;
} wh_print_data_s;

typedef struct {
	wh_print_data_s* data; 
	u64 needed;
} _wh_print_buffer_check_params;

typedef struct {
	const char* format;
	i64 fd;
	char* buffer;
	i64 buffer_length;
	i64 offset;
	u64 flags;
} _wh_print_params;

typedef struct {
	const char* key;
	i64 (*func)(wh_print_data_s* data, void* ptr);
} _wh_print_add_func_params;

extern i64 _wh_print_buffer_check(_wh_print_buffer_check_params params);
extern i64 _wh_print_va(_wh_print_params params, va_list list);
extern i64 _wh_print(_wh_print_params params, ...);
extern void _wh_print_add_func(_wh_print_add_func_params params);

#if !defined(__cplusplus) || !defined(WH_USE_C_MACRO_FUNC)

/* [MD_DOC]
 * # wh_print [ Thread Safe ] and wh_print_va [ Thread Safe ]
 * ```c
 * wh_print((const char* format, i64 fd : optional, char* buffer : optional, u64 buffer_length : optional, u64 offset : optional, u64 flags : optional), ...)
 * ```
 *
 * @d_param(const char*)	format			: The formatted string used for printing.
 * @d_opt(i64)					fd					: The file descriptor for output(defaults yo 1).
 * @d_opt(char*)				buffer			: Optional output buffer.
 * @d_opt(u64)					buffer_length	: Size of the output buffer.
 * @d_opt(u64)					offset			: Offset into buffer to start writing.
 * @d_opt(u64)					flags				: Print control flags (e.g. WH_PRINT_NO_FLUSH).
 *
 * ## Formats
 * | Trigger | Standard from | Input            | Currently Implemented | Description                                                           |
 * | ------- | ------------- | ---------------- | --------------------- | --------------------------------------------------------------------- |
 * | $$      | Wolfhound     | None             | YES                   | Prints a single $.                                                    |
 * | %%      | C ANSI        | None             | YES                   | Prints a single %.                                                    |
 * | $[...]  | Wolfhound     | User Provided    | YES                   | Allows the user to call their own functions with there data.          |
 * | $b      | Wolfhound     | Memory, Length   | NO                    | Takes a pointer to memory and prints it out with the length provided. |
 * | $f      | Wolfhound     | Formatted String | YES                   | Allows recursive calling of formatted string.                         |
 * | $k      | Wolfhound     | Int to Bytes     | YES                   | Prints the integer into [ B, KB. MD. GB, TB, ...].                    |
 * | $n      | Wolfhound     | Errno            | YES                   |                                                                       |
 * | $m      | Wolfhound     | Memory, Length   | YES                   | Takes a pointer to memory and its length printing it in hex.          |
 * | $s      | Wolfhound     | String, Length   | NO                    | Prints a string using the provided length.                            |
 * | $t      | Wolfhound     | Format String    | NO                    | Reads the inputted string and print the formatted time.               |
 * | $v      | Wolfhound     | VK_Result        | YES                   | Takes the status code and prints in human readable format.            |
 * | %a      | C ANSI        | double           | YES(tmp sprintf)      |                                                                       |
 * | %A      | C ANSI        | double           | YES(tmp sprintf)      |                                                                       |
 * | %b      | C ANSI        | unsigned         | NO                    |                                                                       |
 * | %c      | C ANSI        | char             | YES                   | Prints a single char.                                                 |
 * | %C      | POSIX         | wchar_t*         | NO                    |                                                                       |
 * | %d      | C ANSI        | integer          | YES                   | Prints an integer to the output.                                      |
 * | %e      | C ANSI        | double           | YES(tmp sprintf)      |                                                                       |
 * | %E      | C ANSI        | double           | YES(tmp sprintf)      |                                                                       |
 * | %f      | C ANSI        | double           | YES(tmp sprintf)      |                                                                       |
 * | %F      | C ANSI        | double           | YES(tmp sprintf)      |                                                                       |
 * | %g      | C ANSI        | double           | NO                    |                                                                       |
 * | %G      | C ANSI        | double           | NO                    |                                                                       |
 * | %i      | C ANSI        | integer          | YES                   | Prints an integer to the output.                                      |
 * | %s      | C ANSI        | string           | YES                   | Takes a null terminated string and copies it to the output.           |
 * | %S      | POSIX         | const wchar_t*   | NO                    |                                                                       |
 * | %n      | C ANSI        |                  | YES                   |                                                                       |
 * | %m      | GNU           | NONE             | YES                   | Prints the errno string in place.                                     |
 * 
 * ## Examples
 * ```c
 *	i64 bytes = wh_print(("hello $f"), "world%s", "\n");
 * ```
 */

#define wh_print_va(x, args) WH_EPF(_wh_print_va((_wh_print_params){ WH_VA_ARGS x }, args))
#define wh_print(x, ...) WH_EPF(_wh_print((_wh_print_params){ WH_VA_ARGS x } WH_VA_OPT(__VA_ARGS__)))

/* [MD_DOC]
 * # wh_print_buffer_check
 */
#define wh_print_buffer_check(...) WH_EPF(_wh_print_buffer_check((_wh_print_buffer_check_params){ __VA_ARGS__ }))
#define wh_print_add_func(...) WH_EPF(_wh_print_add_func((_wh_print_add_func_params){ __VA_ARGS__ }))


#ifdef USE_NAMESPACE_WOLFHOUND

#define print wh_print
#define print_va wh_print_va

#endif /* USE_NAMESPACE_WOLFHOUND */ 

#endif /* __cplusplus */

WH_C_END()
#endif /* _wh_header_print_ */
