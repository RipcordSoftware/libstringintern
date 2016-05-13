#ifndef RS_LIBSTRINGINTERN_STRING_PAGES_H
#define	RS_LIBSTRINGINTERN_STRING_PAGES_H

#include "string_page.h"

#include <vector>

namespace rs {
namespace stringintern {

class StringPages {
    using Pages = std::vector<string_page_ptr>;
    using MappedPages = std::vector<Pages>;
    
public:    
    StringPages();
    
private:
    Pages pages_;
    MappedPages mappedPages_;

};

}}

#endif	/* RS_LIBSTRINGINTERN_STRING_PAGES_H */

