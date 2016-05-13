#include "string_intern.h"

#include <cstring>

#include "xxhash.h"

rs::stringintern::StringReference rs::stringintern::StringIntern::Add(const char* str) {
    auto len = std::strlen(str);
    auto hash = XXH64(str, len, 42);
}

const char* rs::stringintern::StringIntern::ToString(const StringReference& ref) const {
    
}