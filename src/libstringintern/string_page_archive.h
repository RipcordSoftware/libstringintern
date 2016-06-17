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

#ifndef RS_LIBSTRINGINTERN_STRING_PAGE_ARCHIVE_H
#define	RS_LIBSTRINGINTERN_STRING_PAGE_ARCHIVE_H

#include <atomic>
#include <vector>
#include <cstdint>

#include "string_page.h"

namespace rs {
namespace stringintern {
    
class StringPageArchive {
public:
    StringPageArchive(std::size_t entries);
    StringPageArchive(const StringPageArchive& orig) = delete;
    StringPageArchive(StringPageArchive&&) = delete;
    void operator=(const StringPageArchive&) = delete;
    ~StringPageArchive();
    
    StringPage* NewPage(StringPage::entrycount_t entryCount, StringPage::entrysize_t entrySize);
    
    StringPage* GetPage(std::size_t number) const noexcept;
    
    std::size_t Count() const noexcept;
    
    std::size_t MaxEntries() const noexcept { return pages_.size(); }
    
private:    
    
    std::atomic<std::size_t> index_;
    
    std::vector<std::atomic<StringPage*>> pages_;        

};

}}

#endif	/* RS_LIBSTRINGINTERN_STRING_PAGE_ARCHIVE_H */
