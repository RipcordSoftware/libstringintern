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

#include <algorithm>

rs::stringintern::StringPages::StringPages() :
    nursery_(nurseryCols_, StringPageSizes::pageSizesMaxIndex, stringPageSizeBytes_),
    catalog_(catalogCols_, StringPageSizes::pageSizesMaxIndex) {   
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
        auto row = StringPageSizes::GetPageSizeIndex(len);
        if (!!row) {
            ref = catalog_.Find(row, hash);
            
            if (!ref) {
                auto firstPage = nursery_.Current(row);

                auto index = StringPage::InvalidIndex;
                auto page = firstPage;
                auto cols = nursery_.Cols();

                // search for a suitable page
                while (cols > 0 && index == StringPage::InvalidIndex) {
                    index = page->Add(str, len, hash);
                    if (index == StringPage::InvalidIndex) {
                        page = nursery_.Next(row);
                        --cols;
                    }
                }

                // if we didn't find a page then replace the first page and search again
                if (index == StringPage::InvalidIndex) {
                    page = nursery_.New(row, firstPage, true);

                    if (page == nullptr) {
                        page = nursery_.Current(row);
                    } else {
                        catalog_.Add(row, firstPage);
                    }

                    index = page->Add(str, len, hash);
                }

                // did we find anything?
                if (index != StringPage::InvalidIndex) {
                    ref = StringReference(page->Number(), index);
                }
            }
        }        
    }
    
    return ref;
}
