#ifndef RS_LIBSTRINGINTERN_STRING_PAGE_H
#define	RS_LIBSTRINGINTERN_STRING_PAGE_H

#include <memory>
#include <mutex>
#include <atomic>
#include <cstddef>

#include "string_hash.h"

namespace rs {
namespace stringintern {

// TODO: alloc outside the class
class StringPage {
    
public:    
    using pagesize_t = std::uint32_t;
    using entrysize_t = std::uint32_t;
    using countsize_t = std::uint32_t;
    using indexsize_t = std::uint32_t;
    
    const static indexsize_t InvalidIndex;
    
    StringPage(pagesize_t pageSize, entrysize_t entrySize);
    
    indexsize_t Add(const char*, std::size_t, StringHash::Hash);
    
    entrysize_t EntrySize() const;
    countsize_t EntryCount() const;
    
    static entrysize_t CalculateEntrySize(std::size_t);

private:    
    
#pragma pack(push)
#pragma pack(1)
    struct Entry {
    public:
        std::atomic<StringHash::Hash> hash;
        entrysize_t length;
        char str[0]{};
    };
#pragma pack(pop)
    
    void AllocPage();
        
    std::once_flag ptrFlag_;
    
    char* ptr_;
    const pagesize_t pageSize_;
    const entrysize_t entrySize_;
    const indexsize_t indexMask_;
    static const entrysize_t overheadSize_ = offsetof(Entry, str) + 1;
};

using string_page_ptr = std::shared_ptr<StringPage>;

}}

#endif	/* RS_LIBSTRINGINTERN_STRING_PAGE_H */

