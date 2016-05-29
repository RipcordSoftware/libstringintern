#ifndef RS_LIBSTRINGINTERN_STRING_HASH_H
#define	RS_LIBSTRINGINTERN_STRING_HASH_H

#include <cstdint>

namespace rs {
namespace stringintern {

class StringHash {
public:
    
    using Hash = std::uint64_t;
    static const int seed_ = 42;
    
    StringHash() = delete;
    StringHash(const StringHash&) = delete;
    
    static Hash Get(const char*);
    static Hash Get(const char*, std::size_t len);

private:

};

}}

#endif	/* RS_LIBSTRINGINTERN_STRING_HASH_H */

