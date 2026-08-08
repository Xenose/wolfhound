#ifndef _wh_header_string_
#define _wh_header_string_

#include<wh-core/common.h>
#include<wh-params/string.h>

WH_C()

extern char* _wh_strcat(_wh_strcat_params params, ...);
//extern wh_string_s _wh_string_append(_wh_string_append_params, ...);
extern wh_string_s _wh_string_create(int dummy, ...);
extern const char* _wh_strstr(_wh_strstr_params params);

#ifndef __cplusplus
/* [MD_DOC]
 *
 * # Summary wh_strcat
 * This function is a safer take on the classic but oh so dangerous strcat,
 * this will take several strings as a va_list and concatenate them to the
 * buffer.
 *
 * ## Parameters
 * @d_param(char*)		buffer			: The buffer where the data will be stored.
 * @d_param(u64)			buffer_length	: The size of the buffer.
 * @d_opt(u64)				offset			: The offset where the appending will start, note this will subtract from length and add to the buffer pointer.
 * @d_opt(u64*)			error				: A pointer to user provided pointer where the errors will be stored.
 *
 * ## Return
 * Will return the buffer pointer at its current location.
 *
 */
#define wh_strcat(x, ...)	WH_EPF(_wh_strcat((_wh_strcat_params) { WH_VA_ARGS x }, __VA_ARGS__, WH_PTR_MAX))

//#define wh_string_append(x, ...)		_wh_string_append((_wh_string_append_params) { WH_VA_ARGS x }, __VA_OPT__(, __VA_ARGS__ ))
#define wh_string_create(...)			WH_EPF(_wh_string_create(0, __VA_ARGS__, nullptr))
#define wh_strstr(...)					WH_EPF(_wh_strstr((_wh_strstr_params) { __VA_ARGS__ }))
#endif /* __cplusplus */

WH_C_END()
#endif /* _wh_header_string_ */
