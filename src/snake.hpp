#pragma once
#ifndef NIBBLER_SNAKE
#define NIBBLER_SNAKE

#include "nibbler/graphics_api.hpp"

#include <vector>

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
        Direction direction; // direction of the head
    } body;

    Snake();
    Snake(const Position &start_pos);

    void add_segment(void);
    void change_direction(Direction dir);
    void move(double delta_time);
    bool check_wall_collision(size_t gameboard_width, size_t gameboard_height);
    bool check_fruit_collision(Position fruit_pos);
    bool check_body_collision();

    float move_timer_s = 0;
    float move_interval_s = 0.1;
};

}

#endif