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
#include <thread>

#include "../string_page.h"
#include "../string_intern_exception.h"

class StringPageTests : public ::testing::Test {
protected:
    virtual void SetUp() {
        
    }
    
    virtual void TearDown() {
        
    }
    
public:
    rs::stringintern::StringPagePtr NewPagePtr(
        std::size_t number,
        rs::stringintern::StringPage::entrycount_t entryCount,
        rs::stringintern::StringPage::entrysize_t entrySize) {
        return rs::stringintern::StringPage::New(number, entryCount, entrySize);
    }
};

TEST_F(StringPageTests, test0) {
    const auto pageSize = 2 * 1024 * 1024;
    const auto pageEntrySize = 256;
    const auto pageEntries = pageSize / pageEntrySize;

    auto page = NewPagePtr(42, pageEntries, pageEntrySize);
    
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

        auto page = NewPagePtr(42, pageEntries, pageEntrySize);

        const char* str = "I am a placebo";
        const auto len = 0;
        
        page->Add(str, len, 1);
    }, rs::stringintern::StringInternException);
}

TEST_F(StringPageTests, test2) {    
    ASSERT_THROW({
        const auto pageSize = 2 * 1024 * 1024;
        const auto pageEntrySize = 256;
        const auto pageEntries = pageSize / pageEntrySize;        

        auto page = NewPagePtr(42, pageEntries, pageEntrySize);

        const char* str = "I am a placebo";
        const auto len = 1024;
        
        page->Add(str, len, 1);
    }, rs::stringintern::StringInternException);
}

