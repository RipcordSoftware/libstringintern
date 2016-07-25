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

#include <thread>
#include <atomic>
#include <cstring>

#include "../string_page_archive.h"

class StringPageArchiveTests : public ::testing::Test {
protected:
    virtual void SetUp() {
        
    }
    
    virtual void TearDown() {
        
    }    
    
public:

    
    const rs::stringintern::StringPage::entrycount_t pageEntryCount_ = 32;
    const rs::stringintern::StringPage::entrysize_t pageEntrySize_ = 32;
    const std::size_t pageSize_ = pageEntryCount_ * pageEntrySize_;
};

TEST_F(StringPageArchiveTests, test0) {
    const auto archiveEntries = 8;
    rs::stringintern::StringPageArchive archive{archiveEntries};
    ASSERT_EQ(archiveEntries, archive.GetMaxPages());
    
    auto newPage = archive.NewPage(pageEntryCount_, pageEntrySize_);
    ASSERT_TRUE(!!newPage);
    ASSERT_EQ(0, newPage->GetPageNumber());
    ASSERT_EQ(0, newPage->GetEntryCount());
    ASSERT_EQ(pageEntryCount_, newPage->GetMaxEntryCount());
    ASSERT_EQ(pageEntrySize_, newPage->GetMaxEntrySize());
    
    auto archivePage = archive.GetPage(0);
    ASSERT_TRUE(!!archivePage);
    ASSERT_EQ(0, archivePage->GetPageNumber());
    ASSERT_EQ(0, archivePage->GetEntryCount());
    ASSERT_EQ(pageEntryCount_, archivePage->GetMaxEntryCount());
    ASSERT_EQ(pageEntrySize_, archivePage->GetMaxEntrySize());
    
    ASSERT_EQ(newPage, archivePage);
}

TEST_F(StringPageArchiveTests, test1) {
    const auto archiveEntries = 8;
    rs::stringintern::StringPageArchive archive{archiveEntries};
    ASSERT_EQ(archiveEntries, archive.GetMaxPages());
    
    for (auto i = 0; i < archiveEntries; ++i) {
        auto page = archive.NewPage(pageEntryCount_, pageEntrySize_);
        ASSERT_TRUE(!!page);
        ASSERT_EQ(i, page->GetPageNumber());
        ASSERT_EQ(0, page->GetEntryCount());
        ASSERT_EQ(pageEntryCount_, page->GetMaxEntryCount());
        ASSERT_EQ(pageEntrySize_, page->GetMaxEntrySize());
    }
    
    ASSERT_EQ(archiveEntries, archive.GetPageCount());
    
    auto badPage = archive.NewPage(pageEntryCount_, pageEntrySize_);
    ASSERT_EQ(nullptr, badPage);
    
    ASSERT_EQ(archiveEntries, archive.GetPageCount());
}

TEST_F(StringPageArchiveTests, test2) {
    const auto archiveEntries = 16384;
    rs::stringintern::StringPageArchive archive{archiveEntries};
    ASSERT_EQ(archiveEntries, archive.GetMaxPages());
    
    ASSERT_EQ(nullptr, archive.NewPage(nullptr, pageEntryCount_, pageEntrySize_));
};

TEST_F(StringPageArchiveTests, test3) {
    std::vector<rs::stringintern::StringPage::buffervalue_t> buffer(pageSize_);
    const auto archiveEntries = 16384;
    rs::stringintern::StringPageArchive archive{archiveEntries};
    ASSERT_EQ(archiveEntries, archive.GetMaxPages());
    
    std::atomic<std::uint32_t> i{0};
    auto func = [&]() {
        for (; i < archiveEntries; i++) {
            archive.NewPage(buffer.data(), pageEntryCount_, pageEntrySize_);            
        }
    };
    
    std::thread t1{func};
    std::thread t2{func};
    
    t1.join();
    t2.join();   
    
    ASSERT_EQ(archiveEntries, archive.GetPageCount());
}

TEST_F(StringPageArchiveTests, test4) {
    std::vector<rs::stringintern::StringPage::buffervalue_t> buffer(pageSize_);
    const auto archiveEntries = 16384;
    rs::stringintern::StringPageArchive archive{archiveEntries};
    ASSERT_EQ(archiveEntries, archive.GetMaxPages());
    
    auto func = [&]() {
        for (auto i = 0; i < archiveEntries; ++i) {
            archive.NewPage(buffer.data(), pageEntryCount_, pageEntrySize_);            
        }
    };
    
    std::thread t1{func};
    std::thread t2{func};
    std::thread t3{func};
    std::thread t4{func};
    
    t1.join();
    t2.join();   
    t3.join();
    t4.join();   
    
    ASSERT_EQ(archiveEntries, archive.GetPageCount());
}

TEST_F(StringPageArchiveTests, test5) {
    const auto archiveEntries = 8;
    rs::stringintern::StringPageArchive archive{archiveEntries};
    ASSERT_EQ(archiveEntries, archive.GetMaxPages());
    
    auto newPage = archive.NewPage(pageEntryCount_, pageEntrySize_);
    auto testStr1 = "this is a test";
    newPage->Add(testStr1, std::strlen(testStr1), 0);    
    ASSERT_EQ(1, archive.GetEntryCount());
    
    auto testStr2 = "this is another test";
    newPage->Add(testStr2, std::strlen(testStr2), 1);    
    ASSERT_EQ(2, archive.GetEntryCount());
    
    newPage->Add(testStr2, std::strlen(testStr2), 1);
    ASSERT_EQ(2, archive.GetEntryCount());
}

TEST_F(StringPageArchiveTests, test6) {
    const auto archiveEntries = 8;
    rs::stringintern::StringPageArchive archive{archiveEntries};
    ASSERT_EQ(archiveEntries, archive.GetMaxPages());
    
    for (auto i = 0; i < archiveEntries; i++) {
        ASSERT_TRUE(!!archive.NewPage(pageEntryCount_, pageEntrySize_));
    }
    
    for (auto i = 0; i < archiveEntries; i++) {
        ASSERT_FALSE(!!archive.NewPage(pageEntryCount_, pageEntrySize_));
    }
}