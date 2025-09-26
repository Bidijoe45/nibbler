#pragma once
#ifndef SDL_GUI_HPP
#define SDL_GUI_HPP

#include "nibbler/graphics_api.hpp"

#include <SDL3/SDL.h>

namespace sdlgui {

class SDLGUIWindow : public nibbler::IWindow {
public:
    SDLGUIWindow(std::size_t width_squares, std::size_t height_squares, std::string title);
    ~SDLGUIWindow();

    void add_event_listener_key_down(nibbler::IWindow::KeyDownCallback cb) override;
    void add_event_listener_key_up(nibbler::IWindow::KeyUpCallback cb) override;
    void add_event_listener_key_press(nibbler::IWindow::KeyPressCallback cb) override;
    void clear_screen() override;
    void read_input() override;
    void draw_snake(const std::vector<nibbler::Position> &snake) override;
    void draw_fruit(const nibbler::Position& fruit_pos) override;
    void push_message(const std::string& msg) override;
    void set_score(int score) override;
    void render() override;

private:
    std::pair<int, int> get_window_size();
    void draw_border();

    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<nibbler::IWindow::KeyDownCallback> key_down_callbacks_;
    const int square_size_px_;
    const int border_size_px;
};

class SDLGUI : public nibbler::INibblerGraphicsApi {
    public:
        SDLGUI();
        ~SDLGUI();

    std::unique_ptr<nibbler::IWindow>
    create_window(std::size_t width_squares, std::size_t height_squares, std::string title) override;
};

}

extern "C" {

nibbler::INibblerGraphicsApi* create_graphics_library();
void destroy_graphics_library(nibbler::INibblerGraphicsApi*);

}

#endif