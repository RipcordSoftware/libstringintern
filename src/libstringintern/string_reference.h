#ifndef RS_LIBSTRINGINTERN_STRING_REFERENCE_H
#define	RS_LIBSTRINGINTERN_STRING_REFERENCE_H

#include <cstdint>

namespace rs {
namespace stringintern {

class StringReference {
public:
    StringReference(uint32_t);
    StringReference(const StringReference&);
    
    uint16_t Page() const;
    uint16_t Index() const;

private:
    
    uint32_t reference_;

};

}}

#endif	/* RS_LIBSTRINGINTERN_STRING_REFERENCE_H */
