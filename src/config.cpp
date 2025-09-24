#include "config.hpp"

#include <string>
#include <iostream>

namespace nibbler {

/**
 * TODO: implement this
 */
Configuration ConfigParser::parseConfigFile(const std::string &file_path) {
    Configuration config;

    ConfigLibrary tty_gui = { .key="2", .name="TTY_GUI", .path="build/lib/tty-gui/libTTY_GUI.dylib" };
    ConfigLibrary sdl_gui = { .key="1", .name="SDL_GUI", .path="build/lib/sdl/libSDL_GUI.dylib" };
    config.gui_libraries.push_back(tty_gui);
    config.gui_libraries.push_back(sdl_gui);

    return config;
}

}