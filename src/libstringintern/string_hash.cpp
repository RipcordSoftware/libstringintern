#include "string_hash.h"

#include <cstring>

#include "xxhash.h"

rs::stringintern::StringHash::Hash rs::stringintern::StringHash::Get(const char* str) {
    return !!str ? Get(str, std::strlen(str)) : 0;
}

rs::stringintern::StringHash::Hash rs::stringintern::StringHash::Get(const char* str, std::size_t len) {
    return !!str ? XXH64(str, len, seed_) : 0;
}
