#pragma once
#ifndef TTY_GUI_HPP
#define TTY_GUI_HPP

#include "nibbler/graphics_api.hpp"

#include <cstddef>
#include <string>
#include <memory>
#include <termios.h>

namespace ttygui {

class TTYGUIWindow : public nibbler::IWindow {
public:
    TTYGUIWindow(std::size_t width, std::size_t height, std::string title);
    ~TTYGUIWindow();

    void add_event_listener_key_down(nibbler::IWindow::KeyDownCallback cb);
    void add_event_listener_key_up(nibbler::IWindow::KeyUpCallback cb);
    void add_event_listener_key_press(nibbler::IWindow::KeyPressCallback cb);
    void clear_screen();
    std::pair<size_t, size_t> get_window_size();
    void read_input();
    void draw_snake(std::vector<nibbler::Position> &snake);

    static void restore_terminal();
    static void handle_resize(int);
    static void handle_exit(int);
    static void update_terminal_size();
    static void draw_border();
    static int term_cols;
    static int term_rows;
    static termios orig_termios;

private:
    void set_noncanonical_mode();
    void set_non_blocking(bool enable);
    nibbler::KEY convert_input_to_key(char ch);
    void draw_pixel(size_t x, size_t y, char c);

    std::vector<nibbler::IWindow::KeyDownCallback> key_down_callbacks_;
};

class TTYGUI : public nibbler::INibblerGraphicsApi {
public:
    TTYGUI();
    ~TTYGUI();

    std::shared_ptr<nibbler::IWindow>
    create_window(std::size_t width, std::size_t height, std::string title);
};

} 

extern "C" {

nibbler::INibblerGraphicsApi* create_graphics_library();
void                        destroy_graphics_library(nibbler::INibblerGraphicsApi*);

}

#endif