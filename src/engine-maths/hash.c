#include<wh-maths/hash.h>

typedef struct {
	wh_buffer_s buffer;
	u32 seed;
} wh_hash_xx32_params;


u32 wh_hash_xx32(wh_hash_xx32_params params) {
	u32 a_out = 0;

	u32 p1 = 0x9E3779B1U;  // 0b10011110001101110111100110110001
	u32 p2 = 0x85EBCA77U;  // 0b10000101111010111100101001110111
	u32 p3 = 0xC2B2AE3DU;  // 0b11000010101100101010111000111101
	u32 p4 = 0x27D4EB2FU;  // 0b00100111110101001110101100101111
	u32 p5 = 0x165667B1U;  // 0b00010110010101100110011110110001

	u32 a1 = params.seed + p1 + p2;
	u32 a2 = params.seed + p2;
	u32 a3 = params.seed;
	u32 a4 = params.seed - p1;
	
	// only used if input is less then 16 bytes
	u32 a5 = params.seed + p5;
	u64 bytes = params.buffer.bytes;

	for (u64 i = 0; 4 <= bytes; bytes -= 4, i++) {
		a1 = a1 + (((u32*)params.buffer.ptr)[i] * p2);
		a1 = (a1 << 13) | (a1 >> (32 - 13)); // bit rotation
		a1 = a1 * p1;
	}

	a_out += params.buffer.bytes;

	// step 5
	
	// step 6
	a_out = a_out & (a_out >> 15);
	a_out *= a_out * p2;

	a_out = a_out & (a_out >> 13);
	a_out *= a_out * p3;

	a_out = a_out & (a_out >> 16);

	return a_out;
}

i64 wh_hash_xx64() {
	return 0;
}
