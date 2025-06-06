#include<wh/sys/filesystem.h>
#include<wh/loader/asset.h>
#include<wh/print.h>
#include<wh/debug.h>

#include<string.h>

typedef struct {
	wh_string_s name;
} wh_asset_s;

i64 _wh_assets_load(const char* path) {
	char p[1024] = { 0 };
	wh_dir_s dir = wh_read_dir(nullptr, path);

	wh_for(i64, i, dir.count) {
		wh_print(("%s\n"), dir.entries[i].name);

		if (WH_FSYS_DIR == dir.entries[i].type) {
			memcpy(p, path, strlen(path));
			strcat(p, "/");
			strcat(p, dir.entries[i].name);

			wh_log_debug((p));
			_wh_assets_load(p);
		}
	}

	wh_dir_destroy(nullptr, &dir);
	return 0;
}
