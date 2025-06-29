#include "snake.hpp"
#include "nibbler/graphics_api.hpp"

#include <iostream>
#include <chrono>
#include <thread>
#include <functional>

namespace nibbler {

Snake::Snake(Configuration config, GraphicsApiUniquePtr graphics_api)
    : config_(config), graphics_api(std::move(graphics_api)) { }

Snake::~Snake() { }

void Snake::on_key_down(KEY key) {

}

// This function is called 59.9 times per second. Game logic goes here
void Snake::update(std::shared_ptr<IWindow> window, std::chrono::duration<double> delta_time) {
    window->clear_screen();
    window->draw_pixel(10, 10);
}

int Snake::run() {
    std::shared_ptr<IWindow> window = graphics_api->create_window(
        this->config_.window_width,
        this->config_.window_width, 
        "Nibbler"
    );

    window->add_event_listener_key_down(std::bind(&Snake::on_key_down, this, std::placeholders::_1));

    size_t target_frame_rate = 60;
    std::chrono::duration<double> target_frame_duration = std::chrono::duration<double>(1.0 / target_frame_rate);
    std::chrono::steady_clock::time_point previous_time = std::chrono::steady_clock::now();
    std::chrono::duration<double> delta_time;
    const std::chrono::milliseconds sleep_margin(3);

    while (true) {
        std::chrono::steady_clock::time_point frame_start = std::chrono::steady_clock::now();
        delta_time = frame_start - previous_time;
        previous_time = frame_start;

        this->update(window, delta_time);

        std::chrono::steady_clock::time_point frame_end = std::chrono::steady_clock::now();
        std::chrono::duration<double> work_duration = frame_end - frame_start;
        std::chrono::duration<double> time_remaining = target_frame_duration - work_duration;

        if (time_remaining > sleep_margin) {
            std::this_thread::sleep_for(std::chrono::duration_cast<std::chrono::milliseconds>(time_remaining - sleep_margin));
        }

        while (std::chrono::steady_clock::now() - frame_start < target_frame_duration) {
            std::this_thread::yield();
        }
    }

    return 0;
}

}