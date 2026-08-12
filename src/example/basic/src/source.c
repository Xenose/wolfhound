#include <wh/memory.h>
#include <wh/wolfhound.h>
#include <wh/print.h>
#include <wh/maths/core.h>
#include <wh/convert.h>
#include <wh/debug/logger.h>
#include <wh/string.h>

// temp
#include <wh-posix/string.h>
#include <wh-posix/stdio.h>

/* [MD] Example
 *
 */
void update(wh_instance_s* ins) {
}

int main(int arc, char* const* arv) {
	wh_instance_s* ins = wh_init(
		(wh_args_s){ arc, arv },			// command line arguments
		wh_string_create("basic"),			// application name
	);

	int count = 128;
	int* x[count];

	wh_for(int, i, count) {
		x[i] = wh_mem_alloc(&x, 10);
	}

	wh_mem_free(&x[2], x[2]);
	wh_mem_free(&x[5], x[5]);
	wh_mem_free(&x[6], x[6]);
	wh_mem_free(&x[4], x[4]);
	wh_mem_free(&x[3], x[3]);
	wh_mem_free(&x[9], x[9]);

	_wh_mem_print2();

	wh_print(("\n"));
	wh_log_debug(("debug example"));
	wh_log_info(("info example"));
	wh_log_notice(("notice example"));
	wh_log_warning(("warning example"));
	wh_log_error(("error example"));
	wh_log_critical(("critical example"));
	wh_log_alert(("alert example"));
	wh_log_emergency(("emergency example"));

	wh_loop(ins, &update);
	wh_end(ins);

	wh_log_info(("There are %d memory leaks!\n"), wh_mem_leak_count());
	return 0;
}
