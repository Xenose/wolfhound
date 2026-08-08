#ifndef _wh_header_common_const_
#define _wh_header_common_const_

// Base unit: 1 kilo-unit = 1 millimeter
#define WH_1KU 1024

// Unit hierarchy
#define WH_1MU (WH_1KU * 1024) // Mega-unit
#define WH_1GU (WH_1MU * 1024) // Giga-unit
#define WH_1TU (WH_1GU * 1024) // Tera-unit

// Convenience aliases
#define WH_1MM WH_1KU // 1 millimeter in units

#endif /* _wh_header_common_const_ */
