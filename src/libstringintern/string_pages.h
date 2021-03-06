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

#include <atomic>
#include <cstddef>

#include "string_reference.h"
#include "string_page_nursery.h"
#include "string_page_catalog.h"
#include "string_page_archive.h"

namespace rs {
namespace stringintern {

class StringPages final {
    
public:
    StringPages();
    
    StringReference Add(const char*);
    StringReference Add(const char*, std::size_t, StringHash::Hash);
    
    const char* GetString(const StringReference&) const;
    const char* GetString(const StringReference&, StringPage::entrysize_t&) const;

    StringHash::Hash GetHash(const StringReference&) const;
    
    bool Compare(const StringReference&, const StringReference&) const noexcept;
    
    std::size_t GetPageCount() const noexcept { return archive_.GetPageCount(); }
    std::size_t GetEntryCount() const noexcept { return archive_.GetEntryCount(); }
    
#ifdef RS_LIBSTRINGINTERN_STRINGPAGES_INTERNALSTATE
    const StringPageArchive& GetArchive() const noexcept { return archive_; }
    const StringPageNursery& GetNursery() const noexcept { return nursery_; }
    const StringPageCatalog& GetCatalog() const noexcept { return catalog_; }
    StringPageNursery::colcount_t GetNurseryCols() const noexcept { return nurseryCols_; }
#endif
    
private:
    
    StringPagePtr NewPage(StringPageNursery::rowcount_t, StringPage::entrycount_t, StringPage::entrysize_t);
       
    constexpr static StringPageNursery::colcount_t nurseryCols_ = 8;
    constexpr static StringPageNursery::pagesize_t stringPageSizeBytes_ = 2 * 1024 * 1024;
    constexpr static StringPageNursery::colcount_t catalogCols_ = 4096;

    StringPageArchive archive_;
    StringPageNursery nursery_;
    StringPageCatalog catalog_;
};

}}

#endif	/* RS_LIBSTRINGINTERN_STRING_PAGES_H */

