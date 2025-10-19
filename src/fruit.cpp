#include "fruit.hpp"

namespace nibbler {

FruitFactory::FruitFactory()
    : width_squares_(0), height_squares_(0) {}

FruitFactory::FruitFactory(std::size_t width_squares, std::size_t height_squares)
    : width_squares_(width_squares), height_squares_(height_squares)
{
    this->gen = std::mt19937(this->rd());
    this->distribution_w = std::uniform_int_distribution<>(0, width_squares_ - 1);
    this->distribution_h = std::uniform_int_distribution<>(0, height_squares_ - 1);
}

FruitFactory::FruitFactory(const FruitFactory &other)
    : gen(other.gen),
      distribution_w(other.distribution_w),
      distribution_h(other.distribution_h),
      width_squares_(other.width_squares_),
      height_squares_(other.height_squares_)
{}

FruitFactory &FruitFactory::operator=(const FruitFactory &other)
{
    if (this != &other)
    {
        this->gen = other.gen;
        this->distribution_w = other.distribution_w;
        this->distribution_h = other.distribution_h;
        this->width_squares_ = other.width_squares_;
        this->height_squares_ = other.height_squares_;
    }
    return *this;
}

FruitFactory::~FruitFactory() {}

Fruit FruitFactory::create_fruit_random_pos() {
    Fruit f;

    f.pos.x = distribution_w(this->gen);
    f.pos.y = distribution_h(this->gen);

    return f;
}

Fruit FruitFactory::create_fruit_random_pos(const std::vector<Position> &snake_body) {
    Fruit f;

    do {
        f = this->create_fruit_random_pos();
    } while (std::find_if(snake_body.begin(), snake_body.end(),
        [&f](const auto &snake_segment){
            return f.pos.x == snake_segment.x && f.pos.y == snake_segment.y;
        }) != snake_body.end());

    return f;
}


}