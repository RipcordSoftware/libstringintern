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
#include <algorithm>
#include <thread>
#include <atomic>
#include <mutex>

#include "../string_page_catalog.h"

class StringPageCatalogTests : public ::testing::Test {
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
    
    const rs::stringintern::StringPage::entrycount_t pageEntryCount_ = 32;
    const rs::stringintern::StringPage::entrysize_t pageEntrySize_ = 32;
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
    auto page = NewPagePtr(0, pageEntryCount_, pageEntrySize_);
    
    rs::stringintern::StringPageCatalog catalog{1, 1};
    ASSERT_EQ(1, catalog.Rows());
    ASSERT_EQ(1, catalog.Cols());
    
    ASSERT_TRUE(catalog.Add(0, page));
    ASSERT_EQ(1, catalog.Pages());
    
    ASSERT_FALSE(!!catalog.Find(0, 0));
}

TEST_F(StringPageCatalogTests, test2) {
    auto page = NewPagePtr(42, pageEntryCount_, pageEntrySize_);
    
    rs::stringintern::StringPageCatalog catalog{1, 1};
    ASSERT_EQ(1, catalog.Rows());
    ASSERT_EQ(1, catalog.Cols());
    
    ASSERT_FALSE(catalog.Add(1, page));
    ASSERT_EQ(0, catalog.Pages());    
    ASSERT_FALSE(!!catalog.Find(1, 0));
    
    ASSERT_TRUE(catalog.Add(0, page));
    ASSERT_EQ(1, catalog.Pages());    
    
    ASSERT_FALSE(catalog.Add(0, page));
    ASSERT_EQ(1, catalog.Pages());    
    
    auto pages = catalog.GetPages(0);
    ASSERT_EQ(1, pages.size());
    ASSERT_EQ(page->Number(), pages[0]->Number());
}

TEST_F(StringPageCatalogTests, test3) {
    auto page = NewPagePtr(42, pageEntryCount_, pageEntrySize_);
    ASSERT_NE(rs::stringintern::StringPage::InvalidIndex, page->Add("hello world", 11, 0));
    
    rs::stringintern::StringPageCatalog catalog{1, 1};
    ASSERT_EQ(1, catalog.Rows());
    ASSERT_EQ(1, catalog.Cols());
    
    ASSERT_TRUE(catalog.Add(0, page));
        
    ASSERT_EQ(1, catalog.Pages());
    
    ASSERT_TRUE(!!catalog.Find(0, 0));
    ASSERT_FALSE(!!catalog.Find(0, 1));
}

TEST_F(StringPageCatalogTests, test4) {
    auto page1 = NewPagePtr(0, pageEntryCount_, pageEntrySize_);
    ASSERT_NE(rs::stringintern::StringPage::InvalidIndex, page1->Add("hello world", 11, 0));
    
    auto page2 = NewPagePtr(1, pageEntryCount_, pageEntrySize_);
    ASSERT_NE(rs::stringintern::StringPage::InvalidIndex, page2->Add("Lorem ipsum", 11, 1));
    
    rs::stringintern::StringPageCatalog catalog{2, 1};
    ASSERT_EQ(1, catalog.Rows());
    ASSERT_EQ(2, catalog.Cols());
    
    ASSERT_TRUE(catalog.Add(0, page1));
    ASSERT_TRUE(catalog.Add(0, page2));
        
    ASSERT_EQ(2, catalog.Pages());
    
    auto ref1 = catalog.Find(0, 0);
    ASSERT_TRUE(!!ref1);
    ASSERT_EQ(0, ref1.Index());
    ASSERT_EQ(0, ref1.Number());
    
    auto ref2 = catalog.Find(0, 1);
    ASSERT_TRUE(!!ref2);
    ASSERT_EQ(1, ref2.Index());
    ASSERT_EQ(1, ref2.Number());
    
    ASSERT_FALSE(!!catalog.Find(0, 2));
    
    auto pages = catalog.GetPages(0);
    ASSERT_EQ(2, pages.size());
    ASSERT_EQ(page1->Number(), pages[0]->Number());
    ASSERT_EQ(page2->Number(), pages[1]->Number());
}

