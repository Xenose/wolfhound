#include<wh/maths/hash.h>


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
    u32 a1 = 0; 
    u32 a2 = 0;
    u32 a3 = 0;
    u32 a4 = 0;

    if (16 > bytes) {
        a_out = params.seed + p5;
        goto go_step_4;
    }

    a1 = params.seed + p1 + p2;
    a2 = params.seed + p2;
    a3 = params.seed;
    a4 = params.seed - p1;

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

i64 wh_hash_xx64(_wh_hash_xx64_params params) {
    u64 index = 0;
    u64 bytes = params.buffer.bytes;
    u64 a_out = 0;

    static const u64 p1 = 0x9E3779B185EBCA87ULL;  // 0b1001111000110111011110011011000110000101111010111100101010000111
    static const u64 p2 = 0xC2B2AE3D27D4EB4FULL;  // 0b1100001010110010101011100011110100100111110101001110101101001111
    static const u64 p3 = 0x165667B19E3779F9ULL;  // 0b0001011001010110011001111011000110011110001101110111100111111001
    static const u64 p4 = 0x85EBCA77C2B2AE63ULL;  // 0b1000010111101011110010100111011111000010101100101010111001100011
    static const u64 p5 = 0x27D4EB2F165667C5ULL;  // 0b0010011111010100111010110010111100010110010101100110011111000101

    // Step 1
    u64 a1 = params.seed + p1 + p2;
    u64 a2 = params.seed + p2;
    u64 a3 = params.seed;
    u64 a4 = params.seed - p1;

    if (32 > bytes) {
        a_out = params.seed + p5;
        goto go_step_4;
    }

    // Step 2
    // Step 3
    // Step 4

go_step_4:
    return 0;
}
