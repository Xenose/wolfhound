#ifndef __wh_maths_cord__
#define __wh_maths_cord__

#include <wh-posix/stdint.h>

#define WH_CORD_UNIT 10 // 10 means 10 bits giving us 1024 per 1mm

#define WH_32_MM_TO_CORD(x) (((int32_t)(x)) << WH_CORD_UNIT)
#define WH_32_CORD_TO_MM(x) (((int32_t)(x)) >> WH_CORD_UNIT)

#define WH_64_MM_TO_CORD(x) (((int64_t)(x)) << WH_CORD_UNIT)
#define WH_64_CORD_TO_MM(x) (((int64_t)(x)) >> WH_CORD_UNIT)

typedef int32_t cord32_t;
typedef int64_t cord64_t;

#endif /* __wh_maths_cord__ */
