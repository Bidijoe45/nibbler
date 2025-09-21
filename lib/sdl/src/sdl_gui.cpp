#include "sdl_gui.hpp"
#include "nibbler/graphics_api.hpp"

#include <SDL3/SDL.h>

#include <iostream>

namespace sdlgui {

SDLGUIWindow::SDLGUIWindow(std::size_t width_squares, std::size_t height_squares, std::string title)
    : nibbler::IWindow(width_squares, height_squares, std::move(title)),
      square_size_px_(20)
{
    if (!SDL_CreateWindowAndRenderer(
        title.c_str(),
        this->square_size_px_ * width_squares,
        this->square_size_px_ * height_squares,
        0,
        &this->window,
        &this->render))
    {
        std::cerr << "SDL_CreateWindowAndRenderer error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(this->window);
        SDL_Quit();
    }
}

SDLGUIWindow::~SDLGUIWindow()
{
    SDL_DestroyRenderer(this->render);
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

void SDLGUIWindow::clear_screen() {
    SDL_FRect greenSquare {270, 190, 100, 100};
    
    SDL_SetRenderDrawColor(this->render, 0, 0, 0, 255); // Set render draw color to black
    SDL_RenderClear(this->render); // Clear the renderer

    SDL_SetRenderDrawColor(this->render, 0, 255, 0, 255); // Set render draw color to green
    SDL_RenderFillRect(this->render, &greenSquare); // Render the rectangle
    
    SDL_RenderPresent(this->render); // Render the screen
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
        switch (e.key.key)
        {
            case SDLK_ESCAPE: callback(nibbler::Key::ESC); break;
            case SDLK_1: callback(nibbler::Key::NUMBER_1); break;
            case SDLK_2: callback(nibbler::Key::NUMBER_2); break;
            case SDLK_3: callback(nibbler::Key::NUMBER_3); break;
            default: break;
        }
    }
}

void SDLGUIWindow::draw_snake(const std::vector<nibbler::Position> &snake) {
    //TODO:
}

void SDLGUIWindow::draw_fruit(const nibbler::Position& fruit_pos) {
    //TODO:
}

void SDLGUIWindow::push_message(const std::string& msg) {
    //TODO:
}

void SDLGUIWindow::set_score(int score) {
    //TODO:
}

SDLGUI::SDLGUI() {}
SDLGUI::~SDLGUI() {}

std::unique_ptr<nibbler::IWindow>
SDLGUI::create_window(std::size_t width_squares, std::size_t height_squares, std::string title) {
    return std::make_unique<SDLGUIWindow>(width_squares, height_squares, std::move(title));
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