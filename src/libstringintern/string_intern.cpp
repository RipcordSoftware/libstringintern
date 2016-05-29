#include "string_intern.h"

#include <cstring>

#include "string_hash.h"

rs::stringintern::StringIntern::StringIntern() {
    
}

rs::stringintern::StringReference rs::stringintern::StringIntern::Add(const char* str) {
    auto len = std::strlen(str);
    auto hash = StringHash::Get(str, len);
}

const char* rs::stringintern::StringIntern::ToString(const StringReference& ref) const {
    
}