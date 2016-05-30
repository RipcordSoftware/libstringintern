/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Ripcord Software Ltd
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
**/

#ifndef RS_LIBSTRINGINTERN_STRING_PAGE_H
#define	RS_LIBSTRINGINTERN_STRING_PAGE_H

#include <memory>
#include <atomic>
#include <cstddef>

#include "string_hash.h"

namespace rs {
namespace stringintern {

class StringPage {
    
public:    
    using pagesize_t = std::uint32_t;
    using entrysize_t = std::uint32_t;
    using countsize_t = std::uint32_t;
    using indexsize_t = std::uint32_t;
    
    const static indexsize_t InvalidIndex;
    
    StringPage(void* ptr, pagesize_t pageSize, entrysize_t entrySize) noexcept;
    
    indexsize_t Add(const char*, std::size_t, StringHash::Hash);
    const char* Get(StringHash::Hash) const noexcept;
    
    entrysize_t EntrySize() const noexcept;
    countsize_t EntryCount() const noexcept;       

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
    
    inline entrysize_t CalculateEntrySize(std::size_t len) const noexcept { 
        return overheadSize_ + len; 
    }
    
    inline Entry* GetEntry(indexsize_t index) const noexcept {
        auto ptr = reinterpret_cast<std::uintptr_t>(ptr_);
        ptr += index * entrySize_;
        return reinterpret_cast<Entry*>(ptr);
    }   
    
    void AllocPage();
    
    void* ptr_;
    const pagesize_t pageSize_;
    const entrysize_t entrySize_;
    const indexsize_t indexMask_;
    static const entrysize_t overheadSize_ = offsetof(Entry, str) + 1;
};

using string_page_ptr = std::shared_ptr<StringPage>;

}}

#endif	/* RS_LIBSTRINGINTERN_STRING_PAGE_H */

