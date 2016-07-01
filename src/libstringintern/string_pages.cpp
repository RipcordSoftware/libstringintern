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

#include "string_pages.h"
#include "string_page_sizes.h"
#include "string_hash.h"

#include <cstring>

#include <functional>

rs::stringintern::StringPages::StringPages() :
    archive_(StringReference::MaxNumber()),
    nursery_(nurseryCols_, StringPageSizes::GetMaxIndex(), stringPageSizeBytes_, std::bind(&StringPages::NewPage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)),
    catalog_(catalogCols_, StringPageSizes::GetMaxIndex()) {   
}

rs::stringintern::StringReference rs::stringintern::StringPages::Add(const char* str) {
    StringReference ref;
    
    if (!!str) {
        auto len = std::strlen(str);
        auto hash = StringHash::Get(str, len);
        ref = Add(str, len, hash);
    }
    
    return ref;
}

rs::stringintern::StringReference rs::stringintern::StringPages::Add(const char* str, std::size_t len, StringHash::Hash hash) {
    StringReference ref;

    if (!!str && len > 0) {
        auto row = StringPageSizes::GetIndex(len);
        if (!!row) {
            ref = catalog_.Find(row, hash);
            
            if (!ref) {
                auto iter = nursery_.Iter(row);

                // search for a suitable page
                while (!!iter && !ref) {
                    auto page = nursery_.Next(iter);
                    if (!!page) {
                        ref = page->Add(str, len, hash);
                    }
                }

                // if we didn't find a page then make a new one and try to add it there
                if (!ref) {
                    auto page = nursery_.New(row);
                    if (!!page) {
                        ref = page->Add(str, len, hash);
                    }
                }
            }
        }        
    }

    return ref;
}

const char* rs::stringintern::StringPages::GetString(const StringReference& ref) const {
    const char* str = nullptr;
    
    auto pageNumber = ref.Number();
    auto page = archive_.GetPage(pageNumber);
    if (!!page) {
        str = page->GetString(ref);
    }
    
    return str;
}

rs::stringintern::StringPagePtr rs::stringintern::StringPages::NewPage(StringPageNursery::rowcount_t row, StringPage::entrycount_t entryCount, StringPage::entrysize_t entrySize) {    
    auto page = archive_.NewPage(entryCount, entrySize);
    if (!!page) {
        catalog_.Add(row, page);
    }
    return page;
}