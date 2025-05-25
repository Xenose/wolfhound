[common.h](wh/common.h)
[math.h](wh/params/math.h)

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
