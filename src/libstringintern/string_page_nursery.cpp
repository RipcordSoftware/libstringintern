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

rs::stringintern::StringPageNursery::StringPageNursery(colcount_t cols, rowcount_t rows, pagesize_t pageSize) :
    rows_(rows), cols_(cols), pageSize_(pageSize), pageCount_(0),
    counters_(new std::atomic<rowcount_t>[rows]),
    data_(new std::atomic<StringPage*>[rows * cols]) {
    
    // TODO: replace this with std::atomic_init
    std::fill(&counters_[0], &counters_[rows], 0);
    std::fill(&data_[0], &data_[rows * cols], nullptr);
}

rs::stringintern::StringPage* rs::stringintern::StringPageNursery::Next(rowcount_t row) {
    auto col = counters_[row].fetch_add(1, std::memory_order_relaxed) + 1;
    return Get(col, row);
}

rs::stringintern::StringPage* rs::stringintern::StringPageNursery::Current(rowcount_t row) {
    auto col = counters_[row].load(std::memory_order_relaxed);
    return Get(col, row);
}

rs::stringintern::StringPage* rs::stringintern::StringPageNursery::New(rowcount_t row, colcount_t col, StringPage* oldPage, bool matchPage) {
    auto dataIndex = (rows_ * row) + (col % cols_);
    
    auto pageNumber = pageCount_.fetch_add(1, std::memory_order_relaxed);
    auto buffer = new char[pageSize_];
    auto entrySize = StringPageSizes::pageSizes[row];
    auto entryCount = pageSize_ / entrySize;
    auto newPage = new StringPage(pageNumber, buffer, entryCount, entrySize);
    
    if (!data_[dataIndex].compare_exchange_strong(oldPage, newPage, std::memory_order_relaxed)) {
        delete newPage;
        newPage = matchPage ? nullptr : oldPage;
    }
    
    return newPage;
}

rs::stringintern::StringPage* rs::stringintern::StringPageNursery::New(rowcount_t row, StringPage* oldPage, bool matchPage) {
    auto col = counters_[row].load(std::memory_order_relaxed);
    return New(row, col, oldPage, matchPage);
}

rs::stringintern::StringPage* rs::stringintern::StringPageNursery::Get(colcount_t col, rowcount_t row) {
    auto dataIndex = (rows_ * row) + (col % cols_);
    auto page = data_[dataIndex].load(std::memory_order_relaxed);
    if (page == nullptr) {
        page = New(row, col, page);       
    }
    
    return page;
}