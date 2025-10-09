#pragma once
#ifndef SFML_GUI_HPP
#define SFML_GUI_HPP

#include "nibbler/graphics_api.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace sfmlgui {

class SFMLGUIWindow : public nibbler::IWindow {
    public:
        SFMLGUIWindow(std::size_t resolution_width, std::size_t resolution_height, std::size_t width_squares, std::size_t height_squares, std::string title);
        ~SFMLGUIWindow();

        void add_event_listener_key_down(KeyDownCallback cb) override;
        void add_event_listener_key_up(KeyUpCallback cb) override;
        void add_event_listener_key_press(KeyPressCallback cb) override;
        void clear_screen() override;
        void read_input() override;
        void draw_snake(const std::vector<nibbler::Position> &snake) override;
        void draw_fruit(const nibbler::Position& fruit_pos) override;
        void set_score(int score) override;
        void render() override;
        void push_message(const std::string &msg) override;

    private:
        sf::RenderWindow window_;
        std::vector<nibbler::IWindow::KeyDownCallback> key_down_callbacks_;
        const int square_size_px_;
        const int border_size_px_;
};

class SFMLGUI : public nibbler::INibblerGraphicsApi {
    public:
        SFMLGUI();
        ~SFMLGUI();
        std::unique_ptr<nibbler::IWindow> create_window(std::size_t resolution_width, std::size_t resolution_height, std::size_t width_squares, std::size_t height_squares, std::string title) override;
};

}

extern "C" {
    nibbler::INibblerGraphicsApi* create_graphics_library();
    void destroy_graphics_library(nibbler::INibblerGraphicsApi* lib);
}

#endif
