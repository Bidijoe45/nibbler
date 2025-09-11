#include "snake.hpp"
#include "nibbler/graphics_api.hpp"

#include <iostream>
#include <chrono>
#include <thread>
#include <functional>

namespace nibbler {

void Snake::move(double delta_time) {
    // Move the rest of the snake's body
    for (std::size_t i = this->body.size() - 1; i > 0; i--)
    {

        //std::cout << i << " from: " << this->body[i].x << ", " << this->body[i].y << " to: " << this->body[i-1].x <<", " << this->body[i-1].y << std::endl; 
        this->body[i] = this->body[i - 1];
    }

    // Move first segment of the snake
    switch (this->dir)
    {
        case Direction::UP:
            this->body[0].y -= this->speed * delta_time;
            break;
        case Direction::LEFT:
            this->body[0].x -= this->speed * delta_time;
            break;
        case Direction::DOWN:
            this->body[0].y += this->speed * delta_time;
            break;
        case Direction::RIGHT:
            this->body[0].x += this->speed * delta_time;
            break;
    }
}

void Snake::change_direction(Direction dir) {
    if (this->dir == dir)
        return;
    
    if (this->dir == Direction::UP && dir == Direction::DOWN)
        return;
    if (this->dir == Direction::DOWN && dir == Direction::UP)
        return;
    if (this->dir == Direction::LEFT && dir == Direction::RIGHT)
        return;
    if (this->dir == Direction::RIGHT && dir == Direction::LEFT)
        return;

    this->dir = dir;
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

    this->snake_.body.push_back(start_pos);
    this->snake_.body.push_back(Position({start_pos.x - 1, start_pos.y}));
    this->snake_.body.push_back(Position({start_pos.x - 2, start_pos.y}));
    this->snake_.body.push_back(Position({start_pos.x - 3, start_pos.y}));
    this->snake_.dir = Direction::RIGHT;
    this->snake_.speed = 3;
}

// This function is called 59.9 times per second. Game logic goes here
void SnakeGame::update(std::shared_ptr<IWindow> window, std::chrono::duration<double> delta_time) {
    //static std::pair<size_t, size_t> last_window_size = std::make_pair(0, 0);
    
    //TODO: if window si rescaled, restart the game
    //if (last_window_size != std::make_pair(0,0)
    //    && last_window_size != window->get_window_size_squares())
    //{
    //    initialize_game(window);
    //}

    //window->clear_screen();
    this->snake_.move(delta_time.count());
    
    //TODO: Check collsions

    //window->draw_snake(this->snake_.body);
}

int SnakeGame::run() {
    //FIXME: this should not return a shared_ptr. The graphics_api does not need the ownership of this.
    std::shared_ptr<IWindow> window = this->graphics_api_->create_window(
        this->config_.gameboard_width_squares,
        this->config_.gameboard_height_squares,
        "Nibbler"
    );

    window->add_event_listener_key_down(std::bind(&SnakeGame::on_key_down, this, std::placeholders::_1));

    size_t target_frames_per_s = 60;
    std::chrono::duration<double> target_frame_duration = std::chrono::duration<double>(1.0 / target_frames_per_s);
    std::chrono::steady_clock::time_point previous_time = std::chrono::steady_clock::now();
    std::chrono::duration<double> delta_time;

    this->initialize_game(window);

    while (true) {
        std::chrono::steady_clock::time_point frame_start = std::chrono::steady_clock::now();
        delta_time = frame_start - previous_time;
        previous_time = frame_start;
        window->read_input();
        this->update(window, delta_time);
        
        while (std::chrono::steady_clock::now() - frame_start < target_frame_duration) {
            std::this_thread::yield();
        }
    }

    return 0;
}

}