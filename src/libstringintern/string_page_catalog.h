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

#ifndef RS_LIBSTRINGINTERN_STRING_PAGE_CATALOG_H
#define	RS_LIBSTRINGINTERN_STRING_PAGE_CATALOG_H

#include <atomic>
#include <vector>

#include "string_page.h"
#include "string_hash.h"
#include "string_reference.h"

namespace rs {
namespace stringintern {

class StringPageCatalog final {
public:
    
    using rowcount_t = std::uint32_t;
    using colcount_t = std::uint32_t;
    using pagecount_t = std::uint32_t;
    
    StringPageCatalog(colcount_t, rowcount_t);
    StringPageCatalog(const StringPageCatalog&) = delete;
    StringPageCatalog(const StringPageCatalog&&) = delete;
    void operator=(const StringPageCatalog&) = delete;
    
    bool Add(rowcount_t, StringPagePtr);
    
    StringReference Find(rowcount_t, StringHash::Hash) const noexcept;
    
    inline rowcount_t Rows() const noexcept { return rows_; }
    inline colcount_t Cols() const noexcept { return cols_; }
    
    inline pagecount_t GetPageCount() const noexcept { return totalPages_.load(std::memory_order_relaxed); }
    
    std::vector<StringPagePtr> GetPages(rowcount_t) const;
        
private:
    
    std::vector<std::atomic<rowcount_t>> counters_;
    std::vector<StringPagePtr> data_;

    const colcount_t cols_;
    const rowcount_t rows_;
    
    std::atomic<pagecount_t> totalPages_;
};

}}

#endif	/* RS_LIBSTRINGINTERN_STRING_PAGE_CATALOG_H */

