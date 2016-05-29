#include <cstdlib>
#include <cstring>

#include "string_intern.h"

#include "string_page.h"

using namespace std;

int main() {
    
    const auto pageSize = 2 * 1024 * 1024;
    const auto pageEntries = 256;

    rs::stringintern::StringPage page(pageSize, pageEntries);
    
    const char* str = "Hello world";
    const auto len = std::strlen(str);
    page.Add(str, len, 11234);
    page.Add(str, len, 11234);
    page.Add(str, len, 11234 + (pageSize / pageEntries));
}
