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

#ifndef RS_LIBSTRINGINTERN_STRING_REFERENCE_H
#define	RS_LIBSTRINGINTERN_STRING_REFERENCE_H

#include <cstdint>

namespace rs {
namespace stringintern {

class StringReference final {
public:            
    using reference_t = std::uint32_t;
    
    StringReference() noexcept;    
    StringReference(const StringReference&) noexcept;
    
    static StringReference New(reference_t, reference_t) noexcept;
    
    bool operator!() const noexcept { return reference_ == invalid_; }
    
    StringReference& operator=(const StringReference& other) noexcept { reference_ = other.reference_; return *this; }
    bool operator==(const StringReference& other) const noexcept { return reference_ == other.reference_; }
    bool operator!=(const StringReference& other) const noexcept { return reference_ != other.reference_; }
    bool operator<(const StringReference& other) const noexcept { return reference_ < other.reference_; }

    reference_t Number() const noexcept;
    reference_t Index() const noexcept;

    constexpr static reference_t MaxNumber() { return maxNumber_; }
    constexpr static reference_t MaxIndex() { return maxIndex_; }

private:
    
    StringReference(reference_t, reference_t) noexcept;
    
    using pagenumber_t = std::uint16_t;
    using pageindex_t = std::uint32_t;

    constexpr static reference_t referenceBits_ = sizeof(reference_t) * 8;
    constexpr static reference_t indexBits_ = 18;
    constexpr static reference_t numberBits_ = referenceBits_ - indexBits_;
    
    constexpr static reference_t maxNumber_ = 1 << numberBits_;
    constexpr static reference_t maxIndex_ = 1 << indexBits_;

    constexpr static reference_t indexMask_ = ((1 << indexBits_) - 1);

    constexpr static reference_t invalid_ = -1;
    
    reference_t reference_;

};

}}

#endif	/* RS_LIBSTRINGINTERN_STRING_REFERENCE_H */
