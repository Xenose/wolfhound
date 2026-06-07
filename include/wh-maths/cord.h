#ifndef __wh_maths_cord__
#define __wh_maths_cord__

#include<stdint.h>

#define WH_32_MM_TO_CORD(x) (((int32_t)(x)) << 10)
#define WH_32_CORD_TO_MM(x) (((int32_t)(x)) >> 10)

#define WH_64_MM_TO_CORD(x) (((int64_t)(x)) << 10)
#define WH_64_CORD_TO_MM(x) (((int64_t)(x)) >> 10)

typedef int32_t cord32_t;
typedef int64_t cord64_t;

#endif /* __wh_maths_cord__ */