TEST_F(StringPageCatalogTests, test5) {
    auto page1 = NewPagePtr(0, pageEntryCount_, pageEntrySize_);
    ASSERT_NE(rs::stringintern::StringPage::InvalidIndex, page1->Add("hello world", 11, 0));
    
    auto page2 = NewPagePtr(1, pageEntryCount_, pageEntrySize_);
    ASSERT_NE(rs::stringintern::StringPage::InvalidIndex, page2->Add("Lorem ipsum", 11, 1));
    
    rs::stringintern::StringPageCatalog catalog{2, 2};
    ASSERT_EQ(2, catalog.Rows());
    ASSERT_EQ(2, catalog.Cols());
    
    ASSERT_TRUE(catalog.Add(1, page1));
    ASSERT_TRUE(catalog.Add(1, page2));
        
    ASSERT_EQ(2, catalog.Pages());
    
    auto ref1 = catalog.Find(1, 0);
    ASSERT_TRUE(!!ref1);
    ASSERT_EQ(0, ref1.Index());
    ASSERT_EQ(0, ref1.Number());
    
    auto ref2 = catalog.Find(1, 1);
    ASSERT_TRUE(!!ref2);
    ASSERT_EQ(1, ref2.Index());
    ASSERT_EQ(1, ref2.Number());
    
    ASSERT_FALSE(!!catalog.Find(0, 0));
    ASSERT_FALSE(!!catalog.Find(0, 2));
    ASSERT_FALSE(!!catalog.Find(1, 2));
    
    auto pages = catalog.GetPages(1);
    ASSERT_EQ(2, pages.size());
    ASSERT_EQ(page1->Number(), pages[0]->Number());
    ASSERT_EQ(page2->Number(), pages[1]->Number());
}

TEST_F(StringPageCatalogTests, test6) {
    rs::stringintern::StringPageCatalog::rowcount_t testRows = 7;
    rs::stringintern::StringPageCatalog::colcount_t testCols = 21;
    const auto testPages = testRows * testCols;   
    
    std::vector<rs::stringintern::StringPagePtr> pages(testPages);
    
    rs::stringintern::StringPageCatalog catalog{testCols, testRows};
    ASSERT_EQ(testRows, catalog.Rows());
    ASSERT_EQ(testCols, catalog.Cols());
    
    rs::stringintern::StringPage::pagenumber_t pageIndex = 0;
    for (auto row = 0; row < catalog.Rows(); ++row) {
        for (auto col = 0; col < catalog.Cols(); ++col, ++pageIndex) {
            auto pageText = std::to_string(pageIndex);            
            
            auto page = rs::stringintern::StringPage::New(pageIndex, pageEntryCount_, pageEntrySize_);
            ASSERT_NE(rs::stringintern::StringPage::InvalidIndex, page->Add(pageText.c_str(), pageText.size(), pageIndex));
            
            ASSERT_TRUE(catalog.Add(row, page));
            
            pages.emplace_back(page);
        }
    }
    
    ASSERT_EQ(pageIndex, catalog.Pages());
    
    pageIndex = 0;
    for (auto row = 0; row < catalog.Rows(); ++row) {
        for (auto col = 0; col < catalog.Cols(); ++col, ++pageIndex) {
            ASSERT_TRUE(!!catalog.Find(row, pageIndex));
        }
    }
    
    pageIndex = 0;
    for (auto row = 0; row < catalog.Rows(); ++row) {
        for (auto col = 0; col < catalog.Cols(); ++col, ++pageIndex) {
            ASSERT_FALSE(!!catalog.Find(row + 1, pageIndex));
        }
    }
    
    pageIndex = catalog.Pages();
    for (auto row = 0; row < catalog.Rows(); ++row, ++pageIndex) {
        auto page = rs::stringintern::StringPage::New(pageIndex, pageEntryCount_, pageEntrySize_);
        
        ASSERT_FALSE(catalog.Add(row, page));
        
        pages.emplace_back(page);
    }
    
    ASSERT_EQ(testPages, catalog.Pages());        
    
    pageIndex = 0;
    for (auto row = 0; row < catalog.Rows(); ++row) {
        auto catalogPages = catalog.GetPages(row);
        ASSERT_EQ(testCols, catalogPages.size());
        
        for (auto col = 0; col < catalog.Cols(); ++col, ++pageIndex) {
            ASSERT_EQ(pageIndex, catalogPages[col]->Number());
        }
    }
}

