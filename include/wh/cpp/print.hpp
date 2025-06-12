#ifndef _wh_header_hpp_print_
#define _wh_header_hpp_print_

#include<string>
#include<vector>
#include<any>

#include<wh/print.h>

namespace wh {

class print { 
public:
private:
	std::string _format;
	_wh_print_params _params;
public:
	print(std::string format);
	print& fd(int fd);

	template<typename... Args>
	inline i64 out(Args&&... args) {
		return _wh_print(_params, std::forward<Args>(args)...);
	}
private:
};

}
#endif /* _wh_header_hpp_print_ */
