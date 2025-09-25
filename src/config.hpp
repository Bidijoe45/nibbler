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
};

struct Configuration {
    // These come from the CLI
    size_t gameboard_width_squares = 30;
    size_t gameboard_height_squares = 30;

    // These come from the config file
    std::vector<ConfigLibrary> gui_libraries;
};

class ConfigParser {
public:
    static Configuration parseConfigFile(const std::string &file_path);
};

}

#endif
