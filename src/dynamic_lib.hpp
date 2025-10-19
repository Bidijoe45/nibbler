#pragma once
#ifndef NIBBLER_DYNAMIC_LIB
#define NIBBLER_DYNAMIC_LIB

#include <string>
#include <memory>

namespace nibbler {

struct DynamicLib {
    DynamicLib();
    DynamicLib(const std::string path, void *handle);
    DynamicLib(const DynamicLib &other);
    DynamicLib &operator=(const DynamicLib &other);
    ~DynamicLib();

    void* get_symbol(const std::string &symbol_name);
    
private:
    std::string path_;
    void* handle_;
};

class DynamicLibLoader {
public:
    static std::unique_ptr<DynamicLib> load_library(const std::string path, const int flags);
};

}
#endif
