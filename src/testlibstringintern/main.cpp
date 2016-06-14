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

#include <iostream>

#include <cstdlib>
#include <cstring>
#include <vector>

#include "string_intern.h"

#include "string_page.h"
#include "string_page_sizes.h"
#include "string_pages.h"

using namespace std;

int main() {
    
    /*const auto pageSize = 2 * 1024 * 1024;
    std::vector<char> pageBuffer(pageSize);
    const auto pageEntries = 256;

    rs::stringintern::StringPage page(pageBuffer.data(), pageSize / pageEntries, pageEntries);
    
    const char* str = "Hello world";
    const auto len = std::strlen(str);
    page.Add(str, len, 11234);
    page.Add(str, len, 11234);
    page.Add(str, len, 11234 + (pageSize / pageEntries));*/
    
    /*std::cout << rs::stringintern::StringPageSizes::GetPageSizeIndex(0) << std::endl;
    std::cout << rs::stringintern::StringPageSizes::GetPageSizeIndex(256) << std::endl;
    std::cout << rs::stringintern::StringPageSizes::GetPageSizeIndex(456) << std::endl;
    std::cout << rs::stringintern::StringPageSizes::GetPageSizeIndex(16365) << std::endl;
    std::cout << rs::stringintern::StringPageSizes::GetPageSizeIndex(256 * 1024) << std::endl;
    
    std::cout << rs::stringintern::StringPageSizes::pageSizesMaxIndex << std::endl;*/
    
    rs::stringintern::StringPages pages;
    auto ref1 = pages.Add("hello world");
    auto ref2 = pages.Add("hello world");
    auto ref3 = pages.Add("hello world!!");
    
    std::cout << ref1.Number() << ", " << ref1.Index() << std::endl;
    std::cout << ref2.Number() << ", " << ref2.Index() << std::endl;
    std::cout << ref3.Number() << ", " << ref3.Index() << std::endl;
}
