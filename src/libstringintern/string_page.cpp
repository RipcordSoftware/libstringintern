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

#include "string_page.h"

#include <cstddef>
#include <cstring>
#include <atomic>

#include "string_intern_exception.h"

const rs::stringintern::StringPage::indexsize_t rs::stringintern::StringPage::InvalidIndex = -1;

rs::stringintern::StringPage::StringPage(pagesize_t pageSize, entrysize_t entrySize)
    : ptr_(nullptr), pageSize_(pageSize), entrySize_(entrySize), indexMask_((pageSize / entrySize) - 1) {
    
}

rs::stringintern::StringPage::entrysize_t rs::stringintern::StringPage::EntrySize() const {
    return entrySize_;
}

rs::stringintern::StringPage::countsize_t rs::stringintern::StringPage::EntryCount() const {
    return pageSize_ / entrySize_;
}

rs::stringintern::StringPage::indexsize_t rs::stringintern::StringPage::Add(const char* str, std::size_t len, StringHash::Hash hash) {
    if (CalculateEntrySize(len) >= entrySize_) {
        throw StringInternException("Bad string size for page");
    }
    
    std::call_once(ptrFlag_, &StringPage::AllocPage, this);
    
    auto index = hash & indexMask_;
    auto offset = index * entrySize_;
    auto entry = reinterpret_cast<Entry*>(ptr_ + offset);
    
    auto entryHash = entry->hash.load(std::memory_order_relaxed);
    std::atomic_thread_fence(std::memory_order_acquire);
    if (entryHash == 0) {
        entry->length = len;
        std::memcpy(entry->str, str, len + 1);
        std::atomic_thread_fence(std::memory_order_release);
        entry->hash.store(hash, std::memory_order_relaxed);
    } else if (entryHash != hash) {
        index = InvalidIndex;
    }
    
    return index;
}

rs::stringintern::StringPage::entrysize_t rs::stringintern::StringPage::CalculateEntrySize(std::size_t len) {
    return overheadSize_ + len;    
}

void rs::stringintern::StringPage::AllocPage() {
    ptr_ = new char[pageSize_];
}