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

#include <atomic>
#include <vector>
#include <cstddef>

#include "string_hash.h"
#include "string_reference.h"

namespace rs {
namespace stringintern {

class StringPage {
    
public:
    using entrysize_t = std::uint32_t;
    using entrycount_t = std::uint32_t;
    using indexsize_t = std::uint32_t;
    using pagenumber_t = std::uint16_t;
    
    const static indexsize_t InvalidIndex;
    
    static StringPage* New(std::size_t number, char* ptr, entrycount_t entryCount, entrysize_t entrySize);

    StringPage(const StringPage&) = delete;
    StringPage(const StringPage&&) = delete;
    void operator=(const StringPage&) = delete;
    
    indexsize_t Add(const char*, entrysize_t, StringHash::Hash);
    const char* GetString(StringHash::Hash) const noexcept;
    StringReference GetReference(StringHash::Hash) const noexcept;
    
    entrysize_t EntrySize() const noexcept;
    entrycount_t EntryCount() const noexcept;
    
    pagenumber_t Number() const noexcept;
    
protected:    
    StringPage(pagenumber_t number, char* ptr, entrycount_t entryCount, entrysize_t entrySize) noexcept;

private:
    
    struct Entry {
    public:
        Entry() : hash(0), length(0) {
        }
        
        std::atomic<StringHash::Hash> hash;
        entrysize_t length;
    };
    
    const pagenumber_t number_;
    char* const ptr_;
    const entrysize_t entrySize_;
    const indexsize_t indexMask_;
    
    std::vector<Entry> entries_;
};

}}

#endif	/* RS_LIBSTRINGINTERN_STRING_PAGE_H */

