#pragma once
#ifndef NIBBLER_SNAKE_GAME
#define NIBBLER_SNAKE_GAME

#include "nibbler/graphics_api.hpp"
#include "snake.hpp"
#include "config.hpp"

namespace nibbler {


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