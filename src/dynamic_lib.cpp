#include "dynamic_lib.hpp"

#include <memory>
#include <dlfcn.h>
#include <iostream>

namespace nibbler {

DynamicLib::DynamicLib() : path_(""), handle_(nullptr) {}

DynamicLib::DynamicLib(const std::string path, void *handle) : path_(path), handle_(handle) {}

DynamicLib::DynamicLib(const DynamicLib &other) : path_(other.path_), handle_(other.handle_) {}

DynamicLib &DynamicLib::operator=(const DynamicLib &other)
{
    if (&other != this)
    {
        this->path_ = other.path_;
        this->handle_ = other.handle_;
    }
    return *this;
}

DynamicLib::~DynamicLib() {
    if (this->handle_)
        dlclose(this->handle_);
}

void* DynamicLib::get_symbol(const std::string &symbol_name) {
    if (!this->handle_)
        return nullptr;

    void* symbol = dlsym(this->handle_, symbol_name.c_str());
    if (symbol == nullptr) std::cerr << "ERROR: " <<  dlerror() << std::endl;
    return symbol;
}

std::unique_ptr<DynamicLib> DynamicLibLoader::load_library(const std::string path, const int flags) {
    void* handle = dlopen(path.c_str(), flags);
    if (handle == nullptr) {
        std::cerr << "ERROR: " <<  dlerror() << std::endl;
        return nullptr;
    }
    return std::make_unique<DynamicLib>(path, handle);
}

}