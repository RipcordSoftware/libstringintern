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

#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define RS_LIBSTRINGINTERN_STRINGPAGES_INTERNALSTATE 1
#include "../string_pages.h"

class StringPagesTests : public ::testing::Test {
protected:
    virtual void SetUp() {
        
    }
    
    virtual void TearDown() {
        
    }
    
public:

};

TEST_F(StringPagesTests, test0) {
    rs::stringintern::StringPages pages;
    ASSERT_EQ(0, pages.GetPageCount());
    
    auto str = "hello world";
    auto ref1 = pages.Add(str);
    ASSERT_EQ(1, pages.GetPageCount());
    ASSERT_EQ(0, ref1.Number());
    ASSERT_EQ(1, pages.GetEntryCount());
    
    ASSERT_STREQ(str, pages.GetString(ref1));
    
    auto ref2 = pages.Add(str);
    ASSERT_EQ(1, pages.GetPageCount());
    ASSERT_EQ(0, ref2.Number());
    ASSERT_EQ(1, pages.GetEntryCount());
    
    ASSERT_STREQ(str, pages.GetString(ref2));
    
    ASSERT_TRUE(ref1 == ref2);
}

TEST_F(StringPagesTests, test1) {
    rs::stringintern::StringPages pages;
    ASSERT_EQ(0, pages.GetPageCount());
    
    auto str1 = "hello world";
    auto ref1 = pages.Add(str1);
    ASSERT_EQ(1, pages.GetPageCount());
    ASSERT_EQ(0, ref1.Number());
    ASSERT_EQ(1, pages.GetEntryCount());
    
    ASSERT_STREQ(str1, pages.GetString(ref1));
    
    auto str2 = "HELLO WORLD";
    auto ref2 = pages.Add(str2);
    ASSERT_EQ(1, pages.GetPageCount());
    ASSERT_EQ(0, ref2.Number());
    ASSERT_EQ(2, pages.GetEntryCount());
    
    ASSERT_STREQ(str2, pages.GetString(ref2));
    
    ASSERT_TRUE(ref1 != ref2);
}

TEST_F(StringPagesTests, test2) {
    rs::stringintern::StringPages pages;
    ASSERT_EQ(0, pages.GetPageCount());
 
    const auto count = 1000;
    std::vector<std::string> strings;
    std::vector<rs::stringintern::StringReference> refs1;
    for (auto i = 0; i < count; ++i) {
        auto val = std::to_string(i);
        refs1.push_back(pages.Add(val.c_str()));
        strings.emplace_back(std::move(val));
    }
    
    ASSERT_EQ(2, pages.GetPageCount());
    ASSERT_EQ(count, pages.GetEntryCount());

    std::vector<rs::stringintern::StringReference> refs2;
    for (auto i = 0; i < count; ++i) {
        refs2.push_back(pages.Add(strings[i].c_str()));
    }
    
    ASSERT_EQ(2, pages.GetPageCount());
    ASSERT_EQ(count, pages.GetEntryCount());
    
    ASSERT_EQ(refs1.size(), refs2.size());
    
    for (auto i = 0; i < count; ++i) {
        ASSERT_EQ(refs1[i].Number(), refs2[i].Number());
        ASSERT_EQ(refs1[i].Index(), refs2[i].Index());
    }
}

TEST_F(StringPagesTests, test3) {
    rs::stringintern::StringPages pages;
    ASSERT_EQ(0, pages.GetPageCount());
    
    rs::stringintern::StringReference ref1;
    ASSERT_EQ(nullptr, pages.GetString(ref1));
    
    rs::stringintern::StringPage::entrysize_t size = -1;
    ASSERT_EQ(nullptr, pages.GetString(ref1, size));
    ASSERT_EQ(-1, size);
    
    auto ref2 = rs::stringintern::StringReference::New(-1u, 0);
    ASSERT_EQ(nullptr, pages.GetString(ref2));
    ASSERT_EQ(nullptr, pages.GetString(ref2, size));
    ASSERT_EQ(-1, size);
}

TEST_F(StringPagesTests, test4) {
    rs::stringintern::StringPages pages;
    ASSERT_EQ(0, pages.GetPageCount());
    
    ASSERT_TRUE(!pages.Add(nullptr));        
    ASSERT_TRUE(!pages.Add(nullptr, 8, 0));
    ASSERT_TRUE(!pages.Add("testtest", 32 * 1024 * 1024, 0));
}

