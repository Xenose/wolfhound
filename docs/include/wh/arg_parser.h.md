[lua.h](lua.h)
[common.h](wh/common.h)
[config.h](wh/types/config.h)

This function runs the commands located in the
command folder.

| Parameter | Type | Designation | Optional | Description |
| --------- | ---- | ----------- | -------- | ----------- |
| .ls | lua_State* | ..ls | NO | The sate that will be effected by the commands. |
| .arc | int | ..arc | NO | The argc count. |
| .arv | char* const* | ..arv | NO | The argv from the command line. |
| .config | wh_config_s* | ..config | NO | The config struct. |
