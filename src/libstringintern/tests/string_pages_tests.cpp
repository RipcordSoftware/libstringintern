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
    
    ASSERT_STREQ(str, pages.GetString(ref1));
    
    auto ref2 = pages.Add(str);
    ASSERT_EQ(1, pages.GetPageCount());
    ASSERT_EQ(0, ref2.Number());
    
    ASSERT_STREQ(str, pages.GetString(ref2));
    
    ASSERT_TRUE(ref1 == ref2);
}