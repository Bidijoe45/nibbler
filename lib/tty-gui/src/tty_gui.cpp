#include "tty_gui.hpp"
#include "nibbler/graphics_api.hpp"
#include <iostream>
#include <utility>

namespace ttygui {

    TTYGUIWindow::TTYGUIWindow(std::size_t width, std::size_t height, std::string title)
        : nibbler::IWindow(width, height, std::move(title)) {}

    TTYGUIWindow::~TTYGUIWindow() {};

    void TTYGUIWindow::add_event_listener_key_down(nibbler::IWindow::KeyDownCallback) {}
    void TTYGUIWindow::add_event_listener_key_up(nibbler::IWindow::KeyUpCallback) {}
    void TTYGUIWindow::add_event_listener_key_press(nibbler::IWindow::KeyPressCallback) {}

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
