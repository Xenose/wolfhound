#ifndef _wh_header_common_prefix_
#define _wh_header_common_prefix_

#ifndef __cplusplus
    #define WH_C()
    #define WH_C_END()
#else
    #define WH_C() extern "C" {
    #define WH_C_END() }
#endif

#endif /* _wh_header_common_prefix_ */
