#include "snake.hpp"
#include "nibbler/graphics_api.hpp"

#include <iostream>

namespace nibbler {

Snake::Snake() {}

Snake::Snake(const Position &start_pos)
{
    this->body.segments.push_back(start_pos);
    this->body.segments.push_back({start_pos.x - 1, start_pos.y});
    this->body.segments.push_back({start_pos.x - 2, start_pos.y});
    this->body.segments.push_back({start_pos.x - 3, start_pos.y});
    this->body.direction = Direction::RIGHT;
}

Snake::Snake(const Snake &other)
    : body(other.body),
      move_timer_s(other.move_timer_s),
      move_interval_s(other.move_interval_s),
      last_tail_segment(other.last_tail_segment)
{}

Snake &Snake::operator=(const Snake &other)
{
    if (this != &other)
    {
        this->body = other.body;
        this->move_timer_s = other.move_timer_s;
        this->move_interval_s = other.move_interval_s;
        this->last_tail_segment = other.last_tail_segment;
    }
    return *this;
}

Snake::~Snake() {}

void Snake::add_segment(void)
{
    if (this->body.segments.size() == 0) {
        return;
    }
    this->body.segments.push_back(this->last_tail_segment);
}

void Snake::move(double delta_time) {
    if (this->body.segments.empty())
        return;

    // Store the last position of the last segment of the body, to be used if add_segment() is called:
    this->last_tail_segment = this->body.segments.back();

    this->move_timer_s += delta_time;
    if (this->move_timer_s >= move_interval_s) {
        this->move_timer_s -= move_interval_s;

        // move body from back to front
        for (size_t i = this->body.segments.size() - 1; i > 0; --i) {
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
    Position& snake_head = this->body.segments.front();

    if (snake_head.x == last_pos.x && snake_head.y == last_pos.y)
        return;
    this->last_pos = snake_head;

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

bool Snake::check_wall_collision(int32_t gameboard_width, int32_t gameboard_height) {
    Position& snake_head = this->body.segments[0];

    if (snake_head.x < 0) return true;
    else if (snake_head.y < 0) return true;
    else if (snake_head.x >= gameboard_width) return true;
    else if (snake_head.y >= gameboard_height) return true;

    return false;
}

bool Snake::check_fruit_collision(Position fruit_pos) {
    Position& snake_head = this->body.segments[0];

    if (snake_head.x == fruit_pos.x && snake_head.y == fruit_pos.y)
        return true;

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

void Snake::increase_speed()
{
    if (this->move_interval_s > 0.01)
        this->move_interval_s -= 0.01;
}

}
