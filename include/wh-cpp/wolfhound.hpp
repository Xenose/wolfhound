#ifndef _wh_header_hpp_wolfhound_
#define _wh_header_hpp_wolfhound_

#include<wh-types/wolfhound.h>

namespace wh {

class instance_c {
public:
private:
    wh_instance_s* _instance = nullptr;
public:
    instance_c(const char* name, int arc, char* const* arv);
    ~instance_c();

    void loop();
};

} /* end namespace wh */

#endif /* _wh_header_hpp_wolfhound_ */
