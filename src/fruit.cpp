#include "fruit.hpp"

namespace nibbler {

FruitFactory::FruitFactory(std::size_t width_squares, std::size_t height_squares)
    : width_squares_(width_squares), height_squares_(height_squares)
{
    this->gen = std::mt19937(this->rd());
    this->distribution_w = std::uniform_int_distribution<>(0, width_squares_ - 1);
    this->distribution_h = std::uniform_int_distribution<>(0, height_squares_ - 1);
}

Fruit FruitFactory::create_fruit_random_pos() {
    Fruit f;

    //FIXME: There is a chance to generate the behind the snake body. Something better is needed
    f.pos.x = distribution_w(this->gen);
    f.pos.y = distribution_h(this->gen);

    return f;
}

}