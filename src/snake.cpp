#include "snake.hpp"
#include "nibbler/graphics_api.hpp"

#include <iostream>

namespace nibbler {

Snake::Snake(Configuration config, GraphicsApiUniquePtr graphics_api)
    : config_(config), graphics_api(std::move(graphics_api))
{

}

Snake::~Snake() {

}

int Snake::run() {
    std::cout << "running" << std::endl;

    return 0;
}

}