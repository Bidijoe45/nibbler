#pragma once
#ifndef GLFW_GUI_HPP
#define GLFW_GUI_HPP

#include "nibbler/graphics_api.hpp"
#include <GLFW/glfw3.h>

namespace glfwgui {

class GLFWGUIWindow : public nibbler::IWindow {
    public:
        GLFWGUIWindow(size_t width_squares, size_t height_squares, std::string title);
        ~GLFWGUIWindow();

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
        GLFWwindow* window;
        std::vector<nibbler::IWindow::KeyDownCallback> key_down_callbacks_;
        const int square_size_px_;
        const int border_size_px;

        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

class GLFWGUI : public nibbler::INibblerGraphicsApi {
    public:
        GLFWGUI();
        ~GLFWGUI();
        std::unique_ptr<nibbler::IWindow> create_window(std::size_t width_squares, std::size_t height_squares, std::string title) override;
};

}

extern "C" {
    nibbler::INibblerGraphicsApi* create_graphics_library();
    void destroy_graphics_library(nibbler::INibblerGraphicsApi* lib);
}

#endif
