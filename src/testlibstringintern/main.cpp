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
#include <thread>
#include <sstream>

#include <string.h>

#include "string_intern.h"

std::vector<std::string> GetFileWords(const char* filename) {
    std::vector<std::string> words;
    const auto delims = " \t\r\n\f,.\"\'()[]{}!:;&";
    
    std::fstream fs;
    fs.open(filename, std::fstream::in);
    
    char buffer[4096];
    char* saveptr = nullptr;
    while (fs.getline(buffer, sizeof(buffer) - 1).good()) {
        auto token = strtok_r(buffer, delims, &saveptr);
        while (token != nullptr) {
            words.emplace_back(token);
            token = strtok_r(nullptr, delims, &saveptr);
        }
    }
    
    fs.close();
    
    return words;
}

std::vector<rs::stringintern::StringReference> InternWords(const std::vector<std::string>& words, rs::stringintern::StringIntern& intern) {
    std::vector<rs::stringintern::StringReference> refs;
    
    for (auto word : words) {
        auto ref = intern.Add(word);
        refs.emplace_back(ref);
    }
    
    return refs;
}

void InternFile(const char* filename, rs::stringintern::StringIntern& intern) {   
    auto words = GetFileWords(filename);
    auto refs = InternWords(words, intern);
    
    if (words.size() != refs.size()) {
        std::stringstream error;
        error << "Count mismatch on '" << filename << "'";
        throw error.str();
    }
    
    for (auto i = 0; i < refs.size(); ++i) {
        auto internedWord = intern.ToString(refs[i]);
        if (words[i] != internedWord) {
            std::stringstream error;
            error << "String mismatch on '" << filename << "' at index " << i << ", expected '" << words[i] << "', got '" << internedWord << "'";
            throw error.str();
        }
    }
}

int main() {
    
    std::vector<std::string> files{
        R"(TestFiles/rfc/rfc2616.txt)", 
        R"(TestFiles/gutenberg/11.txt)",
        R"(TestFiles/gutenberg/74.txt)",
        R"(TestFiles/gutenberg/76.txt)",
        R"(TestFiles/gutenberg/98.txt)",
        R"(TestFiles/gutenberg/158.txt)",
        R"(TestFiles/gutenberg/308.txt)",
        R"(TestFiles/gutenberg/345.txt)",
        R"(TestFiles/gutenberg/1184-0.txt)",
        R"(TestFiles/gutenberg/1342.txt)",
        R"(TestFiles/gutenberg/1661.txt)",
        R"(TestFiles/gutenberg/1952.txt)",
        R"(TestFiles/gutenberg/2701.txt)",
        R"(TestFiles/gutenberg/4300.txt)",
        R"(TestFiles/gutenberg/5200.txt)",
        R"(TestFiles/gutenberg/27827.txt)",
        R"(TestFiles/gutenberg/30254.txt)",
    };
    
    std::vector<std::thread> threads;
    
    rs::stringintern::StringIntern intern;

    for (auto i = 0; i < files.size(); ++i) {
        threads.emplace_back([&, i]() {
            try {
                InternFile(files[i].c_str(), intern);
                std::cout << files[i] << ", pages = " << intern.GetPageCount() << ", entries = " << intern.GetEntryCount() << std::endl;
            } catch (const std::string& error) {
                std::cerr << "Error: " << error << std::endl;
            }
        });
    }

    for (auto i = 0; i < threads.size(); ++i) {
        threads[i].join();
    }
}
