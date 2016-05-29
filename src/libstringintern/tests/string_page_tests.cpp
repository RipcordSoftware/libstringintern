#include <gtest/gtest.h>

#include <cstring>

#include "../string_page.h"

class StringPageTests : public ::testing::Test {
protected:
    virtual void SetUp() {
        
    }
    
    virtual void TearDown() {
        
    }     
};

TEST_F(StringPageTests, test0) {
    const auto pageSize = 2 * 1024 * 1024;
    const auto pageEntrySize = 256;
    const auto pageEntries = pageSize / pageEntrySize;

    rs::stringintern::StringPage page(pageSize, pageEntrySize);
    
    ASSERT_EQ(pageEntries, page.EntryCount());
    ASSERT_EQ(pageEntrySize, page.EntrySize());
    
    const char* str = "Hello world";
    const auto len = std::strlen(str);
    ASSERT_EQ(1, page.Add(str, len, 1));
    ASSERT_EQ(1, page.Add(str, len, 1));
    ASSERT_EQ(rs::stringintern::StringPage::InvalidIndex, page.Add(str, len, 1 + pageEntries));
}