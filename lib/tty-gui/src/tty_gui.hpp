#pragma once
#ifndef TTY_GUI_HPP
#define TTY_GUI_HPP

#include "nibbler/graphics_api.hpp"

#include <cstddef>
#include <string>
#include <memory>
#include <termios.h>
#include <deque>

namespace ttygui {

class TTYGUIWindow : public nibbler::IWindow {
public:
    TTYGUIWindow(std::size_t resolution_width, std::size_t resolution_height, std::size_t min_resolution, std::size_t width_squares, std::size_t height_squares, std::string title);
    ~TTYGUIWindow();

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
    static void restore_terminal();
    static void handle_resize(int);
    static void handle_exit(int);
    static void update_terminal_size();
    void draw_border();
    static int term_cols;
    static int term_rows;
    static termios orig_termios;

    void set_noncanonical_mode();
    void set_non_blocking(bool enable);
    nibbler::Key convert_input_to_key(char ch);
    void draw_pixel(size_t x, size_t y, char c);
    void draw_score();
    void draw_messages();

    static int score_rows; // Space for the score line
    static int messages_rows; // Space for the messages
    std::vector<nibbler::IWindow::KeyDownCallback> key_down_callbacks_;
    int score_;
    std::deque<std::string> messages_;
};

class TTYGUI : public nibbler::INibblerGraphicsApi {
public:
    TTYGUI();
    ~TTYGUI();

    std::unique_ptr<nibbler::IWindow>
    create_window(std::size_t resolution_width, std::size_t resolution_height, size_t min_resolution, std::size_t width_squares, std::size_t height_squares, std::string font_path, std::string title) override;
};

} 

extern "C" {

nibbler::INibblerGraphicsApi* create_graphics_library();
void destroy_graphics_library(nibbler::INibblerGraphicsApi*);

}

#endif