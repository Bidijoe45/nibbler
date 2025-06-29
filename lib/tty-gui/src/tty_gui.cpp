#include "tty_gui.hpp"
#include "nibbler/graphics_api.hpp"

#include <iostream>
#include <utility>
#include <unistd.h>
#include <sys/ioctl.h>
#include <csignal>

namespace ttygui {

int TTYGUIWindow::term_cols = 0;
int TTYGUIWindow::term_rows = 0;
termios TTYGUIWindow::orig_termios;

TTYGUIWindow::TTYGUIWindow(std::size_t width, std::size_t height, std::string title)
    : nibbler::IWindow(width, height, std::move(title))
{
    std::atexit(TTYGUIWindow::restore_terminal);
    std::signal(SIGWINCH, TTYGUIWindow::handle_resize);
    std::signal(SIGINT, TTYGUIWindow::handle_exit);

    set_noncanonical_mode();
    draw_border();
}

TTYGUIWindow::~TTYGUIWindow() {};

void TTYGUIWindow::add_event_listener_key_down(nibbler::IWindow::KeyDownCallback) {}
void TTYGUIWindow::add_event_listener_key_up(nibbler::IWindow::KeyUpCallback) {}
void TTYGUIWindow::add_event_listener_key_press(nibbler::IWindow::KeyPressCallback) {}

void TTYGUIWindow::set_noncanonical_mode() {
    tcgetattr(STDIN_FILENO, &TTYGUIWindow::orig_termios);
    termios raw = TTYGUIWindow::orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    raw.c_cc[VMIN] = 1;
    raw.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
    std::cout << "\033[?25l";
}

void TTYGUIWindow::draw_border() {
    std::cout << "\033[2J";
    for (int y = 0; y < TTYGUIWindow::term_rows; ++y) {
        for (int x = 0; x < TTYGUIWindow::term_cols; ++x) {
            if (y == 0 || y == TTYGUIWindow::term_rows - 1 || x == 0 || x == TTYGUIWindow::term_cols - 1) {
                std::cout << "\033[" << y + 1 << ";" << x + 1 << "H#";
            }
        }
    }
    std::cout << "\033[1;1H";
    std::cout.flush();
}

void TTYGUIWindow::restore_terminal() {
    tcsetattr(STDIN_FILENO, TCSANOW, &TTYGUIWindow::orig_termios);
    std::cout << "\033[?25h";
}

void TTYGUIWindow::handle_resize(int) {
    TTYGUIWindow::update_terminal_size();
    TTYGUIWindow::draw_border();
}

void TTYGUIWindow::handle_exit(int) {
    TTYGUIWindow::restore_terminal();
    std::exit(0);
}

// Get terminal size
void TTYGUIWindow::update_terminal_size() {
    winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    TTYGUIWindow::term_rows = w.ws_row;
    TTYGUIWindow::term_cols = w.ws_col;
}

void TTYGUIWindow::clear_screen() {
    std::cout << "\033[2J"
              << "\033[H";
    std::cout.flush();
    TTYGUIWindow::update_terminal_size();
    TTYGUIWindow::draw_border();
}

void TTYGUIWindow::draw_pixel(size_t x, size_t y) {
    char c = 'X';
    std::cout << "\033[" << y << ";" << x << "H" << c;
    std::cout.flush();
}

TTYGUI::TTYGUI() {}
TTYGUI::~TTYGUI() {}

std::shared_ptr<nibbler::IWindow>
TTYGUI::create_window(std::size_t width, std::size_t height, std::string title) {
    return std::make_shared<TTYGUIWindow>(width, height, std::move(title));
}

}

extern "C" {

nibbler::INibblerGraphicsApi* create_graphics_library() {
    return new ttygui::TTYGUI();
}

void destroy_graphics_library(nibbler::INibblerGraphicsApi* lib) {
    delete lib;
}

}
