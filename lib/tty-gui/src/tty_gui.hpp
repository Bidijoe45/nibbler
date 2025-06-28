#pragma once
#ifndef TTY_GUI_HPP
#define TTY_GUI_HPP

#include <cstddef>
#include <string>
#include <memory>
#include "nibbler/graphics_api.hpp"

namespace ttygui {

class TTYGUIWindow : public nibbler::IWindow {
public:
    TTYGUIWindow(std::size_t width, std::size_t height, std::string title);
    ~TTYGUIWindow();

    void add_event_listener_key_down(nibbler::IWindow::KeyDownCallback cb);
    void add_event_listener_key_up(nibbler::IWindow::KeyUpCallback cb);
    void add_event_listener_key_press(nibbler::IWindow::KeyPressCallback cb);
};

class TTYGUI : public nibbler::INibblerGraphicsApi {
public:
    TTYGUI();
    ~TTYGUI();

    std::shared_ptr<nibbler::IWindow>
    create_window(std::size_t width, std::size_t height, std::string title);
};

} 

extern "C" {

nibbler::INibblerGraphicsApi* create_graphics_library();
void                        destroy_graphics_library(nibbler::INibblerGraphicsApi*);

}

#endif