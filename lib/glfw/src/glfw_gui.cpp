#include "nibbler/graphics_api.hpp"
#include "glfw_gui.hpp"

#include <iostream>

#include <GLFW/glfw3.h>

namespace glfwgui {

static void error_callback(int error, const char* description)
{
    std::cerr << "Error: " << description << std::endl;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    for (auto &callback : this->key_down_callbacks_)
    {
        switch (key)
        {
            case GLFW_KEY_ESCAPE: callback(nibbler::Key::ESC); break;
            case GLFW_KEY_1: callback(nibbler::Key::NUMBER_1); break;
            case GLFW_KEY_2: callback(nibbler::Key::NUMBER_2); break;
            case GLFW_KEY_3: callback(nibbler::Key::NUMBER_3); break;
            case GLFW_KEY_UP: callback(nibbler::Key::ARROW_UP); break;
            case GLFW_KEY_LEFT: callback(nibbler::Key::ARROW_LEFT); break;
            case GLFW_KEY_RIGHT: callback(nibbler::Key::ARROW_RIGHT); break;
            case GLFW_KEY_DOWN: callback(nibbler::Key::ARROW_DOWN); break;
            default: break;
        }
    }
}

GLFWGUIWindow::GLFWGUIWindow(size_t width_squares, size_t height_squares, std::string title)
    : nibbler::IWindow(width_squares, height_squares, std::move(title)),
      square_size_px_(20),
      border_size_px(square_size_px_)
{
    glfwSetErrorCallback(error_callback);
    // FIXME: should probably throw exceptions or something so that the caller will have some sort of feedback of whether construction failed
    if (!glfwInit())
    {
        std::cerr << "glfwInit error" << std::endl;
    }

    this->window = glfwCreateWindow(
        this->square_size_px_ * width_squares + (border_size_px * 2),
        this->square_size_px_ * height_squares + (border_size_px * 2),
        title.c_str(),
        NULL, NULL);
    if (!this->window)
    {
        // Window or OpenGL context creation failed
        std::cerr << "glfwCreateWindow error" << std::endl;
    }

    glfwMakeContextCurrent(this->window);
    glfwSetKeyCallback(this->window, key_callback);
}

GLFWGUIWindow::~GLFWGUIWindow()
{
    glfwDestroyWindow(this->window);
    glfwTerminate();
}

void GLFWGUIWindow::add_event_listener_key_down(KeyDownCallback callback)
{
    this->key_down_callbacks_.push_back(callback);
}

void GLFWGUIWindow::add_event_listener_key_up(KeyUpCallback callback)
{
    //TODO:
}

void GLFWGUIWindow::add_event_listener_key_press(KeyPressCallback callback)
{
    //TODO:
}

void GLFWGUIWindow::clear_screen()
{

}

void GLFWGUIWindow::read_input()
{
    glfwPollEvents();
}

void GLFWGUIWindow::draw_snake(const std::vector<nibbler::Position> &snake)
{

}

void GLFWGUIWindow::draw_fruit(const nibbler::Position& fruit_pos)
{

}

void GLFWGUIWindow::set_score(int score)
{

}

void GLFWGUIWindow::render()
{

}

void GLFWGUIWindow::push_message(const std::string &msg)
{

}



GLFWGUI::GLFWGUI() {}
GLFWGUI::~GLFWGUI() {}

std::unique_ptr<nibbler::IWindow> GLFWGUI::create_window(std::size_t width_squares, std::size_t height_squares, std::string title)
{
    return std::make_unique<GLFWGUIWindow>(width_squares, height_squares, std::move(title));
}

} // namespace glfwgui

extern "C" {

nibbler::INibblerGraphicsApi* create_graphics_library() {
    return new glfwgui::GLFWGUI();
}

void destroy_graphics_library(nibbler::INibblerGraphicsApi* lib) {
    delete lib;
}

}