TEST_F(StringPagesTests, test5) {
    auto str = "hello world";
    const auto len = std::strlen(str);
    rs::stringintern::StringPages pages;
    
    auto cols = pages.GetNurseryCols();
    for (decltype(cols) i = 0; i < cols; ++i) {
        ASSERT_TRUE(!!pages.Add(str, len, (1ul << 28) * i));
        ASSERT_EQ(i + 1, pages.GetPageCount());
        
        auto nurseryPages = pages.GetNursery().GetPages(0);
        ASSERT_EQ(i + 1, nurseryPages.size());
        ASSERT_EQ(i, nurseryPages[i]->GetPageNumber());
    }
    
    ASSERT_EQ(cols, pages.GetCatalog().GetPageCount());
    ASSERT_EQ(cols, pages.GetArchive().GetPageCount());
    
    if (true) {
        auto nurseryPages = pages.GetNursery().GetPages(0);
        for (decltype(cols) i = 0; i < cols; ++i) {
            ASSERT_EQ(i, nurseryPages[i]->GetPageNumber());
        }
    }
    
    for (decltype(cols) i = 0; i < cols; ++i) {
        ASSERT_TRUE(!!pages.Add(str, len, (1ul << 28) * (cols + i)));
        ASSERT_EQ(cols + i + 1, pages.GetPageCount());
        
        auto nurseryPages = pages.GetNursery().GetPages(0);
        ASSERT_EQ(cols, nurseryPages.size());
        ASSERT_EQ(cols + i, nurseryPages[i]->GetPageNumber());
    }
    
    ASSERT_EQ(cols * 2, pages.GetCatalog().GetPageCount());
    ASSERT_EQ(cols * 2, pages.GetArchive().GetPageCount());
    
    if (true) {
        auto nurseryPages = pages.GetNursery().GetPages(0);
        for (decltype(cols) i = 0; i < cols; ++i) {
            ASSERT_EQ(cols + i, nurseryPages[i]->GetPageNumber());
        }
    }
    
    for (decltype(cols) i = 0; i < cols * 2; ++i) {
        auto ref = pages.Add(str, len, (1ul << 28) * i);        
        ASSERT_TRUE(!!ref);
        ASSERT_EQ(i, ref.Number());       
    }   
    
    ASSERT_EQ(cols * 2, pages.GetCatalog().GetPageCount());
    ASSERT_EQ(cols * 2, pages.GetArchive().GetPageCount());
}

TEST_F(StringPagesTests, test6) {
    auto str = "hello world";
    const auto len = std::strlen(str);
    rs::stringintern::StringPages pages;
    
    auto cols = pages.GetNurseryCols();
    for (decltype(cols) i = 0; i < cols; ++i) {
        ASSERT_TRUE(!!pages.Add(str, len, (1ul << 28) * i));
    }
    
    ASSERT_EQ(cols, pages.GetPageCount());
    ASSERT_EQ(cols, pages.GetCatalog().GetPageCount());
    ASSERT_EQ(cols, pages.GetArchive().GetPageCount());
    ASSERT_EQ(cols, pages.GetNursery().GetPages(0).size());
    
    for (decltype(cols) i = 0; i < cols; ++i) {
        ASSERT_TRUE(!!pages.Add(str, len, (1ul << 28) + i + 1));
    }
    
    ASSERT_EQ(cols, pages.GetPageCount());
    ASSERT_EQ(cols, pages.GetCatalog().GetPageCount());
    ASSERT_EQ(cols, pages.GetArchive().GetPageCount());        
    ASSERT_EQ(cols, pages.GetNursery().GetPages(0).size());
}

TEST_F(StringPagesTests, test7) {
    auto str = "hello world";
    const auto len = std::strlen(str);
    rs::stringintern::StringPages pages;
    
    auto cols = pages.GetNurseryCols();
    for (decltype(cols) i = 0; i < cols; ++i) {
        ASSERT_TRUE(!!pages.Add(str, len, i));               
    }
    
    ASSERT_EQ(1, pages.GetPageCount());
}
