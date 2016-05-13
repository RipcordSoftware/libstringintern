#ifndef RS_LIBSTRINGINTERN_STRING_INTERN_H
#define	RS_LIBSTRINGINTERN_STRING_INTERN_H

#include "string_reference.h"
#include "string_page.h"

#include <vector>

namespace rs {
namespace stringintern {

class StringIntern {
public:
    StringIntern() {}
    StringIntern(const StringIntern&) = delete;
    
    StringReference Add(const char*);
      
    const char* ToString(const StringReference&) const;
    
private:
    
    std::vector<StringPage> pages_;

};

}}

#endif	/* RS_LIBSTRINGINTERN_STRING_INTERN_H */
