#pragma once
#ifndef NIBBLER_FRUIT
#define NIBBLER_FRUIT

#include "nibbler/graphics_api.hpp"

#include <random>

namespace nibbler {

struct Fruit {
    Position pos;
    int score = 1; //Maybe we will have more fruits in the future?
};

class FruitFactory {
    public:
        FruitFactory(std::size_t width_squares, std::size_t height_squares);
        Fruit create_fruit_random_pos();
        Fruit create_fruit_random_pos(const std::vector<Position> &snake_body); // this overload avoids clash of fruit position with the snake body

    private:
        std::random_device rd;
        std::mt19937 gen;
        std::uniform_int_distribution<> distribution_w;
        std::uniform_int_distribution<> distribution_h;

        std::size_t width_squares_ = 0;
        std::size_t height_squares_ = 0;
};

}

#endif