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

#include "string_page_archive.h"

#include <thread>

rs::stringintern::StringPageArchive::StringPageArchive(std::size_t entries) : 
    pages_(entries), index_(0) {
}

rs::stringintern::StringPagePtr rs::stringintern::StringPageArchive::NewPage(StringPage::entrycount_t entryCount, StringPage::entrysize_t entrySize) {
    StringPagePtr page;    
    
    auto pageNumber = index_.fetch_add(1, std::memory_order_relaxed);
    if (pageNumber < pages_.size()) {
        page = StringPage::New(pageNumber, entryCount, entrySize);
        pages_[pageNumber] = page;
    }
    
    return page;
}

rs::stringintern::StringPagePtr rs::stringintern::StringPageArchive::NewPage(StringPage::bufferptr_t ptr, StringPage::entrycount_t entryCount, StringPage::entrysize_t entrySize) {
    StringPagePtr page;
    
    if (!!ptr) {
        auto pageNumber = index_.fetch_add(1, std::memory_order_relaxed);
        if (pageNumber < pages_.size()) {
            page = StringPage::New(pageNumber, ptr, entryCount, entrySize);
            pages_[pageNumber] = page;
        }
    }
    
    return page;    
}

rs::stringintern::StringPagePtr rs::stringintern::StringPageArchive::GetPage(std::size_t number) const noexcept {
    StringPagePtr page;
    
    if (number < pages_.size() && number < index_.load(std::memory_order_relaxed)) {
        while (!(page = pages_[number])) {
            std::this_thread::yield();
        }
    }
    
    return page;
}

std::size_t rs::stringintern::StringPageArchive::GetPageCount() const noexcept {
    return std::min(pages_.size(), index_.load(std::memory_order_relaxed));
}

std::size_t rs::stringintern::StringPageArchive::GetEntryCount() const noexcept {
    auto entries = 0;
    auto count = GetPageCount();
    for (decltype(count) i = 0; i < count; ++i) {
        entries += GetPage(i)->GetEntryCount();
    }
    return entries;
}