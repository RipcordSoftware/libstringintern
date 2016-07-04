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
#include <thread>
#include <chrono>

#include "string_intern_exception.h"

const rs::stringintern::StringPage::indexsize_t rs::stringintern::StringPage::InvalidIndex = -1;

rs::stringintern::StringPagePtr rs::stringintern::StringPage::New(std::size_t number, entrycount_t entryCount, entrysize_t entrySize) {
    StringPagePtr page;

    if (number < StringReference::MaxNumber()) {
        std::uint64_t pageSize = entryCount * entrySize;
        auto ptr = new char[pageSize];

        if (ptr != nullptr) {
            page = StringPagePtr(new StringPage(number, ptr, entryCount, entrySize, true));
        }
    }

    return page;
}

rs::stringintern::StringPagePtr rs::stringintern::StringPage::New(std::size_t number, bufferptr_t ptr, entrycount_t entryCount, entrysize_t entrySize) {
    StringPagePtr page;

    if (number < StringReference::MaxNumber() && !!ptr) {
        page = StringPagePtr(new StringPage(number, ptr, entryCount, entrySize, false));
    }

    return page;
}

rs::stringintern::StringPage::StringPage(pagenumber_t number, bufferptr_t ptr, entrycount_t entryCount, entrysize_t entrySize, bool freeBuffer) noexcept
    : number_(number), ptr_(ptr), maxEntrySize_(entrySize), maxEntryCount_(entryCount), entries_(entryCount), zeroHashCount_(0), count_(0), freeBuffer_(freeBuffer), refCount_(0) {
    
}

rs::stringintern::StringPage::~StringPage() {
    if (freeBuffer_) {
        delete[] ptr_;
    }
}

rs::stringintern::StringReference rs::stringintern::StringPage::Add(const char* str, std::size_t len, StringHash::Hash hash) {
    if (len == 0 || len >= maxEntrySize_) {
        throw StringInternException("Bad string size for page");
    }
    
    auto index = hash % maxEntryCount_;

    if (index == 0 && zeroHashCount_.load(std::memory_order_relaxed) > 0) {
        index = hash == 0 ? 0 : InvalidIndex;
    } else {
        decltype(zeroHashCount_.operator++()) zeroHashState = 0;
        if (hash == 0) {
            // the state is 0 on first zero hash occurrence and 1 otherwise
            zeroHashState = zeroHashCount_.fetch_add(1, std::memory_order_relaxed) > 0 ? 1 : 0;
        }

        auto& entry = entries_[index];
        auto entryHash = entry.hash.load(std::memory_order_relaxed);
        if (entryHash == 0 && entry.hash.compare_exchange_strong(entryHash, hash, std::memory_order_relaxed)) {
            auto ptr = ptr_ + (maxEntrySize_ * index);
            std::memcpy(ptr, str, len + 1);
            std::atomic_thread_fence(std::memory_order_release);
            entry.length.store(len, std::memory_order_relaxed);

            // increase the entry count, taking into account the zero hash state
            count_.fetch_add(1 - zeroHashState, std::memory_order_relaxed);
        } else if (entryHash != hash) {
            index = InvalidIndex;
        }
    }
    
    return index != InvalidIndex ? StringReference(number_, index) : StringReference();
}

const char* rs::stringintern::StringPage::GetString(const StringHash::Hash& hash) const noexcept {
    const char* str = nullptr;

    if (hash == 0) {
        if (zeroHashCount_.load(std::memory_order_relaxed) > 0) {
            auto& entry = entries_[0];
            if (WaitForLength(entry)) {
                std::atomic_thread_fence(std::memory_order_acquire);
                str = ptr_;
            }
        }
    } else {
        auto index = hash % maxEntryCount_;
        auto& entry = entries_[index];
        if (entry.hash.load(std::memory_order_relaxed) == hash) {
            if (WaitForLength(entry)) {
                std::atomic_thread_fence(std::memory_order_acquire);
                str = ptr_ + (maxEntrySize_ * index);
            }
        }
    }

    return str;
}

const char* rs::stringintern::StringPage::GetString(const StringReference& ref) const noexcept {
    entrysize_t entrySize = 0;
    return GetString(ref, entrySize);
}

const char* rs::stringintern::StringPage::GetString(const StringReference& ref, entrysize_t& entrySize) const noexcept {
    const char* str = nullptr;
    
    if (number_ == ref.Number()) {
        auto index = ref.Index();
        auto& entry = entries_[index];
        if (WaitForLength(entry)) {
            std::atomic_thread_fence(std::memory_order_acquire);
            str = ptr_ + (maxEntrySize_ * index);
            entrySize = entry.length.load(std::memory_order_relaxed);
        }
    }

    return str;
}

rs::stringintern::StringReference rs::stringintern::StringPage::GetReference(const StringHash::Hash& hash) const noexcept {
    StringReference ref;
    
    if (hash == 0) {
        if (zeroHashCount_.load(std::memory_order_relaxed) > 0) {
            auto& entry = entries_[0];
            if (WaitForLength(entry)) {
                ref = StringReference(number_, 0);
            }
        }
    } else {
        auto index = hash % maxEntryCount_;
        auto& entry = entries_[index];
        if (entry.hash.load(std::memory_order_relaxed) == hash) {
            if (WaitForLength(entry)) {
                ref = StringReference(number_, index);
            }
        }
    }

    return ref;
}

bool rs::stringintern::StringPage::WaitForLength(const Entry& entry) const noexcept {
    auto status = false;
    auto count = 1000;
    
    while (!(status = (entry.length.load(std::memory_order_relaxed) != 0)) && --count > 0) {
        std::this_thread::yield();
    }
    
    if (!status) {
        count = 10;
        while (!status && --count > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            status = entry.length.load(std::memory_order_relaxed) != 0;
        }
    }
    
    return status;
}