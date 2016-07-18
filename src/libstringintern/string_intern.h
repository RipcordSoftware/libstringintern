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

#ifndef RS_LIBSTRINGINTERN_STRING_INTERN_H
#define	RS_LIBSTRINGINTERN_STRING_INTERN_H

#include <string>

#include "string_reference.h"
#include "string_pages.h"

namespace rs {
namespace stringintern {

class StringIntern final {

public:
    StringIntern();
    StringIntern(const StringIntern&) = delete;
    StringIntern(StringIntern&&) = delete;
    void operator=(const StringIntern&) = delete;
    
    StringReference Add(const char*);
    StringReference Add(const std::string&);
    StringReference Add(const std::wstring&);
    StringReference Add(const std::u16string&);
    StringReference Add(const std::u32string&);
      
    const char* ToString(const StringReference&) const;
    bool ToString(const StringReference&, std::string&) const;
    bool ToString(const StringReference&, std::wstring&) const;
    bool ToString(const StringReference&, std::u16string&) const;
    bool ToString(const StringReference&, std::u32string&) const;
    
    StringHash::Hash GetHash(const StringReference&) const noexcept;
    
    bool Compare(const StringReference&, const StringReference&) const noexcept;
    
    std::size_t GetPageCount() const noexcept { return pages_.GetPageCount(); }
    std::size_t GetEntryCount() const noexcept { return pages_.GetEntryCount(); }
    
private:
    StringPages pages_;
};

}}

#endif	/* RS_LIBSTRINGINTERN_STRING_INTERN_H */
