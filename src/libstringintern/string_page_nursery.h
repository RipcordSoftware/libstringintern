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

#ifndef RS_LIBSTRINGINTERN_STRING_PAGE_NURSERY_H
#define	RS_LIBSTRINGINTERN_STRING_PAGE_NURSERY_H

#include <atomic>
#include <functional>
#include <cstddef>

#include "string_page.h"

namespace rs {
namespace stringintern {

class StringPageNursery {
public:
    
    using pagesize_t = std::uint32_t;
    using rowcount_t = std::uint32_t;
    using colcount_t = std::uint32_t;
    
    class Iterator {
    public:        
        Iterator(const Iterator& rhs) noexcept : cols_(rhs.cols_), row_(rhs.row_), start_(rhs.start_), pos_(rhs.pos_) {}
        Iterator& operator=(const Iterator& rhs) noexcept { cols_ = rhs.cols_; row_ = rhs.row_; start_ = rhs.start_; pos_ = rhs.pos_; }
        
        bool operator!() const noexcept { return pos_ >= (start_ + cols_); }
        
    private:
        friend StringPageNursery;
        
        Iterator(colcount_t cols, rowcount_t row, colcount_t start) noexcept : cols_(cols), row_(row), start_(start), pos_(start) {}
        rowcount_t operator++(int) noexcept { return pos_++; }        
        
        colcount_t start_;
        colcount_t pos_;
        rowcount_t row_;
        colcount_t cols_;
    };
    
    using NewPageFunc = std::function<StringPagePtr(rowcount_t, StringPage::entrycount_t, StringPage::entrysize_t)>;

    StringPageNursery(colcount_t, rowcount_t, pagesize_t, NewPageFunc newPageFunc);
    StringPageNursery(const StringPageNursery&) = delete;
    StringPageNursery(const StringPageNursery&&) = delete;
    void operator=(const StringPageNursery&) = delete;

    Iterator Iter(rowcount_t row) const noexcept;
    StringPagePtr New(rowcount_t);
    StringPagePtr Next(Iterator& iter);
    
    inline rowcount_t Rows() const noexcept { return rows_; }
    inline colcount_t Cols() const noexcept { return cols_; }
    
    std::vector<StringPagePtr> GetPages(rowcount_t);
    std::vector<StringPage::entrycount_t> GetPageEntryCounts(rowcount_t);
    
private:
    
    StringPagePtr Get(colcount_t, rowcount_t);
    
    NewPageFunc newPageFunc_;
    
    std::vector<std::atomic<rowcount_t>> counters_;
    std::vector<StringPagePtr> data_;
    
    const colcount_t cols_;
    const rowcount_t rows_;
    const pagesize_t pageSize_;

};

}}

#endif	/* RS_LIBSTRINGINTERN_STRING_PAGE_NURSERY_H */

