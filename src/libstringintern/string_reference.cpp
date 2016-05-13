#include "string_reference.h"

rs::stringintern::StringReference::StringReference(uint32_t reference) : reference_(reference) {    
}

rs::stringintern::StringReference::StringReference(const StringReference& rhs) : reference_(rhs.reference_) { 

}

uint16_t rs::stringintern::StringReference::Page() const {
    return reference_ >> 16;
}

uint16_t rs::stringintern::StringReference::Index() const {
    return reference_ & 0xffff;
}