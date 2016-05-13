#ifndef RS_LIBSTRINGINTERN_STRING_PAGE_H
#define	RS_LIBSTRINGINTERN_STRING_PAGE_H

#include <memory>

namespace rs {
namespace stringintern {

class StringPage {
public:
    
    StringPage(uint32_t pageSize, uint32_t entrySize);
    
    uint32_t EntrySize();

private:
    uint32_t pageSize_;
    uint32_t entrySize_;
};

using string_page_ptr = std::shared_ptr<StringPage>;

}}

#endif	/* RS_LIBSTRINGINTERN_STRING_PAGE_H */

