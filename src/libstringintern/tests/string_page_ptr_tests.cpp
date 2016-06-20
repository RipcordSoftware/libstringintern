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

#include <vector>
#include <algorithm>

#include "../string_page_ptr.h"
#include "../string_page.h"

class StringPagePtrTests : public ::testing::Test {
protected:
    virtual void SetUp() {
        
    }
    
    virtual void TearDown() {
        
    }
    
public:    
    rs::stringintern::StringPagePtr NewPagePtr(std::size_t number = 0) {
        return rs::stringintern::StringPage::New(number, pageEntryCount_, pageEntrySize_);
    }  
    
    const rs::stringintern::StringPage::entrycount_t pageEntryCount_ = 32;
    const rs::stringintern::StringPage::entrysize_t pageEntrySize_ = 32;
};

TEST_F(StringPagePtrTests, test0) {
    rs::stringintern::StringPagePtr page;
    ASSERT_TRUE(!page);
    ASSERT_EQ(0, page.RefCount());
}

TEST_F(StringPagePtrTests, test1) {
    auto page1 = NewPagePtr();
    ASSERT_TRUE(!!page1);
    ASSERT_EQ(1, page1.RefCount());
    
    auto page2 = page1;
    ASSERT_TRUE(!!page1);
    ASSERT_TRUE(!!page2);
    ASSERT_EQ(2, page1.RefCount());
    ASSERT_EQ(2, page2.RefCount());
    
    ASSERT_TRUE(page1 == page2);
    ASSERT_TRUE(!!page1);
    ASSERT_TRUE(!!page2);
    ASSERT_EQ(2, page1.RefCount());
    ASSERT_EQ(2, page2.RefCount());
    
    rs::stringintern::StringPagePtr page3;
    page3 = page1;
    ASSERT_TRUE(!!page1);
    ASSERT_TRUE(!!page2);
    ASSERT_TRUE(!!page3);
    ASSERT_EQ(3, page1.RefCount());
    ASSERT_EQ(3, page2.RefCount());
    ASSERT_EQ(3, page3.RefCount());       
    
    ASSERT_TRUE(page1 == page2);
    ASSERT_TRUE(page1 == page3);
}

TEST_F(StringPagePtrTests, test2) {
    auto page1 = NewPagePtr();
    ASSERT_TRUE(!!page1);
    ASSERT_EQ(1, page1.RefCount());
    
    auto page2 = NewPagePtr();
    ASSERT_TRUE(!!page2);
    ASSERT_EQ(1, page1.RefCount());
    ASSERT_EQ(1, page2.RefCount());
    
    ASSERT_TRUE(page1 != page2);
    
    page2 = page1;
    ASSERT_TRUE(!!page1);
    ASSERT_TRUE(!!page2);
    ASSERT_EQ(2, page1.RefCount());
    ASSERT_EQ(2, page2.RefCount());
    
    ASSERT_TRUE(page1 == page2);
}

TEST_F(StringPagePtrTests, test3) {
    auto page1 = NewPagePtr();
    ASSERT_TRUE(!!page1);
    ASSERT_EQ(1, page1.RefCount());
    
    if (true) {
        auto page2 = page1;
        ASSERT_TRUE(!!page1);
        ASSERT_TRUE(!!page2);
        ASSERT_EQ(2, page1.RefCount());
        ASSERT_EQ(2, page2.RefCount());
    }
    
    ASSERT_TRUE(!!page1);
    ASSERT_EQ(1, page1.RefCount());
}


TEST_F(StringPagePtrTests, test4) {
    auto page1 = NewPagePtr();
    ASSERT_TRUE(!!page1);
    ASSERT_EQ(1, page1.RefCount());
    
    rs::stringintern::StringPagePtr page2{std::move(page1)};
    ASSERT_TRUE(!page1);
    ASSERT_EQ(0, page1.RefCount());
    ASSERT_TRUE(!!page2);
    ASSERT_EQ(1, page2.RefCount());
}

TEST_F(StringPagePtrTests, test5) {
    auto page1 = NewPagePtr();
    rs::stringintern::StringPagePtr page2;
    rs::stringintern::StringPagePtr nullPage;
    
    ASSERT_TRUE(page2.compare_exchange_strong(nullPage, page1, std::memory_order_relaxed));
    ASSERT_TRUE(!!page1);
    ASSERT_TRUE(!!page2);
    ASSERT_TRUE(!nullPage);
    ASSERT_EQ(2, page1.RefCount());
    ASSERT_EQ(2, page2.RefCount());
    ASSERT_TRUE(page1 == page2);
}

TEST_F(StringPagePtrTests, test6) {
    auto page1 = NewPagePtr();
    auto page2 = NewPagePtr();
    rs::stringintern::StringPagePtr nullPage;
    
    ASSERT_FALSE(page2.compare_exchange_strong(nullPage, page1, std::memory_order_relaxed));
    ASSERT_TRUE(!!page1);
    ASSERT_TRUE(!!page2);
    ASSERT_TRUE(!!nullPage);
    ASSERT_EQ(1, page1.RefCount());
    ASSERT_EQ(2, page2.RefCount());
    ASSERT_TRUE(page1 != page2);
    ASSERT_TRUE(page2 == nullPage);
}

TEST_F(StringPagePtrTests, test7) {
    auto page1 = NewPagePtr();
    auto page2 = NewPagePtr();
    auto nullPage(page2);
    
    ASSERT_TRUE(page2.compare_exchange_strong(nullPage, page1, std::memory_order_relaxed));
    ASSERT_TRUE(!!page1);
    ASSERT_TRUE(!!page2);
    ASSERT_TRUE(!!nullPage);
    ASSERT_EQ(2, page1.RefCount());
    ASSERT_EQ(2, page2.RefCount());
    ASSERT_EQ(1, nullPage.RefCount());
    ASSERT_TRUE(page1 == page2);
    ASSERT_TRUE(page2 != nullPage);
}

TEST_F(StringPagePtrTests, test8) {
    auto page = NewPagePtr();
    std::vector<decltype(page)> pages{page};
    ASSERT_TRUE(!!page);
    ASSERT_EQ(2, page.RefCount());
}

TEST_F(StringPagePtrTests, test9) {
    auto page = NewPagePtr();
    std::vector<decltype(page)> pages;
    
    pages.emplace_back(page);
    ASSERT_TRUE(!!pages[0]);
    ASSERT_EQ(2, pages[0].RefCount());
    ASSERT_TRUE(!!page);
    ASSERT_EQ(2, page.RefCount());        
}

TEST_F(StringPagePtrTests, test10) {
    auto page = NewPagePtr();
    std::vector<decltype(page)> pages;
    
    pages.emplace_back(std::move(page));
    ASSERT_TRUE(!!pages[0]);
    ASSERT_EQ(1, pages[0].RefCount());
    ASSERT_TRUE(!page);
    ASSERT_EQ(0, page.RefCount());        
}

TEST_F(StringPagePtrTests, test11) {
    auto page1 = NewPagePtr();
    rs::stringintern::StringPagePtr page2;
    
    page2 = std::move(page1);    
    
    ASSERT_TRUE(!page1);
    ASSERT_TRUE(!!page2);
}

TEST_F(StringPagePtrTests, test12) {
    auto page1 = NewPagePtr();
    rs::stringintern::StringPagePtr page2;
    
    std::swap(page1, page2);
    
    ASSERT_TRUE(!page1);
    ASSERT_TRUE(!!page2);
}