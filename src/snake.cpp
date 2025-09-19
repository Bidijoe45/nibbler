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
        Position& snake_head = this->body.segments[0];
        switch (this->body.direction) {
            case Direction::UP:
                snake_head.y -= 1;
                break;
            case Direction::DOWN:
                snake_head.y += 1;
                break;
            case Direction::LEFT:
                snake_head.x -= 1;
                break;
            case Direction::RIGHT:
                snake_head.x += 1;
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

bool Snake::check_wall_collision(size_t gameboard_width, size_t gameboard_height) {
    Position& snake_head = this->body.segments[0];

    if (snake_head.x <= 0) return true;
    else if (snake_head.y <= 0) return true;
    else if (snake_head.x >= gameboard_width) return true;
    else if (snake_head.y >= gameboard_height) return true;

    return false;
}

bool Snake::check_fruit_collision(Position fruit_pos) {
    Position& snake_head = this->body.segments[0];

    if (snake_head.x == fruit_pos.x && snake_head.y == fruit_pos.y) return true;

    return false;
}

}