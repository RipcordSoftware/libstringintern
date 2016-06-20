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

#ifndef RS_LIBSTRINGINTERN_STRING_PAGE_PTR_H
#define	RS_LIBSTRINGINTERN_STRING_PAGE_PTR_H

#include <atomic>

namespace rs {
namespace stringintern {

class StringPage;

/**
 * A smart pointer impl for StringPages - reasoning:
 * G++ 4.9 doesn't support atomic operations on std::shared_ptr<>, so this
 * pointer implementation takes the strain until 4.9 ages out
**/
class StringPagePtr final {
public:
    StringPagePtr() noexcept : ptr_{nullptr} {}    
    StringPagePtr(std::nullptr_t) noexcept : StringPagePtr() {}
    explicit StringPagePtr(StringPage*) noexcept;
    StringPagePtr(const StringPagePtr& rhs) noexcept;
    StringPagePtr(StringPagePtr&& rhs) noexcept;
    ~StringPagePtr() noexcept;
    
    StringPagePtr& operator=(const StringPagePtr& rhs) noexcept;
    StringPagePtr& operator=(StringPagePtr&& rhs) noexcept;

    bool operator!() const noexcept { return !get(); }
    
    StringPage* operator->() const noexcept { return get(); }
    StringPage* get() const noexcept { return ptr_.load(std::memory_order_relaxed); }
    
    std::size_t RefCount() const noexcept;
    
    bool compare_exchange_strong(StringPagePtr&, const StringPagePtr&, std::memory_order) noexcept;
    
private:
    friend bool operator==(const StringPagePtr& lhs, const StringPagePtr& rhs) noexcept;
    friend bool operator!=(const StringPagePtr& lhs, const StringPagePtr& rhs) noexcept;
    
    std::atomic<StringPage*> ptr_;    
};

inline bool operator==(const StringPagePtr& lhs, const StringPagePtr& rhs) noexcept {
    return lhs.get() == rhs.get();
}

inline bool operator!=(const StringPagePtr& lhs, const StringPagePtr& rhs) noexcept {
    return lhs.get() != rhs.get();
}

}}

#endif	/* RS_LIBSTRINGINTERN_STRING_PAGE_PTR_H */