TEST_F(StringPageCatalogTests, test7) {
    const auto maxThreads = 8;
    const rs::stringintern::StringPageCatalog::rowcount_t testRows = 1;
    const rs::stringintern::StringPageCatalog::colcount_t testCols = rs::stringintern::StringReference::MaxNumber();
    const auto testPages = testRows * testCols;
    
    rs::stringintern::StringPageCatalog catalog{testCols, testRows};
    ASSERT_EQ(testRows, catalog.Rows());
    ASSERT_EQ(testCols, catalog.Cols());
    
    std::vector<rs::stringintern::StringPagePtr> pages;
    pages.reserve(testPages);
    
    std::atomic<rs::stringintern::StringPage::pagenumber_t> pageIndex{0};
    for (auto row = 0; row < catalog.Rows(); ++row) {
        for (auto col = 0; col < catalog.Cols(); ++col, ++pageIndex) {
            auto page = rs::stringintern::StringPage::New(pageIndex, pageEntryCount_, pageEntrySize_);
            pages.emplace_back(page);
        }
    }
    
    pageIndex = 0;
    std::atomic<bool> thread_wait{true};
    
    auto func = [&]() {       
        while (thread_wait) {
            std::this_thread::yield();
        }
        
        for (auto row = 0; row < catalog.Rows(); ++row) {
            auto added = true;
            for (auto col = 0; added && col < catalog.Cols(); ++col) {
                auto index = pageIndex.fetch_add(1, std::memory_order_relaxed);
                if (index < testPages) {
                    auto& page = pages[index];
                    added = catalog.Add(row, page);
                } else {
                    added = false;
                }
            }
        }
    };
    
    std::vector<std::thread> threads;
    for (auto i = 0; i < maxThreads; ++i) {
        threads.emplace_back(func);
    }    
    
    thread_wait = false;        
    std::for_each(threads.begin(), threads.end(), [](std::thread& t) { t.join(); });
    
    ASSERT_EQ(testPages, catalog.Pages());
        
    for (auto row = 0; row < catalog.Rows(); ++row) {
        auto rowPages = catalog.GetPages(row);

        ASSERT_EQ(catalog.Cols(), rowPages.size());
    
        std::vector<bool> pagesFound(catalog.Cols());
        std::for_each(rowPages.begin(), rowPages.end(), [&](rs::stringintern::StringPagePtr p) { pagesFound[p->Number()] = true; });        
        ASSERT_EQ(catalog.Cols(), std::count(pagesFound.begin(), pagesFound.end(), true));
    }
}

TEST_F(StringPageCatalogTests, test8) {
    const auto maxThreads = 8;
    rs::stringintern::StringPageCatalog::rowcount_t testRows = maxThreads;
    rs::stringintern::StringPageCatalog::colcount_t testCols = rs::stringintern::StringReference::MaxNumber() / maxThreads;
    rs::stringintern::StringPage::pagenumber_t testPages = testRows * testCols;
    
    rs::stringintern::StringPageCatalog catalog{testCols, testRows};
    ASSERT_EQ(testRows, catalog.Rows());
    ASSERT_EQ(testCols, catalog.Cols());
    
    std::vector<rs::stringintern::StringPagePtr> pages;
    pages.reserve(testPages);
    
    decltype(testPages) pageIndex = 0;
    for (decltype(testRows) row = 0; row < catalog.Rows(); ++row) {
        for (decltype(testCols) col = 0; col < catalog.Cols(); ++col, ++pageIndex) {
            auto page = rs::stringintern::StringPage::New(pageIndex, pageEntryCount_, pageEntrySize_);
            pages.emplace_back(page);
        }
    }
    
    std::atomic<bool> thread_wait{true};
    
    std::atomic<rs::stringintern::StringPageCatalog::rowcount_t> threadRows{0};
    
    auto func = [&]() {       
        while (thread_wait) {
            std::this_thread::yield();
        }
        
        auto row = threadRows.fetch_add(1, std::memory_order_relaxed);
        auto added = true;
        for (auto col = 0; added && col < catalog.Cols(); ++col) {
            auto index = (row * catalog.Cols()) + col;
            auto& page = pages[index];
            added = catalog.Add(row, page);
        }
    };

    std::vector<std::thread> threads;
    for (auto i = 0; i < maxThreads; ++i) {
        threads.emplace_back(func);
    }

    thread_wait = false;
    std::for_each(threads.begin(), threads.end(), [](std::thread& t) { t.join(); });

    ASSERT_EQ(testPages, catalog.Pages());
        
    for (auto row = 0; row < catalog.Rows(); ++row) {
        auto rowPages = catalog.GetPages(row);

        ASSERT_EQ(catalog.Cols(), rowPages.size());
        
        std::vector<bool> pagesFound(catalog.Cols());
        const auto pagesFoundOffset = (row * catalog.Cols());
        std::for_each(rowPages.begin(), rowPages.end(), [&](rs::stringintern::StringPagePtr p) { pagesFound[p->Number() - pagesFoundOffset] = true; });        
        ASSERT_EQ(catalog.Cols(), std::count(pagesFound.begin(), pagesFound.end(), true));
    }
}