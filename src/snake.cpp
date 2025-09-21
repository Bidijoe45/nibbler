#include "snake.hpp"
#include "nibbler/graphics_api.hpp"

#include <iostream>
#include <chrono>
#include <thread>
#include <functional>

namespace nibbler {

void Snake::add_segment(void)
{
    if (this->body.segments.size() == 0) {
        return;
    }

    const Position &prev_seg_pos = *(this->body.segments.end() - 2);

    if (this->body.segments.size() == 1) {
        this->body.segments.push_back(Position({prev_seg_pos.x - 1, prev_seg_pos.y}));
        return;
    }

    const Position &prev_prev_seg_pos = *(this->body.segments.end() - 1);
    
    int diff_x = prev_prev_seg_pos.x - prev_seg_pos.x;
    int diff_y = prev_prev_seg_pos.y - prev_seg_pos.y;

    this->body.segments.push_back(Position({prev_seg_pos.x - diff_x, prev_seg_pos.y - diff_y}));
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

bool Snake::check_body_collision() {
    Position& snake_head = this->body.segments[0];

    for (auto segment = std::next(this->body.segments.begin()); // skip the head
        segment != this->body.segments.end();
        segment++)
    {
        if (snake_head.x == segment->x && snake_head.y == segment->y)
            return true;
    }

    return false;
}

}