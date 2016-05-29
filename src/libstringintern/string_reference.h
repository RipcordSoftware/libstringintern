#ifndef RS_LIBSTRINGINTERN_STRING_REFERENCE_H
#define	RS_LIBSTRINGINTERN_STRING_REFERENCE_H

#include <cstdint>

namespace rs {
namespace stringintern {

class StringReference {
public:
    StringReference();
    StringReference(uint32_t);
    StringReference(const StringReference&);
    
    bool operator!() { return reference_ != invalid_; }
    
    uint16_t Page() const;
    uint16_t Index() const;

private:
    
    const uint32_t invalid_ = -1;
    
    uint32_t reference_;

};

}}

#endif	/* RS_LIBSTRINGINTERN_STRING_REFERENCE_H */
