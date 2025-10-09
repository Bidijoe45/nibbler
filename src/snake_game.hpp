#pragma once
#ifndef NIBBLER_SNAKE_GAME
#define NIBBLER_SNAKE_GAME

#include "nibbler/graphics_api.hpp"
#include "snake.hpp"
#include "config.hpp"
#include "fruit.hpp"

#include <map>

namespace nibbler {

enum GameState {
    INIT,
    RUNNING,
    END
};

class SnakeGame {

public:
    SnakeGame(
        Configuration config,
        const std::map<Key, GraphicsApiSharedPtr> &graphics_apis,
        const std::map<Key, ConfigLibrary> &graphics_apis_configs
    );

    ~SnakeGame();

    void on_key_down(Key key);
    void update(double delta_time);
    int run();

private:
    void initialize_game();
    void switch_gui();

    Configuration config_;
    std::map<Key, GraphicsApiSharedPtr> graphics_apis_;
    std::map<Key, ConfigLibrary> graphics_apis_configs_;
    std::unique_ptr<IWindow> window_;
    Key current_gui_;

    GameState game_state_;
    size_t score_ = 0;
    Snake snake_;
    Fruit fruit_;
    FruitFactory fruit_factory_;

};

}

#endif