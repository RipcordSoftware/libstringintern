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

#include <algorithm>

#include "../string_page_sizes.h"

class StringPageSizesTests : public ::testing::Test {
protected:
    virtual void SetUp() {
        
    }
    
    virtual void TearDown() {
        
    }     
    
public:
    
    // linear search for the right entry in the page size array
    static rs::stringintern::StringPageSizes::Index GetPageSizeIndex(rs::stringintern::StringPage::entrycount_t len) {
        for (auto i = 0; i < rs::stringintern::StringPageSizes::GetMaxIndex(); ++i) {
            if (len <= rs::stringintern::StringPageSizes::GetEntrySize(i)) {
                return i;
            }
        }
        
        return rs::stringintern::StringPageSizes::Index();
    }
};

TEST_F(StringPageSizesTests, test0) {
    auto val = 0;
    auto result = rs::stringintern::StringPageSizes::GetIndex(val);
    ASSERT_TRUE(!!result);
    ASSERT_EQ(GetPageSizeIndex(val), result);    
}

TEST_F(StringPageSizesTests, test1) {
    auto val = 15;
    auto result = rs::stringintern::StringPageSizes::GetIndex(val);
    ASSERT_TRUE(!!result);
    ASSERT_EQ(GetPageSizeIndex(val), result);    
}

TEST_F(StringPageSizesTests, test2) {
    auto val = 115;
    auto result = rs::stringintern::StringPageSizes::GetIndex(val);
    ASSERT_TRUE(!!result);
    ASSERT_EQ(GetPageSizeIndex(val), result);    
}

TEST_F(StringPageSizesTests, test3) {
    auto val = 2115;
    auto result = rs::stringintern::StringPageSizes::GetIndex(val);
    ASSERT_TRUE(!!result);
    ASSERT_EQ(GetPageSizeIndex(val), result);
}

TEST_F(StringPageSizesTests, test4) {
    auto val = 12115;
    auto result = rs::stringintern::StringPageSizes::GetIndex(val);
    ASSERT_TRUE(!!result);
    ASSERT_EQ(GetPageSizeIndex(val), result);
}

TEST_F(StringPageSizesTests, test5) {
    auto val = 32115;
    auto result = rs::stringintern::StringPageSizes::GetIndex(val);
    ASSERT_TRUE(!!result);
    ASSERT_EQ(GetPageSizeIndex(val), result);
}

TEST_F(StringPageSizesTests, test6) {
    auto val = -1;
    auto result = rs::stringintern::StringPageSizes::GetIndex(val);
    ASSERT_TRUE(!result);
    ASSERT_TRUE(!GetPageSizeIndex(val));
}