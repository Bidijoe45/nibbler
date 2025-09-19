#include "sdl_gui.hpp"
#include "nibbler/graphics_api.hpp"

#include <SDL3/SDL.h>

#include <iostream>

namespace sdlgui {

SDLGUIWindow::SDLGUIWindow(std::size_t width_squares, std::size_t height_squares, std::string title)
    : nibbler::IWindow(width_squares, height_squares, std::move(title))
{
    this->window = SDL_CreateWindow("SDL3 Project",640, 480, 0);
    if (this->window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
    }

    this->render = SDL_CreateRenderer(this->window, NULL);
    if (this->render == nullptr) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(this->window);
        SDL_Quit();
    }
}

SDLGUIWindow::~SDLGUIWindow() {
    SDL_DestroyRenderer(this->render);
    SDL_DestroyWindow(this->window);
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

std::pair<size_t, size_t> SDLGUIWindow::get_window_size_squares() {
    //TODO:
}

void SDLGUIWindow::read_input() {
    SDL_Event e;
    SDL_PollEvent(&e);

    for (auto& callback : this->key_down_callbacks_) {
        if (e.type == SDL_EVENT_QUIT) callback(nibbler::Key::ESC);
        if (e.key.key == SDLK_ESCAPE) callback(nibbler::Key::ESC);
    }
}

void SDLGUIWindow::draw_snake(std::vector<nibbler::Position> &snake) {
    //TODO:
}

void SDLGUIWindow::draw_fruit(nibbler::Position& fruit_pos) {
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

std::shared_ptr<nibbler::IWindow>
SDLGUI::create_window(std::size_t width_squares, std::size_t height_squares, std::string title) {
    return std::make_shared<SDLGUIWindow>(width_squares, height_squares, std::move(title));
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