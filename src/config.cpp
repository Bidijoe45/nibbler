#include "config.hpp"

#include <string>
#include <iostream>

namespace nibbler {

/**
 * TODO: implement this
 */
Configuration ConfigParser::parseConfigFile(const std::string &file_path) {
    Configuration config;

    config.gameboard_width_squares = 30;
    config.gameboard_height_squares = 30;
    config.window_width_pixels = 640;
    config.window_height_pixels = 480;

    ConfigLibrary tty_gui = { .key="1", .name="TTY_GUI", .path="build/lib/tty-gui/libTTY_GUI.dylib" };
    config.gui_libraries.push_back(tty_gui);

    return config;
}

}