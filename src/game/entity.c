#include<wh/debug/logger.h>
#include<wh/game/entity.h>

i8 _wh_entity_add_data_header(int type, int count) {
	wh_entity_data_header_s* data;

	data->var_type = type;
	data->row_count = count;

	return 0;
}

i8 _wh_entity_init(_wh_entities_init_params params) {
	u64 bytes = sizeof(wh_entity_s) * params.count;

	params.ins->game.entity_count = 0;
	params.ins->game.entities = wh_alloc(
		params.ins->heap,
		bytes,
		&params.ins->game.entities
	);

	if (nullptr == params.ins->game.entities) {
		wh_log_error(("Failed to allocate entities..."));
		goto go_error_exit;
	}

	memset(params.ins->game.entities, 0, bytes);
	return 0;
go_error_exit:
	return -1;
}

u64 _wh_entity_create(_wh_entity_create_params params) {
	return 0;
}
