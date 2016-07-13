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

#include "../string_reference.h"

class StringReferenceTests : public ::testing::Test {
protected:
    virtual void SetUp() {
        
    }
    
    virtual void TearDown() {
        
    }     
};

TEST_F(StringReferenceTests, test0) {
    rs::stringintern::StringReference ref;
    ASSERT_TRUE(!ref);
    ASSERT_FALSE(!!ref);
}

TEST_F(StringReferenceTests, test1) {
    auto ref = rs::stringintern::StringReference::New(1, 42);
    ASSERT_TRUE(!!ref);
    ASSERT_FALSE(!ref);
    ASSERT_EQ(1, ref.Number());
    ASSERT_EQ(42, ref.Index());
}

TEST_F(StringReferenceTests, test2) {
    auto ref1 = rs::stringintern::StringReference::New(1, 42);
    rs::stringintern::StringReference ref2{ref1};
    ASSERT_TRUE(!!ref1);
    ASSERT_FALSE(!ref1);
    ASSERT_EQ(1, ref1.Number());
    ASSERT_EQ(42, ref1.Index());
    ASSERT_TRUE(!!ref2);
    ASSERT_FALSE(!ref2);
    ASSERT_EQ(1, ref2.Number());
    ASSERT_EQ(42, ref2.Index());
    ASSERT_TRUE(ref1 == ref2);
}

TEST_F(StringReferenceTests, test3) {
    rs::stringintern::StringReference ref1;
    rs::stringintern::StringReference ref2{ref1};
    ASSERT_TRUE(!ref1);
    ASSERT_FALSE(!!ref1);
    ASSERT_TRUE(!ref2);
    ASSERT_FALSE(!!ref2);
    ASSERT_TRUE(ref1 == ref2);
}

TEST_F(StringReferenceTests, test4) {
    ASSERT_TRUE(!rs::stringintern::StringReference::New(0, rs::stringintern::StringReference::MaxIndex()));
}

TEST_F(StringReferenceTests, test5) {
    auto ref1 = rs::stringintern::StringReference::New(1, 42);
    auto ref2 = rs::stringintern::StringReference::New(1, 42);
    auto ref3 = rs::stringintern::StringReference::New(0, 69);
    ASSERT_TRUE(ref1 == ref2);    
    ASSERT_TRUE(ref1 != ref3);
    ASSERT_TRUE(ref2 != ref3);
}

TEST_F(StringReferenceTests, test6) {
    auto ref1 = rs::stringintern::StringReference::New(1, 42);
    auto ref2 = rs::stringintern::StringReference::New(1, 42);
    auto ref3 = rs::stringintern::StringReference::New(0, 69);
    ASSERT_FALSE(ref1 < ref2);    
    ASSERT_FALSE(ref1 < ref3);
    ASSERT_FALSE(ref2 < ref3);
    ASSERT_TRUE(ref3 < ref1);
    ASSERT_TRUE(ref3 < ref2);
}