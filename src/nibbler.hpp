#pragma once
#ifndef NIBBLER
#define NIBBLER

#include <memory>

namespace nibbler {

class Nibbler {
public:
    Nibbler();
    int run();

private:
    std::unique_ptr<Nibbler> nibbler_instance_ = nullptr;
};

}

#endif