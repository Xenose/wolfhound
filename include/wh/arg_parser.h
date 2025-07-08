#ifndef _wh_header_arg_parser_
#define _wh_header_arg_parser_

#include<lua.h>

#include<wh/common.h>
#include<wh/types/config.h>

typedef struct {
	lua_State* ls;
	int arc;
	char* const* arv;
	wh_config_s* config;
} _wh_args_parse_params;

extern i64 _wh_args_parse(_wh_args_parse_params params);
extern i64 _wh_args_parser_init(void);

/* [MD_DOC]
 * This function runs the commands located in the
 * command folder.
 *
 * @d_param(lua_State*)		.ls		: The sate that will be effected by the commands.
 * @d_param(int)				.arc		: The argc count.
 * @d_param(char* const*)	.arv		: The argv from the command line.
 * @d_param(wh_config_s*)	.config	: The config struct.
 *
 */
#define wh_args_parse(...) _wh_args_parse((_wh_args_parse_params) { __VA_ARGS__ })
#define wh_args_parse_init() _wh_args_parse_init()

#ifdef USE_NAMESPACE_WOLFHOUND
#define args_parse wh_args_parse
#define args_parse_init wh_args_parse_init
#endif

#endif /* _wh_header_arg_parser_ */
