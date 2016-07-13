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
#include "../string_intern.h"

class StringInternTests : public ::testing::Test {
protected:
    virtual void SetUp() {
        
    }
    
    virtual void TearDown() {
        
    }
    
public:

};

TEST_F(StringInternTests, test0) {
    rs::stringintern::StringIntern intern;
    
    ASSERT_EQ(0, intern.GetPageCount());
    ASSERT_EQ(0, intern.GetEntryCount());
    
    auto str1 = "hello world";
    auto ref1 = intern.Add(str1);
    ASSERT_TRUE(!!ref1);
    ASSERT_STREQ(str1, intern.ToString(ref1));
    
    ASSERT_EQ(1, intern.GetPageCount());
    ASSERT_EQ(1, intern.GetEntryCount());
    
    auto str2 = "HELLO WORLD";
    auto ref2 = intern.Add(str2);
    ASSERT_TRUE(!!ref2);
    ASSERT_STREQ(str2, intern.ToString(ref2));
    
    ASSERT_EQ(1, intern.GetPageCount());
    ASSERT_EQ(2, intern.GetEntryCount());
}

TEST_F(StringInternTests, test1) {
    rs::stringintern::StringIntern intern;
    
    std::string str1 = "hello world";
    auto ref1 = intern.Add(str1);
    ASSERT_TRUE(!!ref1);
    ASSERT_TRUE(str1 == intern.ToString(ref1));
    
    ASSERT_EQ(1, intern.GetPageCount());
    ASSERT_EQ(1, intern.GetEntryCount());
    
    std::string str2 = "HELLO WORLD";
    auto ref2 = intern.Add(str2);
    ASSERT_TRUE(!!ref2);
    ASSERT_TRUE(str2 == intern.ToString(ref2));
    
    ASSERT_EQ(1, intern.GetPageCount());
    ASSERT_EQ(2, intern.GetEntryCount());
}

TEST_F(StringInternTests, test2) {
    rs::stringintern::StringIntern intern;
    
    std::string str1 = "hello world";
    auto ref1 = intern.Add(str1);
    ASSERT_TRUE(!!ref1);
    std::string temp;
    ASSERT_TRUE(intern.ToString(ref1, temp));
    ASSERT_TRUE(str1 == temp);
    
    ASSERT_EQ(1, intern.GetPageCount());
    ASSERT_EQ(1, intern.GetEntryCount());
    
    std::string str2 = "HELLO WORLD";
    auto ref2 = intern.Add(str2);
    ASSERT_TRUE(!!ref2);
    ASSERT_TRUE(intern.ToString(ref2, temp));
    ASSERT_TRUE(str2 == temp);
    
    ASSERT_EQ(1, intern.GetPageCount());
    ASSERT_EQ(2, intern.GetEntryCount());
}


TEST_F(StringInternTests, test3) {
    rs::stringintern::StringIntern intern;
    
    std::wstring str1 = L"hello world";
    auto ref1 = intern.Add(str1);
    ASSERT_TRUE(!!ref1);
    std::wstring temp;
    ASSERT_TRUE(intern.ToString(ref1, temp));
    ASSERT_TRUE(str1 == temp);
    
    ASSERT_EQ(1, intern.GetPageCount());
    ASSERT_EQ(1, intern.GetEntryCount());
    
    std::wstring str2 = L"HELLO WORLD";
    auto ref2 = intern.Add(str2);
    ASSERT_TRUE(!!ref2);
    ASSERT_TRUE(intern.ToString(ref2, temp));
    ASSERT_TRUE(str2 == temp);
    
    ASSERT_EQ(1, intern.GetPageCount());
    ASSERT_EQ(2, intern.GetEntryCount());
}

TEST_F(StringInternTests, test4) {
    rs::stringintern::StringIntern intern;
    
    std::u16string str1 = u"hello world";
    auto ref1 = intern.Add(str1);
    ASSERT_TRUE(!!ref1);
    std::u16string temp;
    ASSERT_TRUE(intern.ToString(ref1, temp));
    ASSERT_TRUE(str1 == temp);
    
    ASSERT_EQ(1, intern.GetPageCount());
    ASSERT_EQ(1, intern.GetEntryCount());
    
    std::u16string str2 = u"HELLO WORLD";
    auto ref2 = intern.Add(str2);
    ASSERT_TRUE(!!ref2);
    ASSERT_TRUE(intern.ToString(ref2, temp));
    ASSERT_TRUE(str2 == temp);
    
    ASSERT_EQ(1, intern.GetPageCount());
    ASSERT_EQ(2, intern.GetEntryCount());
}

TEST_F(StringInternTests, test5) {
    rs::stringintern::StringIntern intern;
    
    std::u32string str1 = U"hello world";
    auto ref1 = intern.Add(str1);
    ASSERT_TRUE(!!ref1);
    std::u32string temp;
    ASSERT_TRUE(intern.ToString(ref1, temp));
    ASSERT_TRUE(str1 == temp);
    
    ASSERT_EQ(1, intern.GetPageCount());
    ASSERT_EQ(1, intern.GetEntryCount());
    
    std::u32string str2 = U"HELLO WORLD";
    auto ref2 = intern.Add(str2);
    ASSERT_TRUE(!!ref2);
    ASSERT_TRUE(intern.ToString(ref2, temp));
    ASSERT_TRUE(str2 == temp);
    
    ASSERT_EQ(1, intern.GetPageCount());
    ASSERT_EQ(2, intern.GetEntryCount());
}

TEST_F(StringInternTests, test6) {
    rs::stringintern::StringIntern intern;
    ASSERT_EQ(0, intern.GetPageCount());
    ASSERT_EQ(0, intern.GetEntryCount());
    
    rs::stringintern::StringReference ref1;
    ASSERT_EQ(nullptr, intern.ToString(ref1));
    
    std::string str;
    ASSERT_FALSE(intern.ToString(ref1, str));
    ASSERT_EQ(0, str.size());
    
    std::wstring wstr;
    ASSERT_FALSE(intern.ToString(ref1, wstr));
    ASSERT_EQ(0, wstr.size());
    
    std::u16string u16str;
    ASSERT_FALSE(intern.ToString(ref1, u16str));
    ASSERT_EQ(0, u16str.size());
    
    std::u32string u32str;
    ASSERT_FALSE(intern.ToString(ref1, u32str));
    ASSERT_EQ(0, u32str.size());
}

TEST_F(StringInternTests, test7) {
    rs::stringintern::StringIntern intern;
    
    ASSERT_TRUE(!intern.Add(nullptr));
    ASSERT_TRUE(!intern.Add(std::string()));
    ASSERT_TRUE(!intern.Add(std::wstring()));
    ASSERT_TRUE(!intern.Add(std::u16string()));
    ASSERT_TRUE(!intern.Add(std::u32string()));
    
    ASSERT_EQ(0, intern.GetPageCount());
    ASSERT_EQ(0, intern.GetEntryCount());
}