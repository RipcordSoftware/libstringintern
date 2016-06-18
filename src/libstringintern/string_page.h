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
#include <memory>

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
    using buffervalue_t = char;
    using bufferptr_t = buffervalue_t* const;
    
    const static indexsize_t InvalidIndex;
    
    static StringPage* New(std::size_t number, entrycount_t entryCount, entrysize_t entrySize);
    static StringPage* New(std::size_t number, bufferptr_t ptr, entrycount_t entryCount, entrysize_t entrySize);

    StringPage(const StringPage&) = delete;
    StringPage(const StringPage&&) = delete;
    void operator=(const StringPage&) = delete;
    ~StringPage();
    
    indexsize_t Add(const char*, std::size_t, StringHash::Hash);
    const char* GetString(StringHash::Hash) const noexcept;
    StringReference GetReference(StringHash::Hash) const noexcept;
    
    entrysize_t EntrySize() const noexcept;
    entrycount_t EntryCount() const noexcept;
    
    pagenumber_t Number() const noexcept;
    entrycount_t Count() const noexcept;
    
protected:    
    StringPage(pagenumber_t number, char* ptr, entrycount_t entryCount, entrysize_t entrySize, bool freeBuffer = true) noexcept;

private:
    
    struct Entry {
    public:
        Entry() : hash(0), length(0) {
        }
        
        std::atomic<StringHash::Hash> hash;
        std::atomic<entrysize_t> length;
    };
    
    const pagenumber_t number_;
    
    const entrysize_t entrySize_;
    const entrycount_t entryCount_;
    const bool freeBuffer_;

    std::vector<Entry> entries_;
    std::atomic<entrycount_t> count_;
    bufferptr_t ptr_;

    // track the number of times we see a zero hash (see below)
    std::atomic<std::uint32_t> zeroHashCount_;
    
    /**************************************************************************/
    // Note on zero hashes:
    // A zero value hash is a special thing, it can't be easily tracked since
    // an unitialized hash of 0 == an initialized hash of 0.
    // The problem is solved by tracking the number of times we see the zero
    // hash. There is a race handling the first zero hash and another zero hash 
    // appearing, so we only ever count the first zero hash in the page entry
    // count and tolerate the extra copy we might see (the string data is the
    // same anyway). Outside the race window we have special handling for zero
    // hashes where we know we already have one in the page.
    // Outside unit testing this case is highly unlikely to ever happen.

};

}}

#endif	/* RS_LIBSTRINGINTERN_STRING_PAGE_H */

