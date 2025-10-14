#include "raylib_gui.hpp"

#include "nibbler/graphics_api.hpp"
#include "raylib.h"

#include <iostream>
#include <raymath.h>

namespace raylibgui {

RaylibGUIWindow::RaylibGUIWindow(size_t resolution_width, size_t resolution_height, size_t min_resolution, std::size_t gameboard_width, std::size_t gameboard_height, std::string title)
    : nibbler::IWindow(resolution_width, resolution_height, min_resolution, gameboard_width, gameboard_height, std::move(title)),
      square_size_px_(20), border_size_px(square_size_px_)
{
    this->gameboard_width_ = gameboard_width;
    this->gameboard_height_ = gameboard_height;
    this->camera_.position = (Vector3){ 0.0f, 25.0f, 30.0f };
    this->camera_.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    this->camera_.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    this->camera_.fovy = 60.0f;
    this->camera_.projection = CAMERA_PERSPECTIVE;

    SetTraceLogLevel(LOG_WARNING);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(
        this->resolution_width_,
        this->resolution_height_,
        title.c_str());
    SetWindowMinSize(this->min_resolution_, this->min_resolution_);
    SetWindowFocused();
}

RaylibGUIWindow::~RaylibGUIWindow()
{
    CloseWindow();
}

void RaylibGUIWindow::add_event_listener_key_down(nibbler::IWindow::KeyDownCallback cb) {
    this->key_down_callbacks_.push_back(cb);
}

void RaylibGUIWindow::add_event_listener_key_up(nibbler::IWindow::KeyUpCallback cb) {
    //TODO:
}

void RaylibGUIWindow::add_event_listener_key_press(nibbler::IWindow::KeyPressCallback cb) {
    //TODO:
}

void RaylibGUIWindow::draw_border() {
    // No need to implement border, it's 3D
}

void RaylibGUIWindow::clear_screen() {
    // This is done in the render function. This is how the library works
}

void RaylibGUIWindow::read_input() {
    bool close = WindowShouldClose();

    for (auto& callback : this->key_down_callbacks_) {
        if (close) {
            callback(nibbler::Key::ESC);
            break;
        }
        if (IsKeyDown(KeyboardKey::KEY_SPACE)) callback(nibbler::Key::ESC);
        if (IsKeyDown(KeyboardKey::KEY_ONE)) callback(nibbler::Key::NUMBER_1);
        if (IsKeyDown(KeyboardKey::KEY_TWO)) callback(nibbler::Key::NUMBER_2);
        if (IsKeyDown(KeyboardKey::KEY_THREE)) callback(nibbler::Key::NUMBER_3);
        if (IsKeyDown(KeyboardKey::KEY_FOUR)) callback(nibbler::Key::NUMBER_4);
        if (IsKeyDown(KeyboardKey::KEY_FIVE)) callback(nibbler::Key::NUMBER_5);
        if (IsKeyDown(KeyboardKey::KEY_SIX)) callback(nibbler::Key::NUMBER_6);
        if (IsKeyDown(KeyboardKey::KEY_SEVEN)) callback(nibbler::Key::NUMBER_7);
        if (IsKeyDown(KeyboardKey::KEY_EIGHT)) callback(nibbler::Key::NUMBER_8);
        if (IsKeyDown(KeyboardKey::KEY_NINE)) callback(nibbler::Key::NUMBER_9);
        if (IsKeyDown(KeyboardKey::KEY_ZERO)) callback(nibbler::Key::NUMBER_0);
        if (IsKeyDown(KeyboardKey::KEY_UP)) callback(nibbler::Key::ARROW_UP);
        if (IsKeyDown(KeyboardKey::KEY_LEFT)) callback(nibbler::Key::ARROW_LEFT);
        if (IsKeyDown(KeyboardKey::KEY_DOWN)) callback(nibbler::Key::ARROW_DOWN);
        if (IsKeyDown(KeyboardKey::KEY_RIGHT)) callback(nibbler::Key::ARROW_RIGHT);
    }
}

//FIXME: maybe this should be set_snake or update_snake instead of draw
void RaylibGUIWindow::draw_snake(const std::vector<nibbler::Position> &snake) {
    if (this->snake_.size() != snake.size()) {
        size_t new_elements = snake.size() - this->snake_.size();
        this->snake_.assign(snake.begin(), snake.end());
    }

    auto new_snake_it = snake.begin();
    auto snake_it = this->snake_.begin();

    for (; new_snake_it != snake.end(); ++new_snake_it, ++snake_it) {
        *snake_it = *new_snake_it;
    }
}

void RaylibGUIWindow::draw_fruit(const nibbler::Position& fruit_pos) {
    this->fruit_ = fruit_pos;
}

void RaylibGUIWindow::push_message(const std::string& msg) {
    //TODO:
}

void RaylibGUIWindow::set_score(int score) {
    this->score_ = score;
}

void RaylibGUIWindow::render() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode3D(this->camera_);

    // Grid
    Vector3 gridCellV3 = { 0, 0, 0.0f };
    for (int x=0; x < gameboard_width_; x++) {
        for (int y=0; y < gameboard_height_; y++) {
            gridCellV3.x = x;
            gridCellV3.z = y;

            DrawCube(gridCellV3, 1.0f, 0.0f, 1.0f, GRAY);
            DrawCubeWires(gridCellV3, 1.0f, 0.1f, 1.0f, BLACK);
        }
    }

    const nibbler::Position& head = this->snake_.front();
    Vector3 headV3 = {
        static_cast<float>(head.x),
        0.0f,
        static_cast<float>(head.y)
    };

    this->camera_.target =  Vector3Add(this->camera_.target, Vector3Scale(Vector3Subtract(headV3, this->camera_.target), 0.04f));
    this->camera_.position.x = this->camera_.target.x;
    this->camera_.position.z = this->camera_.target.z + 15;

    for (const nibbler::Position& segment : this->snake_) {
        Vector3 cubePosition = {
            static_cast<float>(segment.x),
            0.5f,
            static_cast<float>(segment.y)
        };
        DrawCube(cubePosition, 1.0f, 1.0f, 1.0f, BLUE);
        DrawCubeWires(cubePosition, 1.0f, 1.0f, 1.0f, SKYBLUE);
    }

    Vector3 fruiPosition = {
        static_cast<float>(this->fruit_.x),
        0.5f,
        static_cast<float>(this->fruit_.y)
    };
    DrawCube(fruiPosition, 1.0f, 1.0f, 1.0f, RED);
    DrawCubeWires(fruiPosition, 1.0f, 1.0f, 1.0f, MAROON);

    EndMode3D();
    DrawText(TextFormat("Score: %i", this->score_), 20, 20, 20, ORANGE);

    EndDrawing();
}

std::pair<int, int> RaylibGUIWindow::get_window_size() {
    return std::make_pair(GetScreenWidth(), GetScreenWidth());
}

RaylibGUI::RaylibGUI() {}
RaylibGUI::~RaylibGUI() {}

std::unique_ptr<nibbler::IWindow>
RaylibGUI::create_window(std::size_t resolution_width, std::size_t resolution_height, std::size_t min_resolution, std::size_t width_squares, std::size_t height_squares, std::string font_path, std::string title) {
    return std::make_unique<RaylibGUIWindow>(resolution_width, resolution_height, min_resolution, width_squares, height_squares, std::move(title));
}

}

extern "C" {

nibbler::INibblerGraphicsApi* create_graphics_library() {
    return new raylibgui::RaylibGUI();
}

void destroy_graphics_library(nibbler::INibblerGraphicsApi* lib) {
    delete lib;
}

}
