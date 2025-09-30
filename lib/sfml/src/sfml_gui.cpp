#include "nibbler/graphics_api.hpp"
#include "sfml_gui.hpp"

#include <iostream>
#include <SFML/Window.hpp>

namespace sfmlgui {

SFMLGUIWindow::SFMLGUIWindow(size_t width_squares, size_t height_squares, std::string title)
    : nibbler::IWindow(width_squares, height_squares, std::move(title)),
      square_size_px_(20),
      border_size_px_(square_size_px_)
{
    this->window.create(
        sf::VideoMode({
            static_cast<unsigned int>(square_size_px_ * width_squares),
            static_cast<unsigned int>(square_size_px_ * height_squares)}),
        title,
        sf::Style::Close | sf::Style::Titlebar,
        sf::State::Windowed);
}

SFMLGUIWindow::~SFMLGUIWindow()
{
}

void SFMLGUIWindow::add_event_listener_key_down(KeyDownCallback callback)
{
    this->key_down_callbacks_.push_back(callback);
}

void SFMLGUIWindow::add_event_listener_key_up(KeyUpCallback callback)
{
    //TODO:
}

void SFMLGUIWindow::add_event_listener_key_press(KeyPressCallback callback)
{
    //TODO:
}

void SFMLGUIWindow::clear_screen()
{

}

void SFMLGUIWindow::read_input()
{
}

void SFMLGUIWindow::draw_snake(const std::vector<nibbler::Position> &snake)
{

}

void SFMLGUIWindow::draw_fruit(const nibbler::Position& fruit_pos)
{

}

void SFMLGUIWindow::set_score(int score)
{

}

void SFMLGUIWindow::render()
{

}

void SFMLGUIWindow::push_message(const std::string &msg)
{

}



SFMLGUI::SFMLGUI() {}
SFMLGUI::~SFMLGUI() {}

std::unique_ptr<nibbler::IWindow> SFMLGUI::create_window(std::size_t width_squares, std::size_t height_squares, std::string title)
{
    return std::make_unique<SFMLGUIWindow>(width_squares, height_squares, std::move(title));
}

} // namespace sfmlgui

extern "C" {

nibbler::INibblerGraphicsApi* create_graphics_library() {
    return new sfmlgui::SFMLGUI();
}

void destroy_graphics_library(nibbler::INibblerGraphicsApi* lib) {
    delete lib;
}

}
