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
    struct {
        std::vector<Position> segments; // positions of the body segments
        Direction direction;
    } body;
    float move_timer_s = 0;
    float move_interval_s = 0.2; //TODO: maybe this should be initialized in a more clear way?

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