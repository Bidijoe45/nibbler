#pragma once
#ifndef NIBBLER
#define NIBBLER

#include "config.hpp"
#include "dynamic_lib.hpp"

#include <memory>

namespace nibbler {

class Nibbler {
public:
    Nibbler();
    Nibbler(Configuration config);
    Nibbler(const Nibbler &other);
    Nibbler &operator=(const Nibbler &other);
    ~Nibbler();

    int start();

private:
    Configuration config_;
};

}

#endif