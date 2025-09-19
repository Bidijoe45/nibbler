#include "tty_gui.hpp"
#include "nibbler/graphics_api.hpp"

#include <iostream>
#include <utility>
#include <unistd.h>
#include <sys/ioctl.h>
#include <csignal>
#include <fcntl.h>
#include <poll.h>

namespace ttygui {

int TTYGUIWindow::term_cols = 0;
int TTYGUIWindow::term_rows = 0;
termios TTYGUIWindow::orig_termios;
int TTYGUIWindow::score_rows = 1;
int TTYGUIWindow::messages_rows = 3;

TTYGUIWindow::TTYGUIWindow(std::size_t width_squares, std::size_t height_squares, std::string title)
    : nibbler::IWindow(width_squares, height_squares, std::move(title))
{
    std::atexit(TTYGUIWindow::restore_terminal);
    std::signal(SIGWINCH, TTYGUIWindow::handle_resize);
    std::signal(SIGINT, TTYGUIWindow::handle_exit);

    this->set_noncanonical_mode();
    //TTYGUIWindow::update_terminal_size();
    TTYGUIWindow::term_cols = width_squares;
    TTYGUIWindow::term_rows = height_squares;

    draw_border();
}

TTYGUIWindow::~TTYGUIWindow() {
    this->set_non_blocking(false);
    this->restore_terminal();
};

void TTYGUIWindow::add_event_listener_key_down(nibbler::IWindow::KeyDownCallback callback) {
    this->key_down_callbacks_.push_back(callback);
}

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

void TTYGUIWindow::set_non_blocking(bool enable) {
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    if (enable)
        fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
    else
        fcntl(STDIN_FILENO, F_SETFL, flags & ~O_NONBLOCK);
}

void TTYGUIWindow::draw_border() {
    const int width = TTYGUIWindow::term_cols + 2; // +2 to take into account borders
    const int height = TTYGUIWindow::term_rows + 2;

    std::cout << "\033[2J";
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (y == 0 || y == height - 1 || x == 0 || x == width - 1) {
                std::cout << "\033[" << y + 1 << ";" << x + 1 << "H#";
            }
        }
    }
    std::cout << "\033[1;1H";
    std::cout.flush(); // TODO: maybe this should not be flushed on every draw, instead flushed once when everything is draw
}


void TTYGUIWindow::draw_score() {
    const int draw_start = TTYGUIWindow::term_rows + TTYGUIWindow::score_rows + 2; // +2 to take into account borders 
    std::cout << "\033[" << draw_start << ";1H";
    std::cout << "Score: " << this->score_;
    std::cout << "\033[1;1H";
    std::cout.flush();  // TODO: maybe this should not be flushed on every draw, instead flushed once when everything is draw
}

// Maybe not the best implementation. Text should go from bottom to top.
// If there are more messages than messages rows it goes crazy
// At least we have a small debug. "It ain't much but i'ts honest work" :)
void TTYGUIWindow::draw_messages() {
    int draw_start = TTYGUIWindow::term_rows + TTYGUIWindow::score_rows + 1 + 2; // +2 to take into account borders ;

    if (this->messages_.empty())
        return;

    for (int i=0; i < TTYGUIWindow::messages_rows; i++) {
        if (this->messages_.empty())
            break;
        std::cout << "\033[" << draw_start << ";1H";
        const std::string& msg = this->messages_.front();
        std::cout << ">: " << msg;
        this->messages_.pop_front();
        draw_start += 1;
    }
    
    std::cout << "\033[1;1H";
    std::cout.flush();  // TODO: maybe this should not be flushed on every draw, instead flushed once when everything is draw
}

void TTYGUIWindow::push_message(const std::string& msg) {
    this->messages_.push_back(msg);
}

void TTYGUIWindow::set_score(int score) {
    this->score_ = score;
}

void TTYGUIWindow::restore_terminal() {
    tcsetattr(STDIN_FILENO, TCSANOW, &TTYGUIWindow::orig_termios);
    std::cout << "\033[?25h";
}

void TTYGUIWindow::handle_resize(int) {
    //TTYGUIWindow::update_terminal_size();
    TTYGUIWindow::draw_border();
}

//TODO: Don't know if this is really needed
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
    //TTYGUIWindow::update_terminal_size();
    TTYGUIWindow::draw_border();
    TTYGUIWindow::draw_score();
    TTYGUIWindow::draw_messages();
}

void TTYGUIWindow::draw_pixel(size_t x, size_t y, char c) {
    //Take into account window borders
    x += 1; y += 1;

    std::cout << "\033[" << y << ";" << x << "H" << c;
    std::cout.flush();
}

std::pair<size_t, size_t> TTYGUIWindow::get_window_size_squares() {
    //TTYGUIWindow::update_terminal_size();
    return std::make_pair<size_t, size_t>(TTYGUIWindow::term_cols, TTYGUIWindow::term_rows);
}

void TTYGUIWindow::draw_snake(std::vector<nibbler::Position> &snake) {
    for (auto &pos : snake) {
        this->draw_pixel(pos.x, pos.y, 'X');
    }
}

void TTYGUIWindow::draw_fruit(nibbler::Position& fruit_pos) {
    this->draw_pixel(fruit_pos.x, fruit_pos.y, '0');
}

nibbler::Key TTYGUIWindow::convert_input_to_key(char ch) {
    switch (ch)
    {
        case '1':
            return nibbler::Key::NUMBER_1;
            break;

        case '2':
            return nibbler::Key::NUMBER_2;
            break;

        case 7:
            return nibbler::Key::ESC;
            break;

        default:
            break;
    }

    return nibbler::Key::EMPTY;
}

void TTYGUIWindow::read_input() {
    struct pollfd pfd;
    pfd.fd = STDIN_FILENO;
    pfd.events = POLLIN;

    int ret = poll(&pfd, 1, 0);
    if (ret <= 0) return;

    char ch;
    if (read(STDIN_FILENO, &ch, 1) <= 0) return;

    for (auto& callback : this->key_down_callbacks_) {
        if (ch == 27) {  // ESC or sequence
            // This is needed bc when you press ESC it waits for another character.
            // arrow key sequence start with the same characer as ESC
            int seq_ret = poll(&pfd, 1, 10); 

            if (seq_ret > 0) {
                char seq[2];
                if (read(STDIN_FILENO, &seq[0], 1) <= 0) return;
                if (read(STDIN_FILENO, &seq[1], 1) <= 0) return;
                if (seq[0] == '[') {
                    switch (seq[1]) {
                        case 'A': callback(nibbler::Key::ARROW_UP); break;
                        case 'B': callback(nibbler::Key::ARROW_DOWN); break;
                        case 'C': callback(nibbler::Key::ARROW_RIGHT); break;
                        case 'D': callback(nibbler::Key::ARROW_LEFT); break;
                        default: break;
                    }
                }
            } else {
                callback(nibbler::Key::ESC);
            }
        } else {
            callback(this->convert_input_to_key(ch));
        }
    }
}

TTYGUI::TTYGUI() {}
TTYGUI::~TTYGUI() {}

std::shared_ptr<nibbler::IWindow>
TTYGUI::create_window(std::size_t width_squares, std::size_t height_squares, std::string title) {
    return std::make_shared<TTYGUIWindow>(width_squares, height_squares, std::move(title));
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
