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
#include <vector>
#include <algorithm>

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
