#ifndef _wnt_header_time_
#define _wnt_header_time_

typedef struct {
   u32 low_date_time;
   u32 high_date_time;
} wnt_filetime_s;

extern void _wnt_get_system_time_precise_as_file_time(wnt_filetime_s* out);
extern i8 _wnt_query_performance_frequency(i32* low, i32* high);
extern i8 _wnt_query_performance_counter(i32* low, i32* high);
extern i64 _wnt_get_tick_count();

#endif /* _wnt_header_time_ */