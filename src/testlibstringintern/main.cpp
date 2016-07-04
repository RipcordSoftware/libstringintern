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
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

#include "string_intern.h"

int main() {
    const auto delims = " \t\r\n\f,.\"\'()[]{}!:;&";
    std::vector<rs::stringintern::StringReference> refs;
    
    rs::stringintern::StringIntern intern;    

    std::fstream fs;
    fs.open("rfc2616.txt", std::fstream::in);
    
    char buffer[4096];
    while (fs.getline(buffer, sizeof(buffer) - 1).good()) {
        auto pStr = std::strtok(buffer, delims);
        while (pStr != nullptr) {
            refs.push_back(intern.Add(pStr));
            pStr = std::strtok(nullptr, delims);
        }
    }
    
    fs.close();
    
    for (auto i = 0; i < refs.size(); ++i) {
        const auto& ref = refs[i];
        if (i > 0 && (i % 16) == 0) {
            std::cout << intern.ToString(ref) << std::endl;
        } else {
            std::cout << intern.ToString(ref) << ' ';
        }
    }
    
    std::cout << std::endl << "* pages = " << intern.GetPageCount() << ", entries = " << intern.GetTotalEntries() << std::endl;
}
