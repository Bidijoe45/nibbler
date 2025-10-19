#pragma once
#ifndef NIBBLER_CONFIG
#define NIBBLER_CONFIG

#include <string>
#include <vector>

namespace nibbler {

struct ConfigLibrary {
    std::string key;
    std::string name;
    std::string path;
    std::string font_path;
    int32_t resolution_width;
    int32_t resolution_height;
};

struct Configuration {
    // These come from the CLI
    int32_t gameboard_width_squares = 0;
    int32_t gameboard_height_squares = 0;

    // These come from the config file
    std::vector<ConfigLibrary> gui_libraries;

    bool valid = false;
};

class ConfigParser {
public:
    static Configuration parseConfigFile(const std::string &file_path);
};

}

#endif
