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
    this->window_.create(
        sf::VideoMode({
            static_cast<unsigned int>(square_size_px_ * width_squares),
            static_cast<unsigned int>(square_size_px_ * height_squares)}),
        title,
        sf::Style::Close | sf::Style::Titlebar,
        sf::State::Windowed);

    this->window_.setKeyRepeatEnabled(false);
}

SFMLGUIWindow::~SFMLGUIWindow()
{
    this->window_.close();
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
    this->window_.clear();
}

void SFMLGUIWindow::read_input()
{
    while (const std::optional event = this->window_.pollEvent())
    {
        for (auto &callback : this->key_down_callbacks_)
        {
            if (event->is<sf::Event::Closed>())
            {
                callback(nibbler::Key::ESC);
            }
            if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                switch (keyPressed->code)
                {
                    case sf::Keyboard::Key::Escape:
                        callback(nibbler::Key::ESC);
                        break;
                    case sf::Keyboard::Key::Num1:
                        callback(nibbler::Key::NUMBER_1);
                        break;
                    case sf::Keyboard::Key::Num2:
                        callback(nibbler::Key::NUMBER_2);
                        break;
                    case sf::Keyboard::Key::Num3:
                        callback(nibbler::Key::NUMBER_3);
                        break;
                    case sf::Keyboard::Key::Num4:
                        callback(nibbler::Key::NUMBER_4);
                        break;
                    case sf::Keyboard::Key::Num5:
                        callback(nibbler::Key::NUMBER_5);
                        break;
                    case sf::Keyboard::Key::Num6:
                        callback(nibbler::Key::NUMBER_6);
                        break;
                    case sf::Keyboard::Key::Num7:
                        callback(nibbler::Key::NUMBER_7);
                        break;
                    case sf::Keyboard::Key::Num8:
                        callback(nibbler::Key::NUMBER_8);
                        break;
                    case sf::Keyboard::Key::Num9:
                        callback(nibbler::Key::NUMBER_9);
                        break;
                    case sf::Keyboard::Key::Num0:
                        callback(nibbler::Key::NUMBER_0);
                        break;
                    case sf::Keyboard::Key::Up:
                        callback(nibbler::Key::ARROW_UP);
                        break;
                    case sf::Keyboard::Key::Down:
                        callback(nibbler::Key::ARROW_DOWN);
                        break;
                    case sf::Keyboard::Key::Left:
                        callback(nibbler::Key::ARROW_LEFT);
                        break;
                    case sf::Keyboard::Key::Right:
                        callback(nibbler::Key::ARROW_RIGHT);
                        break;
                    default: break;
                }
            }
        }
    }
}

void SFMLGUIWindow::draw_snake(const std::vector<nibbler::Position> &snake)
{
    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color(150, 50, 250));
    this->window_.draw(shape);

}

void SFMLGUIWindow::draw_fruit(const nibbler::Position& fruit_pos)
{

}

void SFMLGUIWindow::set_score(int score)
{

}

void SFMLGUIWindow::render()
{
    this->window_.display();
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
