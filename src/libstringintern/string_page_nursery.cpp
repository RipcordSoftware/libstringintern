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

#include "string_page_nursery.h"
#include "string_page_sizes.h"

#include <algorithm>

rs::stringintern::StringPageNursery::StringPageNursery(colcount_t cols, rowcount_t rows, pagesize_t pageSize, NewPageFunc newPageFunc) :
    rows_(rows), cols_(cols), pageSize_(pageSize),
    counters_(rows), data_(rows * cols), newPageFunc_(newPageFunc) {
    
    std::for_each(counters_.begin(), counters_.end(), [&](decltype(counters_[0])& c) { c.store(0, std::memory_order_relaxed); });
}

rs::stringintern::StringPagePtr rs::stringintern::StringPageNursery::New(rowcount_t row) {    
    auto entrySize = StringPageSizes::GetEntrySize(row);
    auto entryCount = pageSize_ / entrySize;
    auto newPage = newPageFunc_(row, entryCount, entrySize);
    
    auto col = counters_[row].fetch_add(1, std::memory_order_relaxed);
    auto dataIndex = (cols_ * row) + (col % cols_);
    data_[dataIndex].exchange(newPage, std::memory_order_relaxed);
    
    return newPage;
}

rs::stringintern::StringPagePtr rs::stringintern::StringPageNursery::Get(colcount_t col, rowcount_t row) {
    auto dataIndex = (cols_ * row) + (col % cols_);
    auto page = data_[dataIndex];
    if (!page) {
        page = New(row);
    }
    
    return page;
}

rs::stringintern::StringPageNursery::Iterator rs::stringintern::StringPageNursery::Iter(rowcount_t row) const noexcept {
    auto start = counters_[row].load(std::memory_order_relaxed);
    start = start > cols_ ? (start % cols_) : 0;
    return Iterator{cols_, row, start};
}

rs::stringintern::StringPagePtr rs::stringintern::StringPageNursery::Next(Iterator& iter) {    
    if (!!iter) {
        auto col = iter++;
        return Get(col, iter.row_);
    } else {
        return StringPagePtr{};
    }
}