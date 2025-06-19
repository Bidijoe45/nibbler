#include <memory>

#include "nibbler.hpp"

namespace nibbler {

Nibbler::Nibbler() : nibbler_instance_(this) { }

int Nibbler::run() {
    return 0;
}

}