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
    void draw_pixel(size_t x, size_t y);
    void clear_screen();

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