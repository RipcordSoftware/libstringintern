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
#include <limits>
#include <memory>

#include "../string_page_catalog.h"

class StringPageCatalogTests : public ::testing::Test {
protected:
    virtual void SetUp() {
        
    }
    
    virtual void TearDown() {
        
    }    
    
public:
    const rs::stringintern::StringPage::entrycount_t pageEntryCount_ = 32;
    const rs::stringintern::StringPage::entrysize_t pageEntrySize_ = 32;
    const std::vector<char>::size_type pageSize_ = pageEntryCount_ * pageEntrySize_;
};

using StringPagePtr = std::unique_ptr<rs::stringintern::StringPage>;

TEST_F(StringPageCatalogTests, test0) {
    rs::stringintern::StringPageCatalog catalog{1, 1};
    ASSERT_EQ(1, catalog.Rows());
    ASSERT_EQ(1, catalog.Cols());
    ASSERT_EQ(0, catalog.Pages());
    
    ASSERT_FALSE(!!catalog.Find(0, 0));
}

TEST_F(StringPageCatalogTests, test1) {
    std::vector<char> pageBuffer(pageSize_);
    
    rs::stringintern::StringPage page{0, pageBuffer.data(), pageEntryCount_, pageEntrySize_};
    
    rs::stringintern::StringPageCatalog catalog{1, 1};
    ASSERT_EQ(1, catalog.Rows());
    ASSERT_EQ(1, catalog.Cols());
    
    ASSERT_TRUE(catalog.Add(0, &page));
        
    ASSERT_EQ(1, catalog.Pages());
    
    ASSERT_FALSE(!!catalog.Find(0, 0));
}

TEST_F(StringPageCatalogTests, test2) {
    std::vector<char> pageBuffer(pageSize_);
    rs::stringintern::StringPage page{0, pageBuffer.data(), pageEntryCount_, pageEntrySize_};
    
    rs::stringintern::StringPageCatalog catalog{1, 1};
    ASSERT_EQ(1, catalog.Rows());
    ASSERT_EQ(1, catalog.Cols());
    
    ASSERT_FALSE(catalog.Add(1, &page));
        
    ASSERT_EQ(0, catalog.Pages());
    
    ASSERT_FALSE(!!catalog.Find(1, 0));
}

TEST_F(StringPageCatalogTests, test3) {
    std::vector<char> pageBuffer(pageSize_);    
    rs::stringintern::StringPage page{0, pageBuffer.data(), pageEntryCount_, pageEntrySize_};
    page.Add("hello world", 11, 0);
    
    rs::stringintern::StringPageCatalog catalog{1, 1};
    ASSERT_EQ(1, catalog.Rows());
    ASSERT_EQ(1, catalog.Cols());
    
    ASSERT_TRUE(catalog.Add(0, &page));
        
    ASSERT_EQ(1, catalog.Pages());
    
    ASSERT_TRUE(!!catalog.Find(0, 0));
    ASSERT_FALSE(!!catalog.Find(0, 1));
}

TEST_F(StringPageCatalogTests, test4) {
    std::vector<char> pageBuffer1(pageSize_);
    rs::stringintern::StringPage page1{0, pageBuffer1.data(), pageEntryCount_, pageEntrySize_};
    page1.Add("hello world", 11, 0);
    
    std::vector<char> pageBuffer2(pageSize_);
    rs::stringintern::StringPage page2{1, pageBuffer2.data(), pageEntryCount_, pageEntrySize_};
    page2.Add("Lorem ipsum", 11, 1);
    
    rs::stringintern::StringPageCatalog catalog{2, 1};
    ASSERT_EQ(1, catalog.Rows());
    ASSERT_EQ(2, catalog.Cols());
    
    ASSERT_TRUE(catalog.Add(0, &page1));
    ASSERT_TRUE(catalog.Add(0, &page2));
        
    ASSERT_EQ(2, catalog.Pages());
    
    ASSERT_TRUE(!!catalog.Find(0, 0));    
    ASSERT_TRUE(!!catalog.Find(0, 1));
    ASSERT_FALSE(!!catalog.Find(0, 2));
}