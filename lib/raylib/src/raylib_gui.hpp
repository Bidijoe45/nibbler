#pragma once
#ifndef RAYLIB_GUI_HPP
#define RAYLIB_GUI_HPP

#include "nibbler/graphics_api.hpp"

#include "raylib.h"

namespace raylibgui {

class RaylibGUIWindow : public nibbler::IWindow {
public:
    RaylibGUIWindow();
    
    RaylibGUIWindow(
        int32_t resolution_width_px,
        int32_t resolution_height_px,
        int32_t gameboard_width_squares,
        int32_t gameboard_height_squares,
        std::string title);

    RaylibGUIWindow(const RaylibGUIWindow &other) = delete;
    RaylibGUIWindow &operator=(const RaylibGUIWindow &other) = delete;
    ~RaylibGUIWindow();

    void add_event_listener_key_down(nibbler::IWindow::KeyDownCallback cb) override;
    void add_event_listener_key_up(nibbler::IWindow::KeyUpCallback cb) override;
    void add_event_listener_key_press(nibbler::IWindow::KeyPressCallback cb) override;
    void clear_screen() override;
    void read_input() override;
    void draw_snake(const std::vector<nibbler::Position> &snake) override;
    void draw_fruit(const nibbler::Position& fruit_pos) override;
    void push_message(const std::string& msg) override;
    void set_score(int32_t score) override;
    void render() override;

private:
    void init(int32_t resolution_width_px, int32_t resolution_height_px);
    const std::pair<int, int> get_window_size() const;
    void draw_border();

    std::vector<nibbler::IWindow::KeyDownCallback> key_down_callbacks_;
    int32_t score_;
    std::vector<nibbler::Position> snake_;
    nibbler::Position fruit_;
    Camera3D camera_;
    int32_t gameboard_width_squares_;
    int32_t gameboard_height_squares_;
    std::string title_;
};

class RaylibGUI : public nibbler::INibblerGraphicsApi {
    public:
        RaylibGUI();
        ~RaylibGUI();

    std::unique_ptr<nibbler::IWindow> create_window(
        int32_t resolution_width_px,
        int32_t resolution_height_px,
        int32_t gameboard_width_squares,
        int32_t gameboard_height_squares,
        std::string font_path,
        std::string title) override;
};

}

extern "C" {

nibbler::INibblerGraphicsApi* create_graphics_library();
void destroy_graphics_library(nibbler::INibblerGraphicsApi*);

}

#endif
