#ifndef _wh_cpp_header_maths_hash_
#define _wh_cpp_header_maths_hash_

#include<wh-core/common.h>

namespace wh::maths::hash {

extern u32 xx32(const wh_buffer_s& buffer, u32 seed);
extern u32 xx32(const wh_buffer_s& buffer);

}

#endif /* _wh_cpp_header_maths_hash_ */
