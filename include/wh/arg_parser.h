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

#define wh_args_parse(...) _wh_args_parse((_wh_args_parse_params) { __VA_ARGS__ })

#endif /* _wh_header_arg_parser_ */
