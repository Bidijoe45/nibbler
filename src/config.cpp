#include "config.hpp"

#include <string>

namespace nibbler {

/**
 * TODO: implement this
 */
Configuration ConfigParser::parseConfigFile(const std::string &file_path) {
    Configuration config;

    ConfigLibrary tty_gui = { .key="3", .name="TTY_GUI", .path="build/lib/tty-gui/libTTY_GUI.dylib" };
    ConfigLibrary sdl_gui = { .key="2", .name="SDL_GUI", .path="build/lib/sdl/libSDL_GUI.dylib" };
    ConfigLibrary raylib_gui = { .key="1", .name="RAYLIB_GUI", .path="build/lib/raylib/libRAYLIB_GUI.dylib" };
    //ConfigLibrary glfw_gui = { .key="4", .name="GLFW_GUI", .path="build/lib/glfw/libGLFW_GUI.dylib" };

    config.gui_libraries.push_back(tty_gui);
    config.gui_libraries.push_back(sdl_gui);
    //config.gui_libraries.push_back(glfw_gui);
    config.gui_libraries.push_back(raylib_gui);

    return config;
}

}
