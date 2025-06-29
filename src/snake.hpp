#pragma once
#ifndef NIBBLER_SNAKE
#define NIBBLER_SNAKE

#include "nibbler/graphics_api.hpp"
#include "config.hpp"

namespace nibbler {

class Snake {
public:
    Snake(Configuration config, GraphicsApiUniquePtr graphics_api);
    ~Snake();
    void on_key_down(KEY key);
    void update(std::shared_ptr<IWindow> window, std::chrono::duration<double> delta_time);
    int run();

private:
    Configuration config_;
    GraphicsApiUniquePtr graphics_api;
};

}

#endif