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

#ifndef RS_LIBSTRINGINTERN_STRING_PAGE_SIZES_H
#define RS_LIBSTRINGINTERN_STRING_PAGE_SIZES_H

#include "string_page.h"

#include <limits>

namespace rs {
namespace stringintern {

class StringPageSizes final {
public:
    class Index {
    public:
        Index() : index_(std::numeric_limits<StringPage::entrycount_t>::max()) {}
        Index(StringPage::entrycount_t index) : index_(index) {}
        
        operator StringPage::entrycount_t() const noexcept { return index_; }
        
        bool operator!() const noexcept { return index_ == std::numeric_limits<StringPage::entrycount_t>::max(); }
        
    private:
        const StringPage::entrycount_t index_;
    };
    
    StringPageSizes() = delete;
    StringPageSizes(const StringPageSizes&) = delete;
    StringPageSizes(const StringPageSizes&&) = delete;
    void operator =(const StringPageSizes&) = delete;
    
    static Index GetIndex(StringPage::entrysize_t len);
    static Index GetMaxIndex();
    static StringPage::entrysize_t GetEntrySize(const Index&);

private:    
    const static StringPage::entrysize_t pageSizes[];
    const static StringPage::entrysize_t pageSizesMaxIndex;

};

}}

#endif	/* RS_LIBSTRINGINTERN_STRING_PAGE_SIZES_H */

