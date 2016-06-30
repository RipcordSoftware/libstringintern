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

#include "../string_page_nursery.h"

class StringPageNurseryTests : public ::testing::Test {
protected:
    virtual void SetUp() {
        ResetPageNumber();
    }
    
    virtual void TearDown() {
        
    }
    
private:
    static rs::stringintern::StringPage::pagenumber_t pageNumber_;
    
public:
    
    static rs::stringintern::StringPagePtr NewPage(rs::stringintern::StringPageNursery::rowcount_t row,
    rs::stringintern::StringPage::entrycount_t entryCount, rs::stringintern::StringPage::entrysize_t entrySize) {
        return rs::stringintern::StringPage::New(pageNumber_++, entryCount, entrySize);
    }
    
    static void ResetPageNumber() { pageNumber_ = 0; }
    
    const rs::stringintern::StringPageNursery::colcount_t nurseryCols_ = 8;
    const rs::stringintern::StringPageNursery::rowcount_t nurseryRows_ = 32;
    const rs::stringintern::StringPageNursery::pagesize_t nurseryPageSize_ = 4 * 1024 * 1024;

};

rs::stringintern::StringPage::pagenumber_t StringPageNurseryTests::pageNumber_ = 0;

TEST_F(StringPageNurseryTests, test0) {
    rs::stringintern::StringPageNursery nursery(
        StringPageNurseryTests::nurseryCols_, 
        StringPageNurseryTests::nurseryRows_,
        StringPageNurseryTests::nurseryPageSize_,
        StringPageNurseryTests::NewPage);
    
    ASSERT_EQ(StringPageNurseryTests::nurseryCols_, nursery.Cols());
    ASSERT_EQ(StringPageNurseryTests::nurseryRows_, nursery.Rows());
    
    auto iter = nursery.Iter(0);
    ASSERT_FALSE(!iter);
    ASSERT_EQ(0, nursery.Next(iter)->Number());
    ASSERT_FALSE(!iter);
    ASSERT_EQ(1, nursery.Next(iter)->Number());
    ASSERT_FALSE(!iter);
    ASSERT_EQ(2, nursery.Next(iter)->Number());
    ASSERT_FALSE(!iter);
}

TEST_F(StringPageNurseryTests, test2) {
    rs::stringintern::StringPageNursery nursery(
        StringPageNurseryTests::nurseryCols_, 
        StringPageNurseryTests::nurseryRows_,
        StringPageNurseryTests::nurseryPageSize_,
        StringPageNurseryTests::NewPage);
    
    ASSERT_EQ(StringPageNurseryTests::nurseryCols_, nursery.Cols());
    ASSERT_EQ(StringPageNurseryTests::nurseryRows_, nursery.Rows());
    
    auto iter = nursery.Iter(0);
    const auto cols = nursery.Cols();
    for (auto i = 0; i < cols * 4; ++i) {
        if (i < cols) {
            ASSERT_FALSE(!iter);
            ASSERT_EQ(i, nursery.Next(iter)->Number());            
        } else {
            ASSERT_TRUE(!iter);
            ASSERT_TRUE(!nursery.Next(iter));
        }
    }
}
