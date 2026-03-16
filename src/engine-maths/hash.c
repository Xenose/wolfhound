#include<wh-maths/hash.h>


u32 _wh_hash_xx32(_wh_hash_xx32_params params) {
	u64 index = 0;
	u64 bytes = params.buffer.bytes;
	u32 a_out = 0;

	static const u32 p1 = 0x9E3779B1U;  // 0b 10011110001101110111100110110001
	static const u32 p2 = 0x85EBCA77U;  // 0b 10000101111010111100101001110111
	static const u32 p3 = 0xC2B2AE3DU;  // 0b 11000010101100101010111000111101
	static const u32 p4 = 0x27D4EB2FU;  // 0b 00100111110101001110101100101111
	static const u32 p5 = 0x165667B1U;  // 0b 00010110010101100110011110110001

	// step 1
	u32 a1 = params.seed + p1 + p2;
	u32 a2 = params.seed + p2;
	u32 a3 = params.seed;
	u32 a4 = params.seed - p1;

	if (16 > bytes) {
		a_out = params.seed + p5;
		goto go_step_4;
	}

	// step 2
	for (; 16 <= bytes; bytes -= 16, index += 16) {
		a1 = a1 + *(u32*)wh_ptr_offset(params.buffer.ptr, index) * p2;
		a1 = (a1 << 13) | (a1 >> (32 - 13)); // bit rotation
		a1 = a1 * p1;

		a2 = a2 + *(u32*)wh_ptr_offset(params.buffer.ptr, index + 4) * p2;
		a2 = (a2 << 13) | (a2 >> (32 - 13)); // bit rotation
		a2 = a2 * p1;

		a3 = a3 + *(u32*)wh_ptr_offset(params.buffer.ptr, index + 8) * p2;
		a3 = (a3 << 13) | (a3 >> (32 - 13)); // bit rotation
		a3 = a3 * p1;

		a4 = a4 + *(u32*)wh_ptr_offset(params.buffer.ptr, index + 12) * p2;
		a4 = (a4 << 13) | (a4 >> (32 - 13)); // bit rotation
		a4 = a4 * p1;
	}

	// step 3
	a_out = 
		((a1 << 1) | (a1 >> (32 - 1))) +
		((a2 << 7) | (a2 >> (32 - 7))) +
		((a3 << 12) | (a3 >> (32 - 12))) +
		((a4 << 18) | (a4 >> (32 - 18)));

go_step_4:
	// step 4
	a_out += params.buffer.bytes;

	// step 5
	for (;4 <= bytes; bytes -= 4, index += 4) {
		a_out += *(u32*)wh_ptr_offset(params.buffer.ptr, index ) * p3;
		a_out = ((a_out << 17) | (a_out >> (32 - 17))) * p4; // bit rotation
	}

	for (; 1 <= bytes; bytes--, index++) {
		a_out += (((u8*)params.buffer.ptr)[index] * p5);
		a_out = ((a_out << 11) | (a_out >> (32 - 11))) * p1; // bit rotation
	}

	// step 6
	a_out = a_out ^ (a_out >> 15);
	a_out *= p2;

	a_out = a_out ^ (a_out >> 13);
	a_out *= p3;

	a_out = a_out ^ (a_out >> 16);

	return a_out;
} // _wh_hash_xx32

i64 wh_hash_xx64() {
	return 0;
}
