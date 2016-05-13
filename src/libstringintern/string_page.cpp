#include "string_page.h"

rs::stringintern::StringPage::StringPage(uint32_t pageSize, uint32_t entrySize)
    : pageSize_(pageSize), entrySize_(entrySize) {
    
}

uint32_t rs::stringintern::StringPage::EntrySize() {
    return entrySize_;
}

uint32_t rs::stringintern::StringPage::EntryCount() {
    return pageSize_ / entrySize_;
    
}