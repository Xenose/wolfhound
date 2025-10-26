[common.h](wh/common.h)
[math.h](wh/params/math.h)

# wh_abs
This function is a non branching abs functions for signed and
unsigned integers, for float and doubles the normal abs from
maths.h is called.

## Return value
Returns a positive value from the original value.

# wh_hash_simple
```c
	int64_t wh_hash_simple(const char* str, u64 limit, u64 length : optional)
```

| Parameter     | Optional  | Type     | Designation | Description                     |
| ------------- | --------- | -------- | ----------- | ------------------------------- |
| string        | NO        | char*    | .str        | The string that will be hashed. |
| slot limit    | NO        | uint64_t | .limit      | The limit of slots.             |
| string length | YES       | uint64_t | .length     | The length of the string        |

## Return value
