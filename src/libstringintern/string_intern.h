#ifndef RS_LIBSTRINGINTERN_STRING_INTERN_H
#define	RS_LIBSTRINGINTERN_STRING_INTERN_H

#include "string_reference.h"
#include "string_pages.h"

namespace rs {
namespace stringintern {

class StringIntern {

public:
    StringIntern() {}
    StringIntern(const StringIntern&) = delete;
    
    StringReference Add(const char*);
      
    const char* ToString(const StringReference&) const;
    
private:
    StringPages pages_;
};

}}

#endif	/* RS_LIBSTRINGINTERN_STRING_INTERN_H */
