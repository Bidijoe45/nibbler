#include "config.hpp"

#include <string>

namespace nibbler {

/**
 * TODO: implement this
 */
Configuration ConfigParser::parseConfigFile(const std::string &file_path) {
    Configuration config;

    ConfigLibrary tty_gui = { .key="4", .name="TTY_GUI", .path="build/lib/tty-gui/libTTY_GUI.dylib" };
    ConfigLibrary sdl_gui = { .key="2", .name="SDL_GUI", .path="build/lib/sdl/libSDL_GUI.dylib" };
    ConfigLibrary raylib_gui = { .key="3", .name="RAYLIB_GUI", .path="build/lib/raylib/libRAYLIB_GUI.dylib" };
    ConfigLibrary sfml_gui = { .key="1", .name="SFML_GUI", .path="build/lib/sfml/libSFML_GUI.dylib" };

    config.gui_libraries.push_back(tty_gui);
    config.gui_libraries.push_back(sdl_gui);
    config.gui_libraries.push_back(raylib_gui);
    config.gui_libraries.push_back(sfml_gui);

    return config;
}

}
