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

#include "string_page_catalog.h"

#include <algorithm>

rs::stringintern::StringPageCatalog::StringPageCatalog(colcount_t cols, rowcount_t rows) :
    rows_(rows), cols_(cols), totalPages_(0), counters_(rows), data_(rows * cols) {
    std::for_each(counters_.begin(), counters_.end(), [&](decltype(counters_[0])& c) { c.store(0, std::memory_order_relaxed); });
    std::for_each(data_.begin(), data_.end(), [&](decltype(data_[0])& d) { d.store(nullptr, std::memory_order_relaxed); });
}

bool rs::stringintern::StringPageCatalog::Add(rowcount_t row, StringPage* page) {
    auto added = false;
    
    if (page && row < rows_) {
        auto col = counters_[row].load(std::memory_order_relaxed);
        while (!added && col < cols_) {
            StringPage* nullPage = nullptr;
            added = data_[(cols_ * row) + col].compare_exchange_strong(nullPage, page, std::memory_order_relaxed);
            ++col;
        }

        if (added) {
            auto currentCol = counters_[row].load(std::memory_order_relaxed);
            while (col > currentCol) {
                if (counters_[row].compare_exchange_strong(currentCol, col, std::memory_order_relaxed)) {
                    currentCol = col;
                }
            }
            
            totalPages_.fetch_add(1, std::memory_order_relaxed);
        }       
    }
    
    return added;
}

rs::stringintern::StringReference rs::stringintern::StringPageCatalog::Find(rowcount_t row, StringHash::Hash hash) const noexcept {
    StringReference ref;
    
    if (row < rows_) {
        auto cols = counters_[row].load(std::memory_order_relaxed);

        decltype(cols) i = 0;
        for (; !ref && i < cols; ++i) {
            auto page = data_[(cols_ * row) + i].load(std::memory_order_relaxed);
            ref = page->GetReference(hash);
        }

        if (i > 0 && !ref) {
            cols = counters_[row].load(std::memory_order_relaxed);
            if (i < cols) {
                for (; !ref && i < cols; ++i) {
                    auto page = data_[(cols_ * row) + i].load(std::memory_order_relaxed);
                    ref = page->GetReference(hash);
                }
            }
        }
    }
    
    return ref;
}

std::vector<rs::stringintern::StringPage*> rs::stringintern::StringPageCatalog::GetPages(rowcount_t row) const {
    std::vector<StringPage*> rowPages;
    
    if (row < rows_) {
        auto cols = counters_[row].load(std::memory_order_relaxed);
        rowPages.reserve(cols);

        std::for_each(&data_[cols_ * row], &data_[(cols_ * row) + cols], [&](decltype(data_[0])& d) {
            auto page = d.load(std::memory_order_relaxed);
            rowPages.emplace_back(page);
        });
    }
    
    return rowPages;    
}