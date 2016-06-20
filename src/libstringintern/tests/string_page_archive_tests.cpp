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
    ASSERT_EQ(archiveEntries, archive.MaxEntries());
    
    auto newPage = archive.NewPage(pageEntryCount_, pageEntrySize_);
    ASSERT_TRUE(!!newPage);
    ASSERT_EQ(0, newPage->Number());
    ASSERT_EQ(0, newPage->Count());
    ASSERT_EQ(pageEntryCount_, newPage->EntryCount());
    ASSERT_EQ(pageEntrySize_, newPage->EntrySize());
    
    auto archivePage = archive.GetPage(0);
    ASSERT_TRUE(!!archivePage);
    ASSERT_EQ(0, archivePage->Number());
    ASSERT_EQ(0, archivePage->Count());
    ASSERT_EQ(pageEntryCount_, archivePage->EntryCount());
    ASSERT_EQ(pageEntrySize_, archivePage->EntrySize());
    
    ASSERT_EQ(newPage, archivePage);
}

TEST_F(StringPageArchiveTests, test1) {
    const auto archiveEntries = 8;
    rs::stringintern::StringPageArchive archive{archiveEntries};
    ASSERT_EQ(archiveEntries, archive.MaxEntries());
    
    for (auto i = 0; i < archiveEntries; ++i) {
        auto page = archive.NewPage(pageEntryCount_, pageEntrySize_);
        ASSERT_TRUE(!!page);
        ASSERT_EQ(i, page->Number());
        ASSERT_EQ(0, page->Count());
        ASSERT_EQ(pageEntryCount_, page->EntryCount());
        ASSERT_EQ(pageEntrySize_, page->EntrySize());
    }
    
    ASSERT_EQ(archiveEntries, archive.Count());
    
    auto badPage = archive.NewPage(pageEntryCount_, pageEntrySize_);
    ASSERT_EQ(nullptr, badPage);
    
    ASSERT_EQ(archiveEntries, archive.Count());
}

TEST_F(StringPageArchiveTests, test2) {
    const auto archiveEntries = 16384;
    rs::stringintern::StringPageArchive archive{archiveEntries};
    ASSERT_EQ(archiveEntries, archive.MaxEntries());
    
    ASSERT_EQ(nullptr, archive.NewPage(nullptr, pageEntryCount_, pageEntrySize_));
};

TEST_F(StringPageArchiveTests, test3) {
    std::vector<rs::stringintern::StringPage::buffervalue_t> buffer(pageSize_);
    const auto archiveEntries = 16384;
    rs::stringintern::StringPageArchive archive{archiveEntries};
    ASSERT_EQ(archiveEntries, archive.MaxEntries());
    
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
    
    ASSERT_EQ(archiveEntries, archive.Count());
}

TEST_F(StringPageArchiveTests, test4) {
    std::vector<rs::stringintern::StringPage::buffervalue_t> buffer(pageSize_);
    const auto archiveEntries = 16384;
    rs::stringintern::StringPageArchive archive{archiveEntries};
    ASSERT_EQ(archiveEntries, archive.MaxEntries());
    
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
    
    ASSERT_EQ(archiveEntries, archive.Count());
}