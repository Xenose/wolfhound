#ifndef __wh_maths_cord__
#define __wh_maths_cord__

#include<stdint.h>

#define WH_MM_TO_CORD(x) ((x) << 10)
#define WH_CORD_TO_MM(x) ((x) >> 10)

typedef int64_t cord_t;

#endif /* __wh_maths_cord__ */
