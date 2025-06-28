#pragma once
#ifndef NIBBLER
#define NIBBLER

#include "config.hpp"
#include "dynamic_lib.hpp"

#include <memory>

namespace nibbler {

class Nibbler {
public:
    Nibbler(Configuration config);
    int start();

private:
    Configuration config_;
};

}

#endif