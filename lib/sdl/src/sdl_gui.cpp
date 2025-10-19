#include "sdl_gui.hpp"
#include "nibbler/graphics_api.hpp"

#include <SDL3/SDL.h>
#include <iostream>

namespace sdlgui {

SDLGUIWindow::SDLGUIWindow()
    : gameboard_width_squares_(default_gameboard_x_squares),
      gameboard_height_squares_(default_gameboard_y_squares),
      title_("No title")
{
    this->init(default_res_x_px, default_res_y_px);
}

SDLGUIWindow::SDLGUIWindow(
    int32_t resolution_width_px,
    int32_t resolution_height_px,
    int32_t gameboard_width_squares,
    int32_t gameboard_height_squares,
    std::string title)
    : gameboard_width_squares_(gameboard_width_squares),
      gameboard_height_squares_(gameboard_height_squares),
      title_(title)
{
    this->init(resolution_width_px, resolution_height_px);
}

SDLGUIWindow::SDLGUIWindow(const SDLGUIWindow &other)
    : gameboard_width_squares_(other.gameboard_width_squares_),
      gameboard_height_squares_(other.gameboard_height_squares_),
      title_(other.title_)
{
    const std::pair<int, int> res = other.get_window_size();
    this->init(res.first, res.second);
    this->key_down_callbacks_ = other.key_down_callbacks_;
}

SDLGUIWindow &SDLGUIWindow::operator=(const SDLGUIWindow &other)
{
    if (this != &other)
    {
        this->gameboard_width_squares_ = other.gameboard_width_squares_;
        this->gameboard_height_squares_ = other.gameboard_height_squares_;
        this->title_ = other.title_;

        const std::pair<int, int> res = other.get_window_size();
        this->init(res.first, res.second);

        this->key_down_callbacks_ = other.key_down_callbacks_;
    }
    return *this;
}

SDLGUIWindow::~SDLGUIWindow()
{
    SDL_DestroyRenderer(this->renderer_);
    SDL_DestroyWindow(this->window_);
    SDL_PumpEvents(); // needed on macOS
    SDL_Quit();
}

void SDLGUIWindow::init(int32_t resolution_width_px, int32_t resolution_height_px)
{
    this->square_size_px_ = std::min((resolution_height_px / this->gameboard_width_squares_), (resolution_height_px / this->gameboard_height_squares_));
    this->padding_x_ = (resolution_width_px - (this->square_size_px_ * this->gameboard_width_squares_)) / 2;
    this->padding_y_ = (resolution_height_px - (this->square_size_px_ * this->gameboard_height_squares_)) / 2;

    if (!SDL_CreateWindowAndRenderer(
        this->title_.c_str(),
        resolution_width_px,
        resolution_height_px,
        SDL_WINDOW_RESIZABLE,
        &this->window_,
        &this->renderer_))
    {
        std::string error_msg = std::string("Failed to create SDL window: ") + std::string(SDL_GetError());
        SDL_Quit();
        throw std::runtime_error(error_msg);
    }
}

void SDLGUIWindow::add_event_listener_key_down(nibbler::IWindow::KeyDownCallback cb) {
    this->key_down_callbacks_.push_back(cb);
}

void SDLGUIWindow::add_event_listener_key_up(nibbler::IWindow::KeyUpCallback cb) {
    //TODO:
}

void SDLGUIWindow::add_event_listener_key_press(nibbler::IWindow::KeyPressCallback cb) {
    //TODO:
}

void SDLGUIWindow::draw_border() {
    std::pair<int, int> window_size = this->get_window_size();
    SDL_SetRenderDrawColor(this->renderer_, 252, 163, 17, 255);
    SDL_FRect top_border {
        0,
        0,
        static_cast<float>(window_size.first),
        static_cast<float>(padding_y_)
    };
    SDL_FRect bottom_border {
        0,
        static_cast<float>(window_size.second - padding_y_),
        static_cast<float>(window_size.first),
        static_cast<float>(padding_y_)
    };
    SDL_FRect left_border {
        0,
        static_cast<float>(padding_y_),
        static_cast<float>(padding_x_),
        static_cast<float>(window_size.second - (padding_y_ * 2))
    };
    SDL_FRect right_border {
        static_cast<float>(window_size.first - padding_x_),
        static_cast<float>(padding_y_),
        static_cast<float>(padding_x_),
        static_cast<float>(window_size.second - (padding_y_ * 2))
    };

    SDL_RenderFillRect(this->renderer_, &top_border);
    SDL_RenderFillRect(this->renderer_, &bottom_border);
    SDL_RenderFillRect(this->renderer_, &left_border);
    SDL_RenderFillRect(this->renderer_, &right_border);
}

void SDLGUIWindow::clear_screen() {
    SDL_SetRenderDrawColor(this->renderer_, 0, 0, 0, 255);
    SDL_RenderClear(this->renderer_);
    this->draw_border();
}

void SDLGUIWindow::read_input() {

    SDL_Event e;
    SDL_PollEvent(&e);

    for (auto& callback : this->key_down_callbacks_) {

        if (e.type == SDL_EVENT_QUIT)
        {
            callback(nibbler::Key::ESC);
            break;
        }
        else if (e.type == SDL_EVENT_WINDOW_RESIZED) {
            std::pair<int, int> res = this->get_window_size();

            if (res.first < min_resolution_px)
                res.first = min_resolution_px;
            if (res.second < min_resolution_px)
                res.second = min_resolution_px;
            SDL_SetWindowSize(this->window_, res.first, res.second);

            this->square_size_px_ = std::min((res.first / this->gameboard_width_squares_),(res.second / this->gameboard_height_squares_));
            this->padding_x_ = (res.first - (this->square_size_px_ * this->gameboard_width_squares_)) / 2;
            this->padding_y_ = (res.second - (this->square_size_px_ * this->gameboard_height_squares_)) / 2;
        }

        switch (e.key.key)
        {
            case SDLK_ESCAPE: callback(nibbler::Key::ESC); break;
            case SDLK_1: callback(nibbler::Key::NUMBER_1); break;
            case SDLK_2: callback(nibbler::Key::NUMBER_2); break;
            case SDLK_3: callback(nibbler::Key::NUMBER_3); break;
            case SDLK_4: callback(nibbler::Key::NUMBER_4); break;
            case SDLK_5: callback(nibbler::Key::NUMBER_5); break;
            case SDLK_6: callback(nibbler::Key::NUMBER_6); break;
            case SDLK_7: callback(nibbler::Key::NUMBER_7); break;
            case SDLK_8: callback(nibbler::Key::NUMBER_8); break;
            case SDLK_9: callback(nibbler::Key::NUMBER_9); break;
            case SDLK_0: callback(nibbler::Key::NUMBER_0); break;
            case SDLK_UP: callback(nibbler::Key::ARROW_UP); break;
            case SDLK_LEFT: callback(nibbler::Key::ARROW_LEFT); break;
            case SDLK_RIGHT: callback(nibbler::Key::ARROW_RIGHT); break;
            case SDLK_DOWN: callback(nibbler::Key::ARROW_DOWN); break;
            default: break;
        }
    }
}

void SDLGUIWindow::draw_snake(const std::vector<nibbler::Position> &snake) {
    std::pair<int, int> window_size = get_window_size();
    SDL_SetRenderScale(this->renderer_, 1, 1);
    SDL_SetRenderDrawColor(this->renderer_, 163, 177, 138, 255);

    for (const nibbler::Position& p : snake) {
        float x = static_cast<float>(p.x * this->square_size_px_) + this->padding_x_;
        float y = static_cast<float>(p.y * this->square_size_px_) + this->padding_y_;
        float width = static_cast<float>(this->square_size_px_);
        float height = static_cast<float>(this->square_size_px_);
        SDL_FRect body_square {x, y, width, height};
        
        SDL_RenderFillRect(this->renderer_, &body_square);
    }
}

void SDLGUIWindow::draw_fruit(const nibbler::Position& fruit_pos) {
    std::pair<int, int> window_size = get_window_size();
    SDL_SetRenderDrawColor(this->renderer_, 188, 71, 73, 255);
    float x = static_cast<float>(fruit_pos.x * this->square_size_px_) + this->padding_x_;
    float y = static_cast<float>(fruit_pos.y * this->square_size_px_) + this->padding_y_;
    float width = static_cast<float>(this->square_size_px_);
    float height = static_cast<float>(this->square_size_px_);
    SDL_FRect fruit_square {x, y, width, height};
    SDL_RenderFillRect(this->renderer_, &fruit_square);
}

void SDLGUIWindow::push_message(const std::string& msg) {
    //TODO:
}

void SDLGUIWindow::set_score(int32_t score) {
    std::string score_text = std::string("Score:" + std::to_string(score));
    SDL_SetRenderScale(this->renderer_, 2, 2);
    SDL_SetRenderDrawColor(this->renderer_, 255, 255, 255, 255);
    SDL_RenderDebugText(this->renderer_, 10, 1, score_text.c_str());
}

void SDLGUIWindow::render() {
    SDL_RenderPresent(this->renderer_);
}

const std::pair<int, int> SDLGUIWindow::get_window_size() const {
    int w, h;
    SDL_GetWindowSize(this->window_, &w, &h);
    return std::make_pair(w, h);
}

SDLGUI::SDLGUI() {}
SDLGUI::~SDLGUI() {}

std::unique_ptr<nibbler::IWindow>
SDLGUI::create_window(
    int32_t resolution_width_px,
    int32_t resolution_height_px,
    int32_t gameboard_width_squares,
    int32_t gameboard_height_squares,
    std::string font_path,
    std::string title
) {
    try
    {
        return std::make_unique<SDLGUIWindow>(
            resolution_width_px,
            resolution_height_px,
            gameboard_width_squares,
            gameboard_height_squares,
            std::move(title));
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return nullptr;
    }
}

}

extern "C" {

nibbler::INibblerGraphicsApi* create_graphics_library() {
    return new sdlgui::SDLGUI();
}

void destroy_graphics_library(nibbler::INibblerGraphicsApi* lib) {
    delete lib;
}

}