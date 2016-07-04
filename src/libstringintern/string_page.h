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
#include "string_page_ptr.h"

namespace rs {
namespace stringintern {

class StringPage {
    
public:
    using entrysize_t = std::uint32_t;
    using entrycount_t = std::uint32_t;    
    using pagenumber_t = std::uint16_t;
    using buffervalue_t = char;
    using bufferptr_t = buffervalue_t* const;
    using const_bufferptr_t = const buffervalue_t* const;
    using refcount_t = std::uint32_t;       
    
    static StringPagePtr New(std::size_t number, entrycount_t entryCount, entrysize_t entrySize);
    static StringPagePtr New(std::size_t number, bufferptr_t ptr, entrycount_t entryCount, entrysize_t entrySize);

    StringPage(const StringPage&) = delete;
    StringPage(const StringPage&&) = delete;
    void operator=(const StringPage&) = delete;
    ~StringPage();
    
    StringReference Add(const char*, std::size_t, StringHash::Hash);
    const char* GetString(const StringHash::Hash&) const noexcept;
    const char* GetString(const StringReference&) const noexcept;
    const char* GetString(const StringReference&, entrysize_t&) const noexcept;
    StringReference GetReference(const StringHash::Hash&) const noexcept;
    
    entrysize_t GetMaxEntrySize() const noexcept { return maxEntrySize_; }
    entrycount_t GetMaxEntryCount() const noexcept {return maxEntryCount_; }
    
    pagenumber_t GetPageNumber() const noexcept { return number_; }
    entrycount_t GetEntryCount() const noexcept { return count_; }
    
    refcount_t RefCount() const noexcept { return refCount_.load(std::memory_order_relaxed); }
    
protected:    
    StringPage(pagenumber_t number, bufferptr_t ptr, entrycount_t entryCount, entrysize_t entrySize, bool freeBuffer) noexcept;

private:
    using indexsize_t = std::uint32_t;    
    const static indexsize_t InvalidIndex;
    
    struct Entry {
    public:
        Entry() : hash(0), length(0) {
        }
        
        std::atomic<StringHash::Hash> hash;
        std::atomic<entrysize_t> length;
    };
    
    bool WaitForLength(const Entry&) const noexcept;
    
    const pagenumber_t number_;
    
    const entrysize_t maxEntrySize_;
    const entrycount_t maxEntryCount_;
    const bool freeBuffer_;

    std::vector<Entry> entries_;
    std::atomic<entrycount_t> count_;
    bufferptr_t ptr_;
    
    friend StringPagePtr;
    refcount_t AddRef() const noexcept { return refCount_.fetch_add(1, std::memory_order_relaxed) + 1; }
    refcount_t DecRef() const noexcept { 
        auto count = refCount_.fetch_sub(1, std::memory_order_relaxed) - 1; 
        if (count == 0) {
            delete this;
        }
        return count;
    }
    mutable std::atomic<refcount_t> refCount_;

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

