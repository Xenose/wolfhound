#ifndef _wh_header_config_
#define _wh_header_config_

#include<wh-params/wolfhound.h>
#include<wh-types/config.h>

WH_C()

extern wh_config_s _wh_config_load(_wh_init_params* params, wh_config_s* conf);

WH_C_END()

#endif /* _wh_header_config_ */
