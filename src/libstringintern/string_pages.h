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

#ifndef RS_LIBSTRINGINTERN_STRING_PAGES_H
#define	RS_LIBSTRINGINTERN_STRING_PAGES_H

#include "string_page.h"
#include "string_reference.h"

#include <array>
#include <atomic>
#include <memory>
#include <cstddef>

namespace rs {
namespace stringintern {

class StringPages {
    
public:
    StringPages();
    
    StringReference Add(const char*);
    StringReference Add(const char*, std::size_t, StringHash::Hash);
    
private:
    
    StringPage* AllocatePage(std::uint32_t nurseryIndex, StringPage::entrysize_t);
    
    static const std::uint32_t nurseryRowSize_ = 8;
    static const std::uint32_t stringPageSizeBytes_ = 4 * 1024 * 1024;
    
    std::atomic<StringPage::pagenumber_t> pageCount_ = ATOMIC_VAR_INIT(0);

    std::array<std::atomic<std::uint32_t>, nurseryRowSize_> nurseryCounters_;
    std::unique_ptr<std::atomic<StringPage*>[]> nursery_;

};

}}

#endif	/* RS_LIBSTRINGINTERN_STRING_PAGES_H */

