#ifndef _wh_header_sys_foreman_
#define _wh_header_sys_foreman_

#include <wh-core/common.h>
#include <wh-sys/atomic_lock.h>
#include <wh-types/gameinfo.h>
#include <wh-types/foreman.h>
#include <wh-types/wolfhound.h>

extern void wh_foreman_init(wh_instance_s* ins, wh_foreman_s* foreman);
extern void wh_foreman_execute(wh_foreman_s* foreman);

#endif /* _wh_header_sys_foreman_ */
