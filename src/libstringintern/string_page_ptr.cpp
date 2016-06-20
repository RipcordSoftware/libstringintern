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

#include "string_page_ptr.h"

#include "string_page.h"

rs::stringintern::StringPagePtr::StringPagePtr(StringPage* ptr) noexcept {
    if (!!ptr) {
        ptr->AddRef();
    }
    
    ptr_.store(ptr, std::memory_order_relaxed);
}

rs::stringintern::StringPagePtr::StringPagePtr(const StringPagePtr& rhs) noexcept {
    auto ptr = rhs.get();
    if (!!ptr) {
        ptr->AddRef();
    }
    
    ptr_.store(ptr, std::memory_order_relaxed);
}

rs::stringintern::StringPagePtr::StringPagePtr(StringPagePtr&& rhs) noexcept {   
    ptr_.store(rhs.get(), std::memory_order_relaxed);
    rhs.ptr_.store(nullptr, std::memory_order_relaxed);
}

rs::stringintern::StringPagePtr& rs::stringintern::StringPagePtr::operator=(const StringPagePtr& rhs) noexcept {
    auto ptr = get();
    if (!!ptr) {
        ptr->DecRef();
    }
    
    ptr = rhs.get();
    if (!!ptr) {
        ptr->AddRef();
    }
    
    ptr_.store(ptr, std::memory_order_relaxed);
    return *this;
}

rs::stringintern::StringPagePtr::~StringPagePtr() noexcept {
    auto ptr = get();
    if (!!ptr) {
        ptr->DecRef();
    }
}

bool rs::stringintern::StringPagePtr::compare_exchange_strong(StringPagePtr& expected, const StringPagePtr& desired, std::memory_order order) noexcept {
    auto oldPtr = get();
    auto expectedPtr = expected.get();
    auto desiredPtr = desired.get();
    auto status = ptr_.compare_exchange_strong(expectedPtr, desiredPtr, order);
    if (status) {
        if (!!desiredPtr) {
            desiredPtr->AddRef();
        }
        
        if (!!oldPtr) {
            oldPtr->DecRef();
        }
    } else {
        expected = *this;
    }
    
    return status;
}

std::size_t rs::stringintern::StringPagePtr::RefCount() const noexcept { 
    auto ptr = get(); return !!ptr ? ptr->RefCount() : 0; 
}

rs::stringintern::StringPagePtr& rs::stringintern::StringPagePtr::operator=(StringPagePtr&& rhs) noexcept {
    ptr_.store(rhs.get(), std::memory_order_relaxed);
    rhs.ptr_.store(nullptr, std::memory_order_relaxed);   
    return *this;    
}