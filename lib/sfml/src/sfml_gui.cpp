#include "sfml_gui.hpp"
#include "nibbler/graphics_api.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

namespace sfmlgui {

SFMLGUIWindow::SFMLGUIWindow(int32_t resolution_width_px,
    int32_t resolution_height_px,
    int32_t min_resolution_px,
    int32_t gameboard_width_squares,
    int32_t gameboard_height_squares,
    std::string font_path,
    std::string title)
    : min_resolution_px_(min_resolution_px), gameboard_width_squares_(gameboard_width_squares), gameboard_height_squares_(gameboard_height_squares)
{
    this->square_width_px_ = static_cast<float>(resolution_width_px) / this->gameboard_width_squares_;
    this->square_height_px_ = static_cast<float>(resolution_height_px) / this->gameboard_height_squares_;

    if (!this->font_.openFromFile(font_path))
        throw std::runtime_error("Failed to load font from " + font_path);

    this->window_.create(
        sf::VideoMode({
            static_cast<unsigned int>(resolution_width_px),
            static_cast<unsigned int>(resolution_height_px)}),
        title,
        sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize,
        sf::State::Windowed);

    if (!this->window_.isOpen())
        throw std::runtime_error("Failed to open SFML window.");

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
    this->window_.clear(sf::Color(250, 150, 100));
}

void SFMLGUIWindow::read_input()
{
    while (const std::optional event = this->window_.pollEvent())
    {
        if (const auto *resized = event->getIf<sf::Event::Resized>())
        {
            sf::Vector2u res = this->window_.getSize();
            if (res.x < this->min_resolution_px_)
                res.x = this->min_resolution_px_;
            if (res.y < this->min_resolution_px_)
                res.y = this->min_resolution_px_;
            this->window_.setSize(res);

            // Reset GUI view to avoid default stretching
            sf::FloatRect visibleArea({0.f, 0.f}, {static_cast<float>(res.x), static_cast<float>(res.y)});
            this->window_.setView(sf::View(visibleArea));
            // Update square size
            this->square_width_px_ = static_cast<float>(res.x) / this->gameboard_width_squares_;
            this->square_height_px_ = static_cast<float>(res.y) / this->gameboard_height_squares_;
        }
        for (auto &callback : this->key_down_callbacks_)
        {
            if (event->is<sf::Event::Closed>())
            {
                callback(nibbler::Key::ESC);
            }
            else if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
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
    for (const nibbler::Position &p : snake)
    {
        sf::RectangleShape square({
            this->square_width_px_,
            this->square_height_px_});
        square.setFillColor(sf::Color(150, 50, 250));
        square.setPosition({p.x * this->square_width_px_,
                            p.y * this->square_height_px_});
        square.setOutlineThickness(0.f);
        this->window_.draw(square);
    }
}

void SFMLGUIWindow::draw_fruit(const nibbler::Position& fruit_pos)
{
    sf::RectangleShape fruit({
            this->square_width_px_,
            this->square_height_px_});
    fruit.setFillColor(sf::Color(188, 71, 73));
    fruit.setPosition({fruit_pos.x * this->square_width_px_,
                        fruit_pos.y * this->square_height_px_});
    fruit.setOutlineThickness(0.f);
    this->window_.draw(fruit);
}

void SFMLGUIWindow::set_score(int32_t score)
{
    sf::Text score_text(this->font_);
    score_text.setString("Score: " + std::to_string(score));
    score_text.setCharacterSize(std::max(this->window_.getSize().x / 25, this->window_.getSize().y / 25));
    score_text.setFillColor(sf::Color::Black);
    this->window_.draw(score_text);
}

void SFMLGUIWindow::render()
{
    this->window_.display();
}

void SFMLGUIWindow::push_message(const std::string &msg)
{
    // TODO:
}

SFMLGUI::SFMLGUI() {}
SFMLGUI::~SFMLGUI() {}

std::unique_ptr<nibbler::IWindow> SFMLGUI::create_window(
    int32_t resolution_width_px,
    int32_t resolution_height_px,
    int32_t min_resolution_px,
    int32_t gameboard_width_squares,
    int32_t gameboard_height_squares,
    std::string font_path,
    std::string title)
{
    try
    {
        return std::make_unique<SFMLGUIWindow>(
            resolution_width_px,
            resolution_height_px,
            min_resolution_px,
            gameboard_width_squares,
            gameboard_height_squares,
            font_path,
            std::move(title));
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return nullptr;
    }
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
