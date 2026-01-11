#include<wh-maths/memory.h>

i64 wh_align(i64 value, i64 align) {
	return (value + (align - 1) & ~(align - 1));
}
