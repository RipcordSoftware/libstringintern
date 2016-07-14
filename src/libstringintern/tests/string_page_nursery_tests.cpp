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
    const rs::stringintern::StringPageNursery::pagesize_t nurseryPageSize_ = 2 * 1024 * 1024;

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
    ASSERT_TRUE(!!iter);
    ASSERT_EQ(0, nursery.Next(iter)->GetPageNumber());
    ASSERT_TRUE(!!iter);
    ASSERT_EQ(1, nursery.Next(iter)->GetPageNumber());
    ASSERT_TRUE(!!iter);
    ASSERT_EQ(2, nursery.Next(iter)->GetPageNumber());
    ASSERT_TRUE(!!iter);
    
    auto pages = nursery.GetPages(0);
    ASSERT_EQ(3, pages.size());
    ASSERT_EQ(0, pages[0]->GetPageNumber());
    ASSERT_EQ(1, pages[1]->GetPageNumber());
    ASSERT_EQ(2, pages[2]->GetPageNumber());
    
    auto pageCounts = nursery.GetPageEntryCounts(0);
    ASSERT_EQ(3, pageCounts.size());
    ASSERT_EQ(0, pageCounts[0]);
    ASSERT_EQ(0, pageCounts[1]);
    ASSERT_EQ(0, pageCounts[2]);
}

TEST_F(StringPageNurseryTests, test1) {
    rs::stringintern::StringPageNursery nursery(
        StringPageNurseryTests::nurseryCols_, 
        1,
        StringPageNurseryTests::nurseryPageSize_,
        StringPageNurseryTests::NewPage);
    
    auto iter0 = nursery.Iter(0);
    ASSERT_TRUE(!!iter0);
    
    auto iter1 = nursery.Iter(1);
    ASSERT_FALSE(!!iter1);
    
    auto iter2 = nursery.Iter(2);
    ASSERT_FALSE(!!iter2);
    
    auto iter42 = nursery.Iter(42);
    ASSERT_FALSE(!!iter42);
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
            ASSERT_TRUE(!!iter);
            ASSERT_EQ(i, nursery.Next(iter)->GetPageNumber());            
        } else {
            ASSERT_TRUE(!iter);
            ASSERT_TRUE(!nursery.Next(iter));
        }
    }
    
    auto pages = nursery.GetPages(0);
    ASSERT_EQ(cols, pages.size());
    
    auto pageCounts = nursery.GetPageEntryCounts(0);
    ASSERT_EQ(cols, pageCounts.size());
}

TEST_F(StringPageNurseryTests, test3) {
    rs::stringintern::StringPageNursery nursery(
        StringPageNurseryTests::nurseryCols_, 
        1,
        StringPageNurseryTests::nurseryPageSize_,
        StringPageNurseryTests::NewPage);
        
    ASSERT_EQ(0, nursery.GetPages(0).size());    
    ASSERT_EQ(0, nursery.GetPageEntryCounts(0).size());    
    
    auto iter = nursery.Iter(0);
    const auto cols = nursery.Cols();
    for (auto i = 0; i < cols; ++i) {
        ASSERT_TRUE(!!iter);
        ASSERT_EQ(i, nursery.Next(iter)->GetPageNumber());
        ASSERT_EQ(i + 1, nursery.GetPages(0).size());
        ASSERT_EQ(i + 1, nursery.GetPageEntryCounts(0).size());
    }
    
    auto pages = nursery.GetPages(0);
    ASSERT_EQ(cols, pages.size());
    for (auto i = 0; i < cols; ++i) {
        ASSERT_EQ(i, pages[i]->GetPageNumber());
    }
    
    auto entries = nursery.GetPageEntryCounts(0);
    ASSERT_EQ(cols, entries.size());
    for (auto i = 0; i < cols; ++i) {
        ASSERT_EQ(0, entries[i]);
    }
}

TEST_F(StringPageNurseryTests, test4) {
    auto str = "hello world";
    const auto len = std::strlen(str);
    const auto testEntriesPerPage = 8;
    
    rs::stringintern::StringPageNursery nursery(
        StringPageNurseryTests::nurseryCols_, 
        1,
        StringPageNurseryTests::nurseryPageSize_,
        StringPageNurseryTests::NewPage);
    
    auto iter = nursery.Iter(0);
    ASSERT_FALSE(!iter);
    
    const auto cols = nursery.Cols();
    for (auto i = 0; i < cols; ++i) {
        auto page = nursery.Next(iter);
        ASSERT_TRUE(!!page);
        for (auto j = 0; j < testEntriesPerPage; ++j) {
            ASSERT_TRUE(!!page->Add(str, len, j));
        }
    }   
    
    auto entries = nursery.GetPageEntryCounts(0);
    ASSERT_EQ(cols, entries.size());
    for (auto i = 0; i < cols; ++i) {
        ASSERT_EQ(testEntriesPerPage, entries[i]);
    }
}

TEST_F(StringPageNurseryTests, test5) {
    auto str = "hello world";
    const auto len = std::strlen(str);
    const auto testEntriesPerPage = 8;
    
    rs::stringintern::StringPageNursery nursery(
        StringPageNurseryTests::nurseryCols_, 
        3,
        StringPageNurseryTests::nurseryPageSize_,
        StringPageNurseryTests::NewPage);
    
    auto iter0 = nursery.Iter(0);    
    auto iter1 = nursery.Iter(1);
    auto iter2 = nursery.Iter(2);
    ASSERT_TRUE(!!iter2);
    
    const auto cols = nursery.Cols();
    for (auto i = 0; i < cols; ++i) {
        ASSERT_TRUE(!!iter0);
        auto page1 = nursery.Next(iter0);        
        ASSERT_TRUE(!!page1);
    
        ASSERT_TRUE(!!iter1);
        auto page2 = nursery.Next(iter1);
        ASSERT_TRUE(!!page2);
        
        for (auto j = 0; j < testEntriesPerPage; ++j) {
            ASSERT_TRUE(!!page1->Add(str, len, j));
            
            if (j & 1) {                                
                ASSERT_TRUE(!!page2->Add(str, len, j));    
            }
        }       
    }   
    
    ASSERT_TRUE(!iter0);
    ASSERT_TRUE(!iter1);
    ASSERT_TRUE(!!iter2);
    
    auto entries1 = nursery.GetPageEntryCounts(0);
    ASSERT_EQ(cols, entries1.size());
    for (auto i = 0; i < cols; ++i) {
        ASSERT_EQ(testEntriesPerPage, entries1[i]);
    }
    
    auto entries2 = nursery.GetPageEntryCounts(1);
    ASSERT_EQ(cols, entries2.size());
    for (auto i = 0; i < cols; ++i) {
        ASSERT_EQ(testEntriesPerPage / 2, entries2[i]);
    }
    
    ASSERT_EQ(0, nursery.GetPageEntryCounts(2).size());    
}