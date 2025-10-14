#include "sdl_gui.hpp"
#include "nibbler/graphics_api.hpp"

#include <SDL3/SDL.h>

#include <iostream>
#include <numeric>

namespace sdlgui {

SDLGUIWindow::SDLGUIWindow(std::size_t resolution_width, std::size_t resolution_height, size_t min_resolution, std::size_t width_squares, std::size_t height_squares, std::string title)
    : nibbler::IWindow(resolution_width, resolution_height, min_resolution, width_squares, height_squares, std::move(title)),
      width_squares_(width_squares), height_squares_(height_squares)
{
    this->square_size_px_ = std::min((resolution_width / width_squares),(resolution_height / height_squares));
    this->padding_x_ = (resolution_width - (this->square_size_px_ * width_squares)) / 2;
    this->padding_y_ = (resolution_height - (this->square_size_px_ * height_squares)) / 2;

    if (!SDL_CreateWindowAndRenderer(
        title.c_str(),
        resolution_width,
        resolution_height,
        SDL_WINDOW_RESIZABLE,
        &this->window,
        &this->renderer))
    {
        // FIXME: should probably throw an exception or something so that the caller will have some sort of feedback of whether construction failed
        std::cerr << "SDL_CreateWindowAndRenderer error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(this->window);
        SDL_PumpEvents(); // needed on macOS
        SDL_Quit();
    }
}

SDLGUIWindow::~SDLGUIWindow()
{
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_PumpEvents(); // needed on macOS
    SDL_Quit();
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
    SDL_SetRenderDrawColor(this->renderer, 252, 163, 17, 255);
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

    SDL_RenderFillRect(this->renderer, &top_border);
    SDL_RenderFillRect(this->renderer, &bottom_border);
    SDL_RenderFillRect(this->renderer, &left_border);
    SDL_RenderFillRect(this->renderer, &right_border);
}

void SDLGUIWindow::clear_screen() {
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
    SDL_RenderClear(this->renderer);
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

            if (res.first < this->min_resolution_)
                res.first = this->min_resolution_;
            if (res.second < this->min_resolution_)
                res.second = this->min_resolution_;
            SDL_SetWindowSize(this->window, res.first, res.second);

            this->square_size_px_ = std::min((res.first / this->width_squares_),(res.second / this->height_squares_));
            this->padding_x_ = (res.first - (this->square_size_px_ * this->width_squares_)) / 2;
            this->padding_y_ = (res.second - (this->square_size_px_ * this->height_squares_)) / 2;
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
    SDL_SetRenderScale(this->renderer, 1, 1);
    SDL_SetRenderDrawColor(this->renderer, 163, 177, 138, 255);

    for (const nibbler::Position& p : snake) {
        float x = static_cast<float>(p.x * this->square_size_px_) + this->padding_x_;
        float y = static_cast<float>(p.y * this->square_size_px_) + this->padding_y_;
        float width = static_cast<float>(this->square_size_px_);
        float height = static_cast<float>(this->square_size_px_);
        SDL_FRect body_square {x, y, width, height};
        
        SDL_RenderFillRect(this->renderer, &body_square);
    }
}

void SDLGUIWindow::draw_fruit(const nibbler::Position& fruit_pos) {
    std::pair<int, int> window_size = get_window_size();
    SDL_SetRenderDrawColor(this->renderer, 188, 71, 73, 255);
    float x = static_cast<float>(fruit_pos.x * this->square_size_px_) + this->padding_x_;
    float y = static_cast<float>(fruit_pos.y * this->square_size_px_) + this->padding_y_;
    float width = static_cast<float>(this->square_size_px_);
    float height = static_cast<float>(this->square_size_px_);
    SDL_FRect fruit_square {x, y, width, height};
    SDL_RenderFillRect(this->renderer, &fruit_square);
}

void SDLGUIWindow::push_message(const std::string& msg) {
    //TODO:
}

void SDLGUIWindow::set_score(int score) {
    std::string score_text = std::string("Score:" + std::to_string(score));
    SDL_SetRenderScale(this->renderer, 2, 2);
    SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
    SDL_RenderDebugText(this->renderer, 10, 1, score_text.c_str());
}

void SDLGUIWindow::render() {
    SDL_RenderPresent(this->renderer);
}

std::pair<int, int> SDLGUIWindow::get_window_size() {
    int w, h;
    SDL_GetWindowSize(this->window, &w, &h);
    return std::make_pair(w, h);
}

SDLGUI::SDLGUI() {}
SDLGUI::~SDLGUI() {}

std::unique_ptr<nibbler::IWindow>
SDLGUI::create_window(std::size_t resolution_width, std::size_t resolution_height, std::size_t min_resolution, std::size_t width_squares, std::size_t height_squares, std::string font_path, std::string title) {
    return std::make_unique<SDLGUIWindow>(resolution_width, resolution_height, min_resolution, width_squares, height_squares, std::move(title));
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