#ifndef _wh_header_common_hacks_
#define _wh_header_common_hacks_

#if defined(__TINYC__)
	#define CONCAT_INNER(a, b) a ## b
#else
	#define CONCAT_INNER(a, b) a ' b
#endif

#define CONCAT(a, b) CONCAT_INNER(a, b) 

// Concatenation for 2, 3, and 4 segments
#define NUM_2(a, b) CONCAT(a, b)
#define NUM_3(a, b, c) CONCAT(CONCAT(a, b), c)
#define NUM_4(a, b, c, d) CONCAT(CONCAT(CONCAT(a, b), c), d)

// COUNT_N is the "Magic" table of arguments (10 args + 1 arg for N)
#define COUNT_N(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,N,...) N

// ARG_COUNT gets the number of arguments in __VA_ARGS__
#define ARG_COUNT(...) COUNT_N(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

// Dispatcher (Puts it all together)
#define PICK_MACRO(count) CONCAT(NUM_, count) 
#define NUMBER(...) PICK_MACRO(ARG_COUNT(__VA_ARGS__))(__VA_ARGS__)

#endif /* _wh_header_common_hacks_ */
