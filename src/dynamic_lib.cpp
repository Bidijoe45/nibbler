#include "dynamic_lib.hpp"

#include <memory>
#include <dlfcn.h>
#include <iostream>

namespace nibbler {

DynamicLib::DynamicLib(const std::string path, void *handle) : path(path), handle_(handle) { }

DynamicLib::~DynamicLib() {
    dlclose(this->handle_);
}

void* DynamicLib::get_symbol(const std::string &symbol_name) {
    void* symbol = dlsym(this->handle_, symbol_name.c_str());
    if (symbol == NULL) std::cerr << "ERROR: " <<  dlerror() << std::endl;
    return symbol;
}

std::unique_ptr<DynamicLib> DynamicLibLoader::load_library(const std::string path, const int flags) {
    void* handle = dlopen(path.c_str(), flags);
    if (handle == NULL) std::cerr << "ERROR: " <<  dlerror() << std::endl;
    return std::make_unique<DynamicLib>(path, handle);
}

}