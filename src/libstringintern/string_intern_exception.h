#ifndef RS_LIBSTRINGINTERN_STRING_INTERN_EXCEPTION_H
#define	RS_LIBSTRINGINTERN_STRING_INTERN_EXCEPTION_H

#include <exception>
#include <string>

namespace rs {
namespace stringintern {
    
class StringInternException : public std::exception {
public:
    StringInternException(const char* reason) : reason_(reason) {}
    
    virtual const char* what() const noexcept override { return reason_.c_str(); }
    
private:
    const std::string reason_;
};
    
}}

#endif	/* RS_LIBSTRINGINTERN_STRING_INTERN_EXCEPTION_H */