TEST_F(StringPageTests, test3) {
    const auto pageSize = 2 * 1024 * 1024;
    const auto pageEntrySize = 256;
    const auto pageEntries = pageSize / pageEntrySize;
    
    auto page = NewPagePtr(42, pageEntries, pageEntrySize);

    ASSERT_EQ(42, page->Number());
    ASSERT_EQ(pageEntries, page->EntryCount());
    ASSERT_EQ(pageEntrySize, page->EntrySize());
    
    for (auto i = 0; i < pageEntries; ++i) {
        auto val = std::to_string(i);
        ASSERT_EQ(i, page->Add(val.c_str(), val.length(), i));
        ASSERT_EQ(val, page->GetString(i));
    }
    
    ASSERT_EQ(pageEntries, page->Count());
    
    for (auto i = pageEntries; i < pageEntries * 2; ++i) {
        auto val = std::to_string(i);
        ASSERT_EQ(rs::stringintern::StringPage::InvalidIndex, page->Add(val.c_str(), val.length(), i));
    }
    
    ASSERT_EQ(pageEntries, page->Count());
    
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

TEST_F(StringPageTests, test4) {
    const auto pageSize = 2 * 1024 * 1024;
    const auto pageEntrySize = 256;
    const auto pageEntries = pageSize / pageEntrySize;
    
    auto page1 = NewPagePtr(std::numeric_limits<std::uint16_t>::max(), pageEntries, pageEntrySize);
    ASSERT_EQ(nullptr, page1.get());
    
    auto page2 = NewPagePtr(std::numeric_limits<std::uint32_t>::max(), pageEntries, pageEntrySize);
    ASSERT_EQ(nullptr, page2.get());
}

TEST_F(StringPageTests, test5a) {
    const auto pageSize = 2 * 1024 * 1024;
    const auto pageEntrySize = 256;
    const auto pageEntries = pageSize / pageEntrySize;

    auto page = NewPagePtr(0, pageEntries, pageEntrySize);
    
    const char* str = "I am a placebo";
    auto len = std::strlen(str);

    ASSERT_EQ(0, page->Add(str, len, pageEntries));
    ASSERT_NE(nullptr, page->GetString(pageEntries));
    ASSERT_EQ(nullptr, page->GetString(0));
}

TEST_F(StringPageTests, test5b) {
    const auto pageSize = 2 * 1024 * 1024;
    const auto pageEntrySize = 256;
    const auto pageEntries = pageSize / pageEntrySize;

    auto page = NewPagePtr(0, pageEntries, pageEntrySize);
    
    const char* str = "I am a placebo";
    const auto len = std::strlen(str);

    ASSERT_EQ(0, page->Add(str, len, 0));
    ASSERT_EQ(1, page->Count());
    ASSERT_NE(nullptr, page->GetString(0));
    ASSERT_EQ(nullptr, page->GetString(pageEntries));
    
    ASSERT_EQ(rs::stringintern::StringPage::InvalidIndex, page->Add(str, len, pageEntries));
    ASSERT_EQ(1, page->Count());
    
    ASSERT_EQ(0, page->Add(str, len, 0));
    ASSERT_EQ(1, page->Count());
}

TEST_F(StringPageTests, test6a) {    
    const auto pageSize = 2 * 1024 * 1024;
    const auto pageEntrySize = 32;
    const auto pageEntries = pageSize / pageEntrySize;
    
    std::vector<std::string> strings;
    strings.reserve(pageEntries);
    for (auto i = 0; i < pageEntries; ++i) {
        strings.emplace_back(std::move(std::to_string(i)));
    }

    auto page = NewPagePtr(0, pageEntries, pageEntrySize);
    ASSERT_EQ(pageEntries, page->EntryCount());
    ASSERT_EQ(pageEntrySize, page->EntrySize());

    std::atomic<rs::stringintern::StringPage::entrycount_t> pageIndex{0};
    
    auto func = [&]() {
        for (auto i = 0; i < pageEntries; i = pageIndex.fetch_add(1, std::memory_order_relaxed) + 1) {
            page->Add(strings[i].c_str(), strings[i].size(), i);
        }
    };
    
    std::thread t1{func};
    std::thread t2{func};
    
    t1.join();
    t2.join();
    
    ASSERT_EQ(pageEntries, page->Count());
    
    for (auto i = 0; i < pageEntries; ++i) {
        ASSERT_EQ(strings[i], page->GetString(i));
    }
}

TEST_F(StringPageTests, test6b) {    
    const auto pageSize = 4 * 1024 * 1024;
    const auto pageEntrySize = 8;
    const auto pageEntries = pageSize / pageEntrySize;
    
    std::vector<std::string> strings;
    strings.reserve(pageEntries);
    for (auto i = 0; i < pageEntries; ++i) {
        strings.emplace_back(std::move(std::to_string(i)));
    }

    auto page = NewPagePtr(0, pageEntries, pageEntrySize);
    ASSERT_EQ(pageEntries, page->EntryCount());
    ASSERT_EQ(pageEntrySize, page->EntrySize());

    std::atomic<rs::stringintern::StringPage::entrycount_t> pageIndex{0};
    
    auto func = [&]() {
        for (auto i = 0; i < pageEntries; i = pageIndex.fetch_add(1, std::memory_order_relaxed) + 1) {
            page->Add(strings[i].c_str(), strings[i].size(), i);
        }
    };
    
    std::thread t1{func};
    std::thread t2{func};
    std::thread t3{func};
    std::thread t4{func};
    
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    
    ASSERT_EQ(pageEntries, page->Count());
    
    for (auto i = 0; i < pageEntries; ++i) {
        ASSERT_EQ(strings[i], page->GetString(i));
    }
}

TEST_F(StringPageTests, test6c) {    
    const auto pageSize = 2 * 1024 * 1024;
    const auto pageEntrySize = 32;
    const auto pageEntries = pageSize / pageEntrySize;
    
    std::vector<std::string> strings;
    strings.reserve(pageEntries);
    for (auto i = 0; i < pageEntries; ++i) {
        strings.emplace_back(std::move(std::to_string(i)));
    }

    auto page = NewPagePtr(0, pageEntries, pageEntrySize);
    ASSERT_EQ(pageEntries, page->EntryCount());
    ASSERT_EQ(pageEntrySize, page->EntrySize());
    
    auto func = [&]() {
        for (auto i = 0; i < pageEntries; ++i) {
            page->Add(strings[i].c_str(), strings[i].size(), i);
        }
    };
    
    std::thread t1{func};
    std::thread t2{func};
    
    t1.join();
    t2.join();
    
    ASSERT_EQ(pageEntries, page->Count());
    
    for (auto i = 0; i < pageEntries; ++i) {
        ASSERT_EQ(strings[i], page->GetString(i));
    }
}

TEST_F(StringPageTests, test6d) {    
    const auto pageSize = 4 * 1024 * 1024;
    const auto pageEntrySize = 8;
    const auto pageEntries = pageSize / pageEntrySize;
    
    std::vector<std::string> strings;
    strings.reserve(pageEntries);
    for (auto i = 0; i < pageEntries; ++i) {
        strings.emplace_back(std::move(std::to_string(i)));
    }

    auto page = NewPagePtr(0, pageEntries, pageEntrySize);
    ASSERT_EQ(pageEntries, page->EntryCount());
    ASSERT_EQ(pageEntrySize, page->EntrySize());
    
    auto func = [&]() {
        for (auto i = 0; i < pageEntries; ++i) {
            page->Add(strings[i].c_str(), strings[i].size(), i);
        }
    };
    
    std::thread t1{func};
    std::thread t2{func};
    std::thread t3{func};
    std::thread t4{func};
    
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    
    ASSERT_EQ(pageEntries, page->Count());
    
    for (auto i = 0; i < pageEntries; ++i) {
        ASSERT_EQ(strings[i], page->GetString(i));
    }
}

TEST_F(StringPageTests, test7) {
    const auto pageSize = 2 * 1024 * 1024;
    const auto pageEntrySize = 256;
    const auto pageEntries = pageSize / pageEntrySize;

    ASSERT_EQ(nullptr, rs::stringintern::StringPage::New(0, nullptr, pageEntries, pageEntrySize));
}