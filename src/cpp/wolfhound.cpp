#include<wh/cpp/wolfhound.hpp>

extern "C" {
#include<wh/wolfhound.h>
}

using namespace wh;


instance_c::instance_c(const char* name, int arc, char* const* arv) {
	_wh_init_params params = { 0 };

	params.ins = &_instance;
	params.args = (wh_args_s){ 0,  arc, arv };
	params.mode = WH_GRAPHICS_MODE_SDL3;

	_instance = _wh_init(params);
}
	
instance_c::~instance_c() {
	if (nullptr != _instance) {
		// TODO free instance
	}
}
	
void instance_c::loop() {
}
