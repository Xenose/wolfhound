#include<wh/memory/core.h>

i64 _wh_memcmp_mask(_wh_memcmp_mask_params params) {
	i64 out = 0;
	u8* cc0 = (u8*)params.c0;
	u8* cc1 = (u8*)params.c1;
	u8* m = (u8*)params.mask;

	if (nullptr == cc0 && nullptr == cc1) {
		goto go_exit;
	}
	
	if (nullptr == cc0 || nullptr == cc1) {
		out = -1;
		goto go_error_exit;
	}

	if (nullptr == m) {
		wh_for(i64, i, params.length) {
			out = *cc0 - *cc1;

			if (0 != out) {
				break;
			}

			// moving the pointer
			cc0 += 1;
			cc1 += 1;
		}
	} else {
		wh_for(i64, i, params.length) {
			out = (*cc0 & *m) - (*cc1 & *m);

			if (0 != out) {
				break;
			}

			// moving the pointer
			cc0 += 1;
			cc1 += 1;
			m += 1;
		}
	}

go_exit:
go_error_exit:
	return out;
}
