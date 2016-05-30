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

#include "../string_hash.h"

class StringHashTests : public ::testing::Test {
protected:
    virtual void SetUp() {
        
    }
    
    virtual void TearDown() {
        
    }     
};

TEST_F(StringHashTests, test0) {
    ASSERT_EQ(0, rs::stringintern::StringHash::Get(nullptr));
    ASSERT_EQ(0, rs::stringintern::StringHash::Get(nullptr, 0));
    ASSERT_EQ(0, rs::stringintern::StringHash::Get(nullptr, 256));
}

TEST_F(StringHashTests, test1) {
    auto str = "Hello world";
    
    auto hash1 = rs::stringintern::StringHash::Get(str);
    auto hash2 = rs::stringintern::StringHash::Get(str, std::strlen(str));
    
    ASSERT_NE(0, hash1);
    ASSERT_NE(0, hash2);
    
    ASSERT_EQ(hash1, hash2);
}

TEST_F(StringHashTests, test2) {
    auto str = 
        "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vivamus sed faucibus lacus, vel auctor risus. Aliquam vehicula magna quis pretium fermentum. "
        "In cursus metus ex, quis tincidunt mauris congue venenatis. Vivamus metus justo, dictum ut rhoncus in, placerat nec elit. Cras tristique tellus sit amet "
        "sollicitudin dignissim. Pellentesque semper leo neque, ac fermentum purus porta sit amet. Donec tellus orci, pharetra quis ligula at, egestas malesuada "
        "dui. Nunc varius efficitur ante at elementum. Sed sed nulla viverra, malesuada sapien eu, fermentum lacus. Vestibulum ante ipsum primis in faucibus orci "
        "luctus et ultrices posuere cubilia Curae; Aliquam pellentesque libero consequat, cursus nisi id, sodales nunc.";
    
    auto hash1 = rs::stringintern::StringHash::Get(str);
    auto hash2 = rs::stringintern::StringHash::Get(str, std::strlen(str));
    
    ASSERT_NE(0, hash1);
    ASSERT_NE(0, hash2);
    
    ASSERT_EQ(hash1, hash2);
}

TEST_F(StringHashTests, test3) {
    auto str = 
        "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vivamus sed faucibus lacus, vel auctor risus. Aliquam vehicula magna quis pretium fermentum. "
        "In cursus metus ex, quis tincidunt mauris congue venenatis. Vivamus metus justo, dictum ut rhoncus in, placerat nec elit. Cras tristique tellus sit amet "
        "sollicitudin dignissim. Pellentesque semper leo neque, ac fermentum purus porta sit amet. Donec tellus orci, pharetra quis ligula at, egestas malesuada "
        "dui. Nunc varius efficitur ante at elementum. Sed sed nulla viverra, malesuada sapien eu, fermentum lacus. Vestibulum ante ipsum primis in faucibus orci "
        "luctus et ultrices posuere cubilia Curae; Aliquam pellentesque libero consequat, cursus nisi id, sodales nunc.";
    
    std::string bigStr(str);
    bigStr += bigStr;
    bigStr += bigStr;
    bigStr += bigStr;
    
    auto hash1 = rs::stringintern::StringHash::Get(bigStr.c_str());
    auto hash2 = rs::stringintern::StringHash::Get(bigStr.c_str(), bigStr.length());
    
    ASSERT_NE(0, hash1);
    ASSERT_NE(0, hash2);
    
    ASSERT_EQ(hash1, hash2);
}

TEST_F(StringHashTests, test5) {
    auto str1 = "Hello world";
    auto str2 = "arfle barfle gloop";
    
    auto hash1 = rs::stringintern::StringHash::Get(str1, std::strlen(str2));
    auto hash2 = rs::stringintern::StringHash::Get(str2, std::strlen(str2));
    
    ASSERT_NE(0, hash1);
    ASSERT_NE(0, hash2);
    
    ASSERT_NE(hash1, hash2);
}

TEST_F(StringHashTests, test6) {
    auto str1 = "Hello world";
    auto str2 = "hello world";
    
    auto hash1 = rs::stringintern::StringHash::Get(str1, std::strlen(str2));
    auto hash2 = rs::stringintern::StringHash::Get(str2, std::strlen(str2));
    
    ASSERT_NE(0, hash1);
    ASSERT_NE(0, hash2);
    
    ASSERT_NE(hash1, hash2);
}