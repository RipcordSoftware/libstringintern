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

#include "string_page_sizes.h"

// TODO: fill out sizes above 32k
const rs::stringintern::StringPage::entrycount_t rs::stringintern::StringPageSizes::pageSizes[] = {
    32, 48, 64, 80, 96, 112, 128, 144, 160, 192, 224, 
    256, 288, 320, 352, 384, 416, 448, 480, 
    512, 576, 640, 704, 768, 832, 896, 960, 
    1024, 1280, 1536, 1792, 2048, 2304, 2560, 2816, 3072, 3328, 3584, 3840, 
    4096, 4608, 5120, 5632, 6144, 6656, 7168, 7680, 
    8192, 9216, 10240, 11264, 12288, 13312, 14336, 15360, 
    16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 
    32768    
};

const rs::stringintern::StringPage::entrycount_t rs::stringintern::StringPageSizes::pageSizesMaxIndex = sizeof(pageSizes) / sizeof(pageSizes[0]);

rs::stringintern::StringPageSizes::Index rs::stringintern::StringPageSizes::GetPageSizeIndex(std::size_t len) {
    auto start = 0;
    auto end = pageSizesMaxIndex;    
    
    while (true) {
        auto diff = end - start;
        if (diff == 0) {
            auto inBounds = len <= pageSizes[start];            
            return inBounds ? Index(start) : Index();
        }
        
        auto mid = start + (diff / 2);
                
        if (len < pageSizes[mid]) {
            end = mid;
        } else {
            start = mid + 1;
        }
    }
}

rs::stringintern::StringPage::entrysize_t rs::stringintern::StringPageSizes::GetPageEntrySize(const Index& index) {
    return StringPageSizes::pageSizes[index];
}