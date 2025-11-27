#include<wh/cpp/wolfhound.hpp>

extern "C" {
#include<wh/wolfhound.h>
}

using namespace wh;


instance_c::instance_c(const char* name, int arc, char* const* arv) {
	_wh_init_params params = { 0 };
	wh_args_s args = { 0 };

	args.count = arc;
	args.ptr = arv;

	params.ins = &_instance;
	params.args = args;
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
