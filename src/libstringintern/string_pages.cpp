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

#include "string_pages.h"
#include "string_page_sizes.h"
#include "string_hash.h"

#include <cstring>

#include <algorithm>

rs::stringintern::StringPages::StringPages() :
    nursery_(new std::atomic<StringPage*>[nurseryRowSize_ * StringPageSizes::pageSizesMaxIndex]) {
    std::fill(nurseryCounters_.begin(), nurseryCounters_.end(), 0);
}

rs::stringintern::StringReference rs::stringintern::StringPages::Add(const char* str) {
    StringReference ref;
    
    if (!!str) {
        auto len = std::strlen(str);
        auto hash = StringHash::Get(str, len);
        ref = Add(str, len, hash);
    }
    
    return ref;
}

rs::stringintern::StringReference rs::stringintern::StringPages::Add(const char* str, std::size_t len, StringHash::Hash hash) {
    StringReference stringRef;
    
    if (!!str && len > 0) {
        auto pageSizeIndex = StringPageSizes::GetPageSizeIndex(len);
        if (!!pageSizeIndex) {
            auto start = nurseryCounters_[pageSizeIndex].load(std::memory_order_relaxed);
            
            StringPage* page = nullptr;
            auto pageIndex = StringPage::InvalidIndex;
            for (auto i = start; (i < start + nurseryRowSize_) && pageIndex == StringPage::InvalidIndex; ++i) {
                auto nurseryIndex = (pageSizeIndex * nurseryRowSize_) + (i % nurseryRowSize_);
                page = nursery_[nurseryIndex].load(std::memory_order_relaxed);

                if (page == nullptr) {
                    auto entrySize = StringPageSizes::GetPageEntrySize(pageSizeIndex);                
                    page = AllocatePage(nurseryIndex, entrySize);
                }

                pageIndex = page->Add(str, len, hash);
            }
            
            if (pageIndex == StringPage::InvalidIndex) {
                // TODO: push the page to the archive and create a new one
            }
            
            stringRef = StringReference(page->Number(), pageIndex);
        }        
    }
    
    return stringRef;
}

// TODO: store the page in the index table
rs::stringintern::StringPage* rs::stringintern::StringPages::AllocatePage(std::uint32_t nurseryIndex, StringPage::entrysize_t entrySize) {
    auto number = pageCount_.fetch_add(1, std::memory_order_relaxed);
    auto buffer = new char[stringPageSizeBytes_];
    auto entryCount = stringPageSizeBytes_ / entrySize;
    auto newPage = new StringPage(number, buffer, entryCount, entrySize);
                
    StringPage* page = nullptr;
    if (nursery_[nurseryIndex].compare_exchange_strong(page, newPage)) {                    
        page = newPage;
    } else {                
        delete[] newPage;
    }
    
    return page;
}