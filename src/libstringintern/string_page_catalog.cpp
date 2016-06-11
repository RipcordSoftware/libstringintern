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

rs::stringintern::StringPageCatalog::StringPageCatalog(colcount_t cols, rowcount_t rows) :
    rows_(rows), cols_(cols), totalPages_(0),
    counters_(new std::atomic<rowcount_t>[rows]),
    data_(new StringPage*[rows * cols]) {
    std::fill(&counters_[0], &counters_[rows], 0);
    std::fill(&data_[0], &data_[rows * cols], nullptr);
}

bool rs::stringintern::StringPageCatalog::Add(rowcount_t row, StringPage* page) {
    auto added = false;
    
    if (row < rows_) {
        auto col = counters_[row].fetch_add(1, std::memory_order_relaxed);
        std::atomic_thread_fence(std::memory_order_acquire);
        if (col < cols_) {
            data_[(rows_ * row) + col] = page;
            std::atomic_thread_fence(std::memory_order_release);
            totalPages_.fetch_add(1, std::memory_order_relaxed);
            added = true;
        }
    }
    
    return added;
}

rs::stringintern::StringReference rs::stringintern::StringPageCatalog::Find(rowcount_t row, StringHash::Hash hash) const noexcept {
    StringReference ref;
    
    if (row < rows_) {
        auto cols = counters_[row].load(std::memory_order_relaxed);
        std::atomic_thread_fence(std::memory_order_acquire);

        decltype(cols) i = 0;
        for (; !ref && i < cols; ++i) {
            auto page = data_[(rows_ * row) + i];
            ref = page->GetReference(hash);
        }

        if (!ref) {
            cols = counters_[row].load(std::memory_order_relaxed);
            if (i < cols) {
                std::atomic_thread_fence(std::memory_order_acquire);
                for (; !ref && i < cols; ++i) {
                    auto page = data_[(rows_ * row) + i];
                    ref = page->GetReference(hash);
                }
            }
        }
    }
    
    return ref;
}