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

#include "string_reference.h"

rs::stringintern::StringReference::StringReference() noexcept : reference_(invalid_) {
    
}

rs::stringintern::StringReference::StringReference(reference_t number, reference_t index) noexcept {
    reference_ = number;
    reference_ <<= indexBits_;
    reference_ |= index;
}

rs::stringintern::StringReference::StringReference(const StringReference& rhs) noexcept : reference_(rhs.reference_) { 

}

rs::stringintern::StringReference rs::stringintern::StringReference::New(reference_t number, reference_t index) noexcept {
    return index < indexMask_ ? StringReference(number, index) : StringReference();
}

rs::stringintern::StringReference::reference_t rs::stringintern::StringReference::Number() const noexcept {
    return reference_ >> indexBits_;
}

rs::stringintern::StringReference::reference_t rs::stringintern::StringReference::Index() const noexcept {
    return reference_ & indexMask_;
}