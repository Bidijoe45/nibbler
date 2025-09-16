#pragma once
#ifndef NIBBLER_SNAKE
#define NIBBLER_SNAKE

#include "nibbler/graphics_api.hpp"
#include "config.hpp"

namespace nibbler {

enum Direction {
    LEFT,
    UP,
    DOWN,
    RIGHT
};

struct Snake {
    // Positions and directions are kept in two separate vectors like this
    // instead of e.g. a vector of pairs, in order to be able to pass the
    // vector of positions directly to draw_snake():
    struct {
        std::vector<Position> segments; // positions of the body
        std::vector<Direction> directions; // each segment has its own direction
    } body;
    float speed;

    void add_segment(void);
    void change_direction(Direction dir);
    void move(double delta_time);
};

class SnakeGame {
public:
    SnakeGame(Configuration config, GraphicsApiUniquePtr graphics_api);
    ~SnakeGame();
    void on_key_down(Key key);
    void update(std::shared_ptr<IWindow> window, double delta_time);
    int run();

private:
    void initialize_game(std::shared_ptr<IWindow> window);

    Configuration config_;
    GraphicsApiUniquePtr graphics_api_;

    Snake snake_;
};

}

#endif