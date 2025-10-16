#pragma once
#ifndef SDL_GUI_HPP
#define SDL_GUI_HPP

#include "nibbler/graphics_api.hpp"

#include <SDL3/SDL.h>

namespace sdlgui {

class SDLGUIWindow : public nibbler::IWindow {
public:
    SDLGUIWindow(
        int32_t resolution_width_px,
        int32_t resolution_height_px,
        int32_t min_resolution_px,
        int32_t gameboard_width_squares,
        int32_t gameboard_height_squares,
        std::string title
    );
    ~SDLGUIWindow();

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
    std::pair<int, int> get_window_size();
    void draw_border();

    SDL_Window* window_;
    SDL_Renderer* renderer_;
    std::vector<nibbler::IWindow::KeyDownCallback> key_down_callbacks_;

    const int32_t min_resolution_px_ = 0;
    const int32_t gameboard_width_squares_ = 0;
    const int32_t gameboard_height_squares_ = 0;
    int32_t square_size_px_;
    int32_t padding_x_;
    int32_t padding_y_;
};

class SDLGUI : public nibbler::INibblerGraphicsApi {
    public:
        SDLGUI();
        ~SDLGUI();

    std::unique_ptr<nibbler::IWindow> create_window(
        int32_t resolution_width_px,
        int32_t resolution_height_px,
        int32_t min_resolution_px,
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