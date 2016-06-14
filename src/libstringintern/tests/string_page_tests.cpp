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

#include <gtest/gtest.h>

#include <cstring>
#include <string>
#include <memory>
#include <limits>

#include "../string_page.h"
#include "../string_intern_exception.h"

class StringPageTests : public ::testing::Test {
protected:
    virtual void SetUp() {
        
    }
    
    virtual void TearDown() {
        
    }
    
public:
    std::shared_ptr<rs::stringintern::StringPage> NewPagePtr(
        std::size_t number,
        char* ptr, 
        rs::stringintern::StringPage::entrycount_t entryCount,
        rs::stringintern::StringPage::entrysize_t entrySize) {
        return std::shared_ptr<rs::stringintern::StringPage>(rs::stringintern::StringPage::New(number, ptr, entryCount, entrySize));
    }
};

TEST_F(StringPageTests, test0) {
    const auto pageSize = 2 * 1024 * 1024;
    std::vector<char> pageBuffer(pageSize);
    const auto pageEntrySize = 256;
    const auto pageEntries = pageSize / pageEntrySize;

    auto page = NewPagePtr(42, pageBuffer.data(), pageEntries, pageEntrySize);
    
    ASSERT_EQ(42, page->Number());
    ASSERT_EQ(pageEntries, page->EntryCount());
    ASSERT_EQ(pageEntrySize, page->EntrySize());
    
    const char* str = "Hello world";
    const auto len = std::strlen(str);
    ASSERT_EQ(1, page->Add(str, len, 1));
    ASSERT_EQ(1, page->Add(str, len, 1));
    ASSERT_EQ(rs::stringintern::StringPage::InvalidIndex, page->Add(str, len, 1 + pageEntries));
}

TEST_F(StringPageTests, test1) {    
    ASSERT_THROW({
        const auto pageSize = 2 * 1024 * 1024;
        const auto pageEntrySize = 256;
        const auto pageEntries = pageSize / pageEntrySize;
        std::vector<char> pageBuffer(pageSize);    

        auto page = NewPagePtr(42, pageBuffer.data(), pageEntries, pageEntrySize);

        const char* str = "I am a placebo";
        const auto len = 1024;
        
        page->Add(str, len, 1);
    }, rs::stringintern::StringInternException);
}

TEST_F(StringPageTests, test2) {
    const auto pageSize = 2 * 1024 * 1024;
    std::vector<char> pageBuffer(pageSize);
    const auto pageEntrySize = 256;
    const auto pageEntries = pageSize / pageEntrySize;
    
    auto page = NewPagePtr(42, pageBuffer.data(), pageEntries, pageEntrySize);

    ASSERT_EQ(42, page->Number());
    ASSERT_EQ(pageEntries, page->EntryCount());
    ASSERT_EQ(pageEntrySize, page->EntrySize());
    
    for (auto i = 0; i < pageEntries; ++i) {
        auto val = std::to_string(i);
        ASSERT_EQ(i, page->Add(val.c_str(), val.length(), i));
        ASSERT_EQ(val, page->GetString(i));
    }
    
    for (auto i = 0; i < pageEntries; ++i) {
        auto val = std::to_string(i);
        ASSERT_EQ(i, page->Add(val.c_str(), val.length(), i));
        ASSERT_EQ(val, page->GetString(i));
    }
    
    for (auto i = 0; i < pageEntries; ++i) {
        auto index = pageEntries - i - 1;
        auto val = std::to_string(index);
        ASSERT_EQ(val, page->GetString(index));
    }    
}

TEST_F(StringPageTests, test3) {
    const auto pageSize = 2 * 1024 * 1024;
    std::vector<char> pageBuffer(pageSize);
    const auto pageEntrySize = 256;
    const auto pageEntries = pageSize / pageEntrySize;
    
    auto page1 = NewPagePtr(std::numeric_limits<std::uint16_t>::max(), pageBuffer.data(), pageEntries, pageEntrySize);
    ASSERT_EQ(nullptr, page1.get());
    
    auto page2 = NewPagePtr(std::numeric_limits<std::uint32_t>::max(), pageBuffer.data(), pageEntries, pageEntrySize);
    ASSERT_EQ(nullptr, page2.get());
}