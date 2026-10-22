#include<wh-testing/unit.h>
#include<wh/maths/core.h>
#include<wh-core/maths/hash.h>

typedef struct {
    u64 hash;
    const char* v;
} hash_pair_s;

i64 test_simple(wh_unit_test_s* info) {

    i64 hash = 0;
    hash_pair_s pairs[] = {
        { -1,   "" },
        { 166,  "a" },
        { 33,   "abc" },
        { 4,    "cpp" },
        { 8,    "cpd" },
        { 187,  "message digest" },
        { 238,  "abcdefghijklmnopqrstuvwxyz" },
    };

    wh_for(int, i, sizeof(pairs) / sizeof(hash_pair_s)) {
        hash = wh_hash_simple((void*)pairs[i].v, 256, strlen(pairs[i].v));
        WH_TEST_INT64EQ(info, hash, pairs[i].hash);
    }

    return 0;
}

i64 test_xx32(wh_unit_test_s* info) {
    i64 hash = 0;
    hash_pair_s pairs[] = {
        { 0x02CC5D05, "" },
        { 0x550D7456, "a" },
        { 0x32D153FF, "abc" },
        { 0x7C948494, "message digest" },
        { 0x63A14D5F, "abcdefghijklmnopqrstuvwxyz" },
    };

    wh_for(int, i, sizeof(pairs) / sizeof(hash_pair_s)) {
        hash = wh_hash_xx32((void*)pairs[i].v, strlen(pairs[i].v));
        WH_TEST_INT64EQ(info, hash, pairs[i].hash);
    }

    return 0;
}

i64 init(wh_unit_test_s* info) {
    test_simple(info);
    test_xx32(info);
    return 0;
}
