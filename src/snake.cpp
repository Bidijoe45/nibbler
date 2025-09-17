#include "snake.hpp"
#include "nibbler/graphics_api.hpp"

#include <iostream>
#include <chrono>
#include <thread>
#include <functional>

namespace nibbler {

void Snake::add_segment(void)
{
    const Position &prev_segment_pos = this->body.segments.back();
    // FIXME: add the new tail in the direction of the current tail
    this->body.segments.push_back(Position({prev_segment_pos.x - 1, prev_segment_pos.y}));
}

void Snake::move(double delta_time) {
    if (this->body.segments.empty()) return;

    this->move_timer_s += delta_time;
    if (this->move_timer_s >= move_interval_s) {
        this->move_timer_s -= move_interval_s;

        // move body from back to front
        for (int i = this->body.segments.size() - 1; i > 0; --i) {
            this->body.segments[i] = this->body.segments[i - 1];
        }

        // move head
        switch (this->body.direction) {
            case Direction::UP:
                this->body.segments[0].y -= 1;
                break;
            case Direction::DOWN:
                this->body.segments[0].y += 1;
                break;
            case Direction::LEFT:
                this->body.segments[0].x -= 1;
                break;
            case Direction::RIGHT:
                this->body.segments[0].x += 1;
                break;
        }
    }

}

void Snake::change_direction(Direction dir) {
    if (this->body.direction == dir)
        return;
    
    if (this->body.direction == Direction::UP && dir == Direction::DOWN)
        return;
    if (this->body.direction == Direction::DOWN && dir == Direction::UP)
        return;
    if (this->body.direction == Direction::LEFT && dir == Direction::RIGHT)
        return;
    if (this->body.direction == Direction::RIGHT && dir == Direction::LEFT)
        return;

    this->body.direction = dir;
}

SnakeGame::SnakeGame(Configuration config, GraphicsApiUniquePtr graphics_api)
    : config_(config), graphics_api_(std::move(graphics_api)) { }

SnakeGame::~SnakeGame() { }

void SnakeGame::on_key_down(Key key) {
    switch (key)
    {
        case Key::ARROW_LEFT:
            this->snake_.change_direction(Direction::LEFT);
            break;

        case Key::ARROW_RIGHT:
            this->snake_.change_direction(Direction::RIGHT);
            break;
        
        case Key::ARROW_DOWN:
            this->snake_.change_direction(Direction::DOWN);
            break;

        case Key::ARROW_UP:
            this->snake_.change_direction(Direction::UP);
            break;

        // TODO: add gui-changin keys! Maybe they could be mapped by Key enum (either from config or at a later point) so that they'd be more easily accessible

        default:
            break;
    }
}

void SnakeGame::initialize_game(std::shared_ptr<IWindow> window) {
    std::pair<size_t, size_t> windows_size = window->get_window_size_squares();
    Position start_pos;
    start_pos.x = windows_size.first / 2;
    start_pos.y = windows_size.second / 2;

    this->snake_.body.segments.push_back(start_pos);
    this->snake_.body.direction = Direction::RIGHT;
    this->snake_.add_segment();
    this->snake_.add_segment();
    this->snake_.add_segment();
}

// This function is called 59.9 times per second. Game logic goes here
void SnakeGame::update(std::shared_ptr<IWindow> window, double delta_time) {
    //static std::pair<size_t, size_t> last_window_size = std::make_pair(0, 0);
    
    //TODO: if window si rescaled, restart the game
    //if (last_window_size != std::make_pair(0,0)
    //   && last_window_size != window->get_window_size_squares())
    //{
    //   initialize_game(window);
    //}

    window->clear_screen();
    this->snake_.move(delta_time);

    //TODO: Check collsions

    window->draw_snake(this->snake_.body.segments);
}

int SnakeGame::run() {
    //FIXME: this should not return a shared_ptr. The graphics_api does not need the ownership of this.
    std::shared_ptr<IWindow> window = this->graphics_api_->create_window(
        this->config_.gameboard_width_squares,
        this->config_.gameboard_height_squares,
        "Nibbler"
    );

    window->add_event_listener_key_down(std::bind(&SnakeGame::on_key_down, this, std::placeholders::_1));

    const size_t target_frames_per_s = 60;
    const std::chrono::nanoseconds target_frame_duration(std::chrono::nanoseconds(std::chrono::seconds(1)) / target_frames_per_s);
    std::chrono::steady_clock::time_point previous_time = std::chrono::steady_clock::now();

    this->initialize_game(window);

    while (true) {
        std::chrono::steady_clock::time_point frame_start = std::chrono::steady_clock::now();
        std::chrono::duration<double> delta_time_s = frame_start - previous_time;
        previous_time = frame_start;

        window->read_input();

        this->update(window, delta_time_s.count()); 

        //double fps = 1.0 / delta_time.count();
        //std::cout << "FPS: " << fps << "\n";

        //TODO: maybe in the future add a sleep to reduce the %CPU usage

        while (std::chrono::steady_clock::now() - frame_start < target_frame_duration) {
            std::this_thread::yield();
        }
    }

    return 0;
}

}